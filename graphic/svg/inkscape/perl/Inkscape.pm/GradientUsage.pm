use warnings;
use strict;
package GradientUsage;

sub new {
  my $self = {};
  bless $self, shift;

  $self -> {id} = $GradientDefinition::id++;

  $self -> {gradientDefinition} = shift;

  $self -> {x1} = shift;
  $self -> {y1} = shift;

  $self -> {x2} = shift;
  $self -> {y2} = shift;

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile <<PIECE;
    <linearGradient
       inkscape:collect="always"
       xlink:href="#$self->{gradientDefinition}->{type}Gradient$self->{gradientDefinition}->{id}"
       id="$self->{gradientDefinition}->{type}Gradient$self->{id}"
       x1="$self->{x1}"
       y1="$self->{y1}"
       x2="$self->{x2}"
       y2="$self->{y2}"
       gradientUnits="userSpaceOnUse" />
PIECE

}

1;
