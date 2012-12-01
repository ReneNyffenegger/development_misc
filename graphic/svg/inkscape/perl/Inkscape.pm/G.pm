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

sub line_M {
  my $self      = shift;

# creates a «zig-zag» line. That is: the
# nodes of the lines are corners.
# The M in «line_M» stands for the Mof the move to.

  my $path = new Path;
  $self -> addElem($path);

  my $d = 'M';
  $path -> {sodipodi_nodetypes} = '';
  $path -> {inkscape_connector_curvature} = '0';

  while (@_) {
    my $x = shift;
    my $y = shift;

    $d .= " $x,$y";
    $path -> {sodipodi_nodetypes} .= 'c';
  }

  $path->{d}=$d;

  return $path;
}

sub line_smooth_nodes {

  #  This procedure should create a line with «smooth»
  #  edges. That is, as though a line would have been
  #  drawn with the Shift+F6 tool («Draw Bezier curves
  #  and straight lines») and then each node (except the
  #  first and the last one) would have made smooth
  # (F2, then «make selected node smooth»).
  #
  #  See also http://stackoverflow.com/questions/13037606/how-does-inkscape-calculate-the-coordinates-for-control-points-for-smooth-edges
  #

  my $self = shift;

  my $path = new Path;
  $self -> addElem($path);

  my $nofNodes = @_ / 2.0;

  die if $nofNodes != int($nofNodes) or $nofNodes < 3;

  #  First segment

  my $x_first = shift;
  my $y_first = shift;

  #  Move to coordinates of first node:

  my $d = "M $x_first,$y_first";

  #  The first control points coincide with
  #  the first node:
  $d .= " C $x_first,$y_first";


  #

  #  The first node is a «corner»:
  my $sodipodi_nodetypes = 'c';


  #  -----------------------------------

  my $x_prev = $x_first;
  my $y_prev = $y_first;

  my $x_current = shift;
  my $y_current = shift;

  # iterate over nodes between first and last node:

  for my $n (2 .. $nofNodes -1) {

  #   Algorithm according to Inkscape's src/ui/tool/node.cpp, method Node::_updateAutoHandles.

      my $x_next = shift;
      my $y_next = shift;

      my $x_vec_prev = $x_prev - $x_current;
      my $y_vec_prev = $y_prev - $y_current;

      my $x_vec_next = $x_next - $x_current;
      my $y_vec_next = $y_next - $y_current;

      my $len_prev   = sqrt( ($x_vec_prev * $x_vec_prev) + ($y_vec_prev * $y_vec_prev) );
      my $len_next   = sqrt( ($x_vec_next * $x_vec_next) + ($y_vec_next * $y_vec_next) );


      # "dir" is an unit vector perpendicular to the bisector of the angle created
      # by the previous node, this node and the next node.

      my $x_dir_=  ($len_prev / $len_next) * $x_vec_next - $x_vec_prev;
      my $y_dir_=  ($len_prev / $len_next) * $y_vec_next - $y_vec_prev;

      # Normalize "dir_"

      my $x_dir = $x_dir_ / sqrt ( $x_dir_ * $x_dir_ + $y_dir_ * $y_dir_);
      my $y_dir = $y_dir_ / sqrt ( $x_dir_ * $x_dir_ + $y_dir_ * $y_dir_);

      my $x_prev_control_point = $x_current + (-$x_dir * ($len_prev / 3));
      my $y_prev_control_point = $y_current + (-$y_dir * ($len_prev / 3));

      my $x_next_control_point = $x_current + ( $x_dir * ($len_next / 3));
      my $y_next_control_point = $y_current + ( $y_dir * ($len_next / 3));

    # ----

      $x_prev_control_point = output_number($x_prev_control_point);
      $y_prev_control_point = output_number($y_prev_control_point);
      $x_next_control_point = output_number($x_next_control_point);
      $y_next_control_point = output_number($y_next_control_point);

    # ----

      $d .= " $x_prev_control_point,$y_prev_control_point $x_current,$y_current $x_next_control_point,$y_next_control_point";

      $x_prev = $x_current;
      $y_prev = $y_current;

      $x_current = $x_next;
      $y_current = $y_next;

    # All nodes except the first and the last node are «smooth»:
      $sodipodi_nodetypes .= 's';

  }


  #  Add last control point before last node. (As it happens,
  #  this control point coincides with the last node:
  $d .= " $x_current,$y_current";

  #  Finally: add the last node:
  $d .= " $x_current,$y_current";

  $path->{d} = $d;

  #  The last node is a «corner» (as is the first one):
  $sodipodi_nodetypes .= 'c';

  $path->{sodipodi_nodetypes} = $sodipodi_nodetypes;

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

  return $self -> line_M($xFrom, $yFrom, $xTo, $yTo);
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

sub output_number {
  my $number = shift;

  my $ret = sprintf("%.7f", $number);

  $ret =~ s/0*$//g;
  $ret =~ s/\.$//g;

  return $ret;
}

1;
