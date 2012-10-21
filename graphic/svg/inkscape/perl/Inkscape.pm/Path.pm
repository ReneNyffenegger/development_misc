use warnings;
use strict;
package Path;

my $id = 1;

sub new {
  my $self = {};
  bless $self, shift;

#
#       
#   SVG specifies the following path data commands:
#  
#       M: moveto
#       L: lineto
#       H: horizontal lineto
#       V: vertical lineto
#       C: curveto
#       S: smooth curveto
#       Q: quadratic Bézier curve
#       T: smooth quadratic Bézier curveto
#       A: elliptical Arc
#  
#       Capital letters: absolutely positioned
#       lower cases:     relatively positioned.
#
#   Finally, there is also the
#       z: closepath
#  
#   Inkscape seems to prefer absolutely positioned coordinates. In my (limited) tests, relatively
#   positioned commands were converted into absolutely positioned coordinates.
#       
        
# Note: order of styles in <path> different from order in <rect>?
  $self -> {style} -> {'fill'}            = 'none'   ;
  $self -> {style} -> {'stroke'}          = '#000000'; # not in <rect>.
  $self -> {style} -> {'stroke-width'}    = '1px'    ; # px not stated in  stroke-width of <rect>
  $self -> {style} -> {'stroke-linecap'}  = 'butt'   ;
  $self -> {style} -> {'stroke-linejoin'} = 'miter'  ;
  $self -> {style} -> {'stroke-opacity'}  =  1       ;

  $self -> {id} = "path" . $id++;

  $self -> {valid_styles} = [
    {name => 'fill'             , optional => 0},
    {name => 'stroke'           , optional => 0},
    {name => 'stroke-width'     , optional => 0},
    {name => 'stroke-linecap'   , optional => 0},
    {name => 'stroke-linejoin'  , optional => 0},
    {name => 'stroke-miterlimit', optional => 1, default=>'4'},
    {name => 'stroke-opacity'   , optional => 0},
  ];

  return $self;
}

sub style {
  my $self       = shift;
  my $style_text = shift;

  Inkscape::style_($self, $style_text);
}

sub write {
  my $self      = shift;
  my $svgFile   = shift;
  my $indent    = shift;

  my $styleText = Inkscape::finalStyle_($self);

  print $svgFile '  ' x $indent . "<path\n";
  print $svgFile '  ' x $indent . "   style=\"$styleText\"\n";
  print $svgFile '  ' x $indent . "   d=\"$self->{d}\"\n";
  print $svgFile '  ' x $indent . "   id=\"$self->{id}\"\n";
  print $svgFile '  ' x $indent . "   inkscape:connector-curvature=\"0\"\n";
  print $svgFile '  ' x $indent . "   sodipodi:nodetypes=\"cc\" />\n";
}

1;
