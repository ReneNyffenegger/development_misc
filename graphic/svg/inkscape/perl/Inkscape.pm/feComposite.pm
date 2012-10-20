use warnings;
use strict;
package feComposite;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  $self  -> {operator} = shift;

  my %options = @_;

  $self  -> {in}       = Filter::result_($options{in} ) if exists $options{in} ;
  $self  -> {in2}      = Filter::result_($options{in2}) if exists $options{in2};

  $self  -> {id}       = 'feComposite' . $id++;

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile "      <feComposite\n";
  print $svgFile "         id=\"$self->{id}\"";
  print $svgFile "\n         in=\"$self->{in}\""     if exists $self -> {in};
  print $svgFile "\n         in2=\"$self->{in2}\"\n" if exists $self -> {in2};
  print $svgFile "         operator=\"$self->{operator}\"";
  print $svgFile "\n         result=\"$self->{result}\"" if exists $self->{result};
  print $svgFile " />\n";
}

1;
