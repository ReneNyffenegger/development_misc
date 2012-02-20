use warnings;
use strict;

use XML::Parser;
use DBI;
use utf8;

my $osmFileName = $ARGV[0];

open (my $osmFile, '<', $osmFileName) or die "could not open $osmFileName";

my $xml_parser=new XML::Parser(Style=>'Stream');


my $dbh = DBI->connect('DBI:mysql:osm', 'osmusr', $ENV{'OSM_PASSWORD');
$dbh -> do ("use osm");
my $sth_insert_node         = $dbh -> prepare('insert into node       (id, lat, lon) values (?,?,?)');
my $sth_insert_way          = $dbh -> prepare('insert into way        (id, building) values (?,?  )');
my $sth_insert_relation     = $dbh -> prepare('insert into relation   (id          ) values (?    )');

my $sth_insert_tag          = $dbh -> prepare('insert into tag        (k, v, node_id, way_id, relation_id) values (?,?,?,?,?)');

my $sth_insert_node_in_way  = $dbh -> prepare('insert into node_in_way(node_id, way_id, order_) values (?,?,?)');

my $sth_insert_node_in_relation  = $dbh -> prepare('insert into node_in_relation(node_id, relation_id, role) values (?,?,?)');
my $sth_insert_way_in_relation   = $dbh -> prepare('insert into way_in_relation (way_id , relation_id, role) values (?,?,?)');

$xml_parser -> setHandlers (
    Start   => \&xml_start_element,
    End     => \&xml_end_element,
    Char    => \&xml_character_data,
    Default => \&xml_default,
    Final   => \&xml_final # what xml_parser -> parse($text) will return.
);

$dbh -> begin_work;

$xml_parser-> parse($osmFile);

$dbh -> commit;

#   { Functions used by XML::Parser, see setHandlers above.

my $counter=0;
sub xml_start_element {

  my($expat, $element, %attributes) = @_;

  $expat ->{node_way_or_relation} = "" unless defined $expat->{node_way_or_relation};

  if ($element eq 'relation' or $element eq 'way' or $element eq 'node') {
      die if $expat -> {node_way_or_relation};
      $expat -> {node_way_or_relation} = $element;
  }

  my $k;
  my $v;

  my $lat;
  my $lon;

   
  if ($element eq $expat -> {node_way_or_relation}) {
    $expat -> {current_id} = $attributes{id};

    $expat -> {lat} = $attributes{lat};
    $expat -> {lon} = $attributes{lon};
  }
  elsif ($element eq 'tag') {
    $k = $attributes{k};
    $v = $attributes{v};
  }
  elsif ($element eq 'nd') {
    push @{$expat -> {nds}}, $attributes{'ref'};
  }
  elsif ($element eq 'member') {
    push @{$expat -> {members}}, {type => $attributes{'type'}, 'ref' => $attributes{'ref'}, role => $attributes{role}};
  }

  if ($element eq 'tag') {
     if    ($k eq 'created_by' or $k eq 'source') {
         # These keys don't seem very interesting
     }
     elsif ($k eq 'building') {
     #
     #  TODO: Can relations have the 'building' key?
     #        Currently, those wouldn't be stored.
     #
        $expat -> {building} = 1;
     }
     else {
       push @{$expat -> {tags}}, {k=>$k, v=>$v} unless $k eq 'created_by' or $k eq 'source'
     }
  }
}

sub xml_end_element {
  my($expat, $element, %attributes) = @_;

  if ($expat -> {node_way_or_relation} and
      $expat -> {node_way_or_relation} eq $element) {


    if    ($element eq 'node'    ) {

        $sth_insert_node -> execute($expat->{current_id}, $expat->{lat}, $expat->{lon});

        foreach my $kv (@{$expat->{tags}}) {
          $sth_insert_tag -> execute($kv->{k}, $kv->{v}, $expat->{current_id}, undef, undef);
        }

    }
    elsif ($element eq 'way'     ) {

        $sth_insert_way -> execute($expat->{current_id}, $expat->{building});

        foreach my $kv (@{$expat->{tags}}) {
          $sth_insert_tag -> execute($kv->{k}, $kv->{v}, undef, $expat->{current_id}, undef);
        }

        my $pos = 0;
        foreach my $nd (@{$expat->{nds}}) {
          $pos++;
          $sth_insert_node_in_way -> execute($nd, $expat->{current_id}, $pos);
        }

    }
    elsif ($element eq 'relation') {

        $sth_insert_relation -> execute($expat->{current_id});

        foreach my $kv (@{$expat->{tags}}) {
          $sth_insert_tag -> execute($kv->{k}, $kv->{v}, undef, undef, $expat->{current_id});
        }
        foreach my $member (@{$expat->{members}}) {

          if ($member->{type} eq 'way') {
            $sth_insert_way_in_relation  -> execute($member->{'ref'}, $expat->{current_id}, $member->{role});
          }
          else {
            $sth_insert_node_in_relation -> execute($member->{'ref'}, $expat->{current_id}, $member->{role});
          }
        }

    }


    # Reset the accumulated values for the three
    # tags node, way and relation

    $expat -> {node_way_or_relation} = "";
    $expat -> {tags    } = [];
    $expat -> {nds     } = [];
    $expat -> {members } = [];
    $expat -> {building} =  0;

    if ($counter ++ > 100000) {
      print "commit\n";
      $counter = 0;
      $dbh -> commit;
      $dbh -> begin_work;
    }
  }
}

sub xml_character_data {
  my($expat, $data) = @_;
  $data =~ s/{amp}/&/;
}

sub xml_final {

  my($expat) = @_;

  return $expat->{returned};
}


sub xml_default {
}


# }


