use warnings;
use strict;
package feBlend;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  $self  -> {mode} = shift;

  $self -> {id} = 'feBlend' . $id++;

  my %options = @_;

  $self  -> {in2} = Filter::result_($options{in2}) if exists $options{in2};

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile "      <feBlend\n";
  print $svgFile "         mode=\"$self->{mode}\"\n";
  print $svgFile "         in2=\"$self->{in2}\"\n";
  print $svgFile "         id=\"$self->{id}\" />\n";
}

1;
