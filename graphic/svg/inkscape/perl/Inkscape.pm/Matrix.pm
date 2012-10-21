use warnings;
use strict;
package Matrix;

sub new {
  my $self = {};
  bless $self, shift;

  $self -> {m00} = 1;
  $self -> {m01} = 0;
  $self -> {m02} = 0;

  $self -> {m10} = 0;
  $self -> {m11} = 1;
  $self -> {m12} = 0;

  return $self;
}

sub init {
  my $self = {};
  bless $self, shift;

  $self -> {m00} = shift;
  $self -> {m01} = shift;
  $self -> {m02} = shift;

  $self -> {m10} = shift;
  $self -> {m11} = shift;
  $self -> {m12} = shift;

  return $self;
}

sub multiply {
  my $self  = shift;
  my $other = shift;
  
  my $m00 = $self->{m00} * $other->{m00}  +  $self->{m01} * $other->{m10};
  my $m01 = $self->{m00} * $other->{m01}  +  $self->{m01} * $other->{m11};
  my $m02 = $self->{m00} * $other->{m02}  +  $self->{m01} * $other->{m12};

  my $m10 = $self->{m10} * $other->{m00}  +  $self->{m11} * $other->{m10};
  my $m11 = $self->{m10} * $other->{m01}  +  $self->{m11} * $other->{m11};
  my $m12 = $self->{m10} * $other->{m02}  +  $self->{m11} * $other->{m12};

  $self -> {m00} = $m00;
  $self -> {m01} = $m01;
  $self -> {m02} = $m02;

  $self -> {m10} = $m10;
  $self -> {m11} = $m11;
  $self -> {m12} = $m12;
}

sub rotate {
  my $self  = shift;

  my $alpha = shift;

  my $rotation = init Matrix  cos $alpha, sin $alpha, 0,
                             -sin $alpha, cos $alpha, 0;

  return $self -> multiply($rotation);
}

sub tag {
  my $self = shift;

  #
  # Return sthe matrix rounded to 8 digits after the decimal seperator
  # as a tag.
  # %0.8f seemd not really useful as this would have printed 8 digits
  # after the seperator for integers as well, so the following
  # peculiar way was chosen (int (...)).
  # Probably, it can be optimized, but I don't have access to the
  # internet where I am right now and cannot ask stackoverflow.com
  #
  return sprintf "transform=\"matrix(%s,%s,%s,%s,%s,%s)\"",
    map {int ($_ * 10e7 + 0.5) / 10e7} ($self->{m00},$self->{m10},$self->{m01},$self->{m11},$self->{m02},$self->{m12});
}


1;
