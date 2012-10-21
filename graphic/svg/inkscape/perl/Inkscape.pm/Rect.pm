use warnings;
use strict;
package Rect;

my $id=1;

sub new {
  my $self = {};

  bless $self, shift;

  $self->{x}          = shift;
  $self->{y}          = shift;
  $self->{width}      = shift;
  $self->{height}     = shift;

  my %options         = @_;

  $self -> {rx}       = $options{rx} if exists $options{rx};
  $self -> {ry}       = $options{ry} if exists $options{ry};

# Note: order of styles in <rect> different from order in <line>?

# $self -> {style} -> {'opacity'}            = 1;

  $self -> {style} -> {'fill'}               ='none'    ; # not in <line>
  $self -> {style} -> {'fill-opacity'}       = 1        ; # not in <line>

  $self -> {style} -> {'stroke-width'}       = 1        ; # Is default px? px explicitely stated in styles of <line>

  $self -> {style} -> {'stroke'}             = '#000000';

  $self -> {style} -> {'stroke-miterlimit'}  = 4        ; # Is default px? px explicitely stated in styles of <line>
  $self -> {style} -> {'stroke-dasharray'}   ='none'    ; # not in <line>
  $self -> {style} -> {'stroke-opacity'}     = '1'      ; # not in <line>

  $self -> {style} -> {'stroke-linecap'}     = 'butt'   ; # found in <line>

  $self->{id} = "rect" . $id++;

  $self -> {valid_styles} = [
    {name => 'opacity'           , optional => 1, default=>'1'},
    {name => 'fill'              , optional => 0},
    {name => 'stroke'            , optional => 0},
    {name => 'stroke-width'      , optional => 0},
    {name => 'stroke-linecap'    , optional => 0},
    {name => 'stroke-miterlimit' , optional => 0},
    {name => 'stroke-opacity'    , optional => 0},
    {name => 'stroke-dasharray'  , optional => 0},
    {name => 'fill-opacity'      , optional => 1, default=>'1'},
  ];

  return $self;
}

sub style {
  my $self       = shift;
  my $style_text = shift;

  Inkscape::style_($self, $style_text);
}

sub applyGradient {
  my $self               = shift;
  my $gradientDefinition = shift;

  Inkscape::applyGradient_($self, $gradientDefinition, @_);
}

sub write {
  my $self      = shift;
  my $svgFile   = shift;
  my $indent    = shift;


  my $styleText = Inkscape::finalStyle_($self);

  print $svgFile       '  ' x $indent . "<rect\n";
  print $svgFile       '  ' x $indent . "   style=\"$styleText\"\n";
  print $svgFile       '  ' x $indent . "   width=\"$self->{width}\"\n";
  print $svgFile       '  ' x $indent . "   height=\"$self->{height}\"\n";
  print $svgFile       '  ' x $indent . "   x=\"$self->{x}\"\n";
  print $svgFile       '  ' x $indent . "   y=\"$self->{y}\"";
  print $svgFile "\n". '  ' x $indent . "   rx=\"$self->{rx}\"" if exists $self -> {rx};
  print $svgFile "\n". '  ' x $indent . "   ry=\"$self->{ry}\"" if exists $self -> {ry};
  print $svgFile "\n". '  ' x $indent . "   id=\"$self->{id}\" />\n";
}

1;
