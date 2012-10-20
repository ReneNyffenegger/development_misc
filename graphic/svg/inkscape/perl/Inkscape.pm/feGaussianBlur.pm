use warnings;
use strict;
package feGaussianBlur;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  my %options = @_;

  $self  -> {id} = 'feGaussianBlur' . $id++;

  if (exists $options{stdDeviation}) {
     $self  -> {stdDeviation} = $options{stdDeviation};
  }
  else {
     $self  -> {stdDeviation} = 1;
  }

  if (exists $options{in}) {
     $self  -> {in} = $options{in};
  }


  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile "      <feGaussianBlur\n";
  print $svgFile "         stdDeviation=\"$self->{stdDeviation}\"\n";
  print $svgFile "         id=\"$self->{id}\"";

  if (exists $self -> {in} ) {
    print $svgFile "\n         in=\"$self->{in}\"";
  }
  
  print $svgFile " />\n";
}

1;
