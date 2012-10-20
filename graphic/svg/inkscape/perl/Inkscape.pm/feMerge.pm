use warnings;
use strict;
package feMerge;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  $self  -> {id}       = 'feMerge' . $id++;

  for my $mergeNode (@_) {
    push @{$self->{mergeNodes}}, Filter::result_($mergeNode);
  }

  return $self;
}

my $mergeNodeId=1;
sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile "      <feMerge\n";
  print $svgFile "         id=\"$self->{id}\">\n";

  for my $mergeNode (@{$self->{mergeNodes}}) {

    print $svgFile "        <feMergeNode\n";
    print $svgFile "           inkscape:collect=\"always\"\n";
    print $svgFile "           id=\"feMergeNode" . $mergeNodeId ++ . "\"\n";
    print $svgFile "           in=\"$mergeNode\" />\n";
  }

  print $svgFile "      </feMerge>\n";
}

1;
