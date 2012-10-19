use warnings;
use strict;
package feComposite;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self;

  $self  -> {id}       = 'feComposite' . $id++;
  $self  -> {in2}      = 'SourceGraphic';
  $self  -> {operator} = 'atop';
  $self  -> {result}   = 'result0';


  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile <<"E"
      <feComposite
         id="$self->{id}"
         in2="$self->{in2}"
         operator="$self->{operator}"
         result="$self->{result}" />
E
}

1;
