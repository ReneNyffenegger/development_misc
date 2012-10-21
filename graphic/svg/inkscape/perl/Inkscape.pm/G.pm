use warnings;
use strict;
package G;
use Circle;
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

sub circle {

  my $self      = shift;

  my $circle    = new Circle(@_);

  $self -> addElem($circle);

  return $circle;
}

sub ellipse {
  my $self      = shift;

  my $x         = shift;
  my $y         = shift;

  my $rx        = shift;
  my $ry        = shift;

  my $x1  = $x + $rx;
  my $rx2 = $rx * 2;     

  my $path      = new Path;

  $self -> addElem($path);

  $path -> {d} = "m $x1,$y a $rx,$ry 0 1 1 -$rx2,0 $rx,$ry 0 1 1 $rx2,0 z";

  $path -> {sodipodi_type} = 'arc';

  $path -> {sodipodi_cx} = $x;
  $path -> {sodipodi_cy} = $y;
  $path -> {sodipodi_rx} = $rx;
  $path -> {sodipodi_ry} = $ry;

  return $path;

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

  $path -> {inkscape_connector_curvature} = '0';
  $path -> {sodipodi_nodetypes} = 'cc';

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
