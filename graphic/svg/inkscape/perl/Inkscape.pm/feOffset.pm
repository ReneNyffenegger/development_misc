use warnings;
use strict;
package feOffset;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  $self  -> {id} = 'feOffset' . $id++;

  $self  -> {dx} =  shift;
  $self  -> {dy} =  shift;

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;


  print $svgFile "      <feOffset\n";
  print $svgFile "         dx=\"$self->{dx}\"\n";
  print $svgFile "         dy=\"$self->{dy}\"\n";
  print $svgFile "         id=\"$self->{id}\"";
  print $svgFile "\n         result=\"$self->{result}\"" if exists $self->{result};

  print $svgFile " />\n";
}

1;
