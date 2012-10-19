use warnings;
use strict;
package feGaussianBlur;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self;

  $self  -> {id} = 'feGaussianBlur' . $id++;

  $self  -> {stdDeviation} = 1;

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile <<"E"
      <feGaussianBlur
         stdDeviation="$self->{stdDeviation}"
         id="$self->{id}" />
E
}

1;
