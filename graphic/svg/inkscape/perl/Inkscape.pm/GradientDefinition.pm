use warnings;
use strict;
package GradientDefinition;

our $id     = 1;
my $stopId = 1;
sub new {
  my $self = {};

  bless $self, shift;

  $self -> {type} = shift;  # linear, ...
  $self -> {id}   = $id++;

  my $stops = shift;

  for my $stop (@{$stops}) {

    push @{$self -> {stops}}, {
            color   => $stop->[0],
            opacity => $stop->[1],
            id      =>"stop" . $stopId++
          };
  }

  return $self;
}

sub write {

  my $self = shift;

  my $svgFile = shift;

  print $svgFile "    <$self->{type}Gradient\n";
  print $svgFile "       id=\"$self->{type}Gradient$self->{id}\">\n";

  my $offset = 0;
  for my $stop (@{$self->{stops}}) {

    print $svgFile "      <stop\n";
    print $svgFile "         style=\"stop-color:$stop->{color};stop-opacity:$stop->{opacity};\"\n";
    print $svgFile "         offset=\"$offset\"\n"; $offset++;
    print $svgFile "         id=\"$stop->{id}\" />\n";

  }

  print $svgFile "    </$self->{type}Gradient>\n";
}

1;
