use warnings;
use strict;
package OSM::Relation;

sub new {

  my $class = shift;
  my $id    = shift;

  my $self  = shift;

  $self -> {id  } = $id;
  $self -> {ways} = [];

  bless $self, $class;
  return $self;
}

sub addWay {

  my $self = shift;
  my $way  = shift;

  die ref $way unless (ref $way) =~ /OSM::Way/;

  push @{$self->{ways}}, $way;

}

sub asSvgPath {

  my $self             = shift;
  my $style            = shift;
  my $latLongToXY___   = shift;

  die ref $self unless (ref $self) =~ /OSM::Relation/;

  my $paths = "";

  foreach my $way (@{$self->{ways}}) {
    $paths .= $way -> asSvgPath($style, $latLongToXY___);
  }

  return $paths;
}

1;
