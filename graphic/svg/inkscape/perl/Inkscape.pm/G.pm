use warnings;
use strict;
package G;
use Path;
use Rect;
use Text;

my $id = 1;

sub new {

  my $self = {};
  bless $self, shift;

  $self-> {name} = shift;

  $self -> {id} = "g" . $id++;

  return $self;
}

sub makeLayer {
  my $self = shift;

  my $name = shift;

  $self -> {layerName} = $name;
}

sub line {
  my $self      = shift;

  my $xFrom     = shift;
  my $yFrom     = shift;

  my $xDiff     = shift;
  my $yDiff     = shift;

  my $xTo       = $xFrom + $xDiff;
  my $yTo       = $yFrom + $yDiff;

  my $path      = new Path;
  $self -> addElem($path);

  $path -> {d} = "M $xFrom,$yFrom $xTo,$yTo";

  return $path;
}

sub rect {
  my $self      = shift;

  my $rect      = new Rect(@_);
  $self -> addElem($rect);

  return $rect;
}

sub text {

  my $self = shift;

  my $text = new Text(@_);
  $self -> addElem($text);

  return $text;
}

sub g {
  my $self      = shift;
  my $g         = new G;

  $self -> addElem($g);

  return $g;
}

sub addElem {
  my $self      = shift;
  my $elem      = shift;

  push @{$self->{elems}}, $elem;
}

sub write {
  
  my $self      = shift;
  my $svgFile   = shift;
  my $indent    = shift;
  
  print $svgFile '  ' x $indent . "<g\n";
 
  if (exists $self->{layerName}) {
      print $svgFile '  ' x $indent . "   inkscape:label=\"$self->{layerName}\"\n";
      print $svgFile '  ' x $indent . "   inkscape:groupmode=\"layer\"\n";
  }

  print $svgFile '  ' x $indent . "   id=\"$self->{id}\">\n";

  foreach my $elem (@{$self->{elems}}) {
    $elem->write($svgFile, $indent+1);
  }

  print $svgFile '  ' x $indent . "</g>\n";
}

1;
