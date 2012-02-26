use warnings;
use strict;

package OSM::Way;

sub new {

  my $class = shift;

  my $id    = shift;

  my $self  = {};
  
  $self -> {id   }  = $id;
  $self -> {nodes}  = [];

  bless $self, $class;

  return $self;

}

sub addNode {

  my $self = shift;
  my $node = shift;

  die ref $node unless (ref $node) =~ /OSM::Node/;

  push @{$self->{nodes}}, $node;

}

sub nodes {

  my $self = shift;

  return @{$self -> {nodes}};

}

sub asSvgPath {
  my $self             = shift;
  my $style            = shift;
  my $latLongToXY___   = shift;

  die ref $self unless (ref $self) =~ /OSM::Way/;

  my $path = "<path style='$style' d='M"; # M: moveto (absolute)

  my $first_node_id;

  my $counter = 0;
  foreach my $node (@{$self->{nodes}}) {
#    my $latLong = $osm -> latLongOfNode($node);
#    die ref $node unless (ref $node) =~ /^OSM::Node/;

     $first_node_id = $node->{id} unless defined $first_node_id;

     $counter ++;

     if ($counter == @{$self->{nodes}}) {

       if ($node -> {id} == $first_node_id) {

       #  If the path starts with the same node as it
       #  ends with, we close the path (with a 'z'):
          $path .= ' z'; # z: Close the path
       }
       else {

       #  The path ends with another node than
       #  it started with (so it's not closed)
       #  We cannot close the path with a 'z',
       #  but have to append the last node:
         my $xy = $latLongToXY___->($node);
         $path .= " $xy->{x},$xy->{y}";
       }
     }
     else {

     # Add any non-last node to the path

       my $xy = $latLongToXY___->($node);
       $path .= " $xy->{x},$xy->{y}";
    }
  }

#

  $path .= "' id='osm_way_$self->{id}'";
  $path .= " inkscape:connector-curvature='0' />\n";
  
  return $path;

  
}


1;
