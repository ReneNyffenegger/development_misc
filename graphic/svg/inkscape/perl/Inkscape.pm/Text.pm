package Text;

my $id = 1;
sub new {

  my $self = {};
  bless $self, shift;

  $self->{x} = shift;
  $self->{y} = shift;

  $self -> {textLines} = shift;

  $self->{style}->{'font-size'}                    = '20px';
  $self->{style}->{'font-style'}                   = 'normal';
  $self->{style}->{'font-variant'}                 = 'normal';
  $self->{style}->{'font-weight'}                  = 'normal';
  $self->{style}->{'font-stretch'}                 = 'normal';
  $self->{style}->{'text-align'}                   = 'start';
  $self->{style}->{'line-height'}                  = '100%';
  $self->{style}->{'letter-spacing'}               = '0px';  # TODO: letter-spacing and
  $self->{style}->{'word-spacing'}                 = '0px';  # word-spacing should probably be optional
  $self->{style}->{'writing-mode'}                 = 'lr-tb';
  $self->{style}->{'text-anchor'}                  = 'start';
  $self->{style}->{'fill'}                         = '#000000';
  $self->{style}->{'fill-opacity'}                 = '1';
  $self->{style}->{'stroke'}                       = 'none';
  $self->{style}->{'font-family'}                  = 'Sans';
  $self->{style}->{'-inkscape-font-specification'} = 'Sans';

  $self->{id} = "text" . $id++;

  $self -> {valid_styles} = [
    {name => 'font-size'                     , optional => 0},
    {name => 'font-style'                    , optional => 0},
    {name => 'font-variant'                  , optional => 0},
    {name => 'font-weight'                   , optional => 0},
    {name => 'font-stretch'                  , optional => 0},
    {name => 'text-align'                    , optional => 0},
    {name => 'line-height'                   , optional => 0},
    {name => 'letter-spacing'                , optional => 0},
    {name => 'word-spacing'                  , optional => 0},
    {name => 'writing-mode'                  , optional => 0},
    {name => 'text-anchor'                   , optional => 0},
    {name => 'fill'                          , optional => 0},
    {name => 'fill-opacity'                  , optional => 0},
    {name => 'stroke'                        , optional => 0},
    {name => 'filter'                        , optional => 1, default=>''},
    {name => 'font-family'                   , optional => 0},
    {name => '-inkscape-font-specification'  , optional => 0},
  ];

  return $self;
}

my $textSpanId=1;
sub write {
  my $self      = shift;
  my $svgFile   = shift;
  my $indent    = shift;

  my $styleText = Inkscape::finalStyle_($self);

  print $svgFile '  ' x $indent . "<text\n";
  print $svgFile '  ' x $indent . "   xml:space=\"preserve\"\n";
  print $svgFile '  ' x $indent . "   style=\"$styleText\"\n";
  print $svgFile '  ' x $indent . "   x=\"$self->{x}\"\n";
  print $svgFile '  ' x $indent . "   y=\"$self->{y}\"\n";
  print $svgFile '  ' x $indent . "   id=\"$self->{id}\"\n";
  print $svgFile '  ' x $indent . "   sodipodi:linespacing=\"" . $self->{style}->{'line-height'} . "\"";

  print $svgFile "\n". '  ' x $indent . "   " . $self->{transformation}->tag if exists $self->{transformation};
  
  print $svgFile ">";

  my $x = $self->{x};
  my $y = $self->{y};
  for my $textLine (@{$self->{textLines}}) {

    print $svgFile "<tspan\n";

    print $svgFile '  ' x $indent . "     sodipodi:role=\"line\"\n";
    print $svgFile '  ' x $indent . "     id=\"tspan" . $textSpanId++ . "\"\n";
    print $svgFile '  ' x $indent . "     x=\"$x\"\n";
    print $svgFile '  ' x $indent . "     y=\"$y\">" . $textLine . "</tspan>";

    $y += int ($self->{style}->{'font-size'} * int($self->{style}->{'line-height'})/100);
  }

  print $svgFile "</text>\n";
}

sub style {
  my $self       = shift;
  my $style_text = shift;

  Inkscape::style_($self, $style_text);
}

sub applyFilter {
  my $self   = shift;
  my $filter = shift;

  Inkscape::applyFilter_($self, $filter, @_);
}

# Transformations {

sub rotate {
  my $self  = shift;
  my $alpha = shift;

  Inkscape::rotate_($self, $alpha);
}

# }

1;
