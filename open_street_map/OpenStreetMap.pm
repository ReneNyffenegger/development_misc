package OpenStreetMap;

require LWP::UserAgent;

use XML::Parser;

sub new {
  my $self = {};

  $self -> {ua} = LWP::UserAgent->new;

  bless  $self;
  return $self;
}

sub api_call_ {
  my $self       = shift;
  my $name       = shift;
  my $parameters = shift;

  my $call_ = $name;

  if (defined $parameters) {
     $call_ .= "?$parameters";
  }

  my $response = $self -> {ua} -> get("http://api.openstreetmap.org/api/0.6/$call_");

  return $response -> decoded_content;
}

sub capabilities {
  my $self = shift;
  return $self -> api_call_('capabilities');
}

sub map {
  my $self   = shift;

  my $west   = shift;
  my $east   = shift;
  my $north  = shift;
  my $south  = shift;

  return $self -> api_call_('map', "bbox=$west,$south,$east,$north");
}

sub keyValueInMap {

#   This function takes a bounding box ($west .. $east, $north .. $south) 
#   and retrieves the distinct keys, values, and ids.
#   See test.pl for more details.

  my $self = shift;

  my $west   = shift;
  my $east   = shift;
  my $north  = shift;
  my $south  = shift;

  my $text = $self -> map($west, $east, $north, $south);

  my $xml_parser = new XML::Parser(Style=>'Stream');

  $xml_parser -> setHandlers (
      Start   => \&xml_start_element,
      End     => \&xml_end_element,
      Char    => \&xml_character_data,
      Default => \&xml_default,
      Final   => \&xml_final # what xml_parser -> parse($text) will return.
  );

  return $xml_parser -> parse($text);
}

#   { Functions used by XML::Parser, see setHandlers above.

sub xml_start_element {

  my($expat, $element, %attributes) = @_;

  if ($element eq 'relation' or $element eq 'way' or $element eq 'node') {
      die if $expat -> {node_way_or_relation};
      $expat -> {node_way_or_relation} = $element;
  }

  my $k;
  my $v;

  foreach my $attribute (keys %attributes) {
   
    if ($element eq $expat -> {node_way_or_relation} and $attribute eq 'id') {
       $expat -> {current_id} = $attributes{$attribute};
    }
    elsif ($element eq 'tag') {

      if ($attribute eq 'k') {
        $k = $attributes{$attribute};
      }
      elsif ($attribute eq 'v') {
        $v = $attributes{$attribute};
      }

    }
  }

  if ($element eq 'tag') {
     push @{$expat->{returned} -> {$k} -> {$v} -> {$expat->{node_way_or_relation}}}, $expat->{current_id};
  }
}

sub xml_end_element {
  my($expat, $element, %attributes) = @_;

  if ($expat -> {node_way_or_relation} and
      $expat -> {node_way_or_relation} eq $element) {

    $expat -> {node_way_or_relation} = "";
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

# }

sub xml_default {
}


1;
