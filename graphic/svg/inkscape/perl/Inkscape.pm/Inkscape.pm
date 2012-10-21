use warnings;
use strict;
package Inkscape;

use File::Basename;
use G;
use GradientDefinition;
use GradientUsage;
use Filter;
use Matrix;

sub new {
  my $self = {};

  bless $self, shift;

  for my $arg (@_) {
    $self -> a4_portrait if $arg eq 'a4';
  }

  $self -> {version} = '0.48.2 r9819';

  return $self;
}

sub width_height {
  my $self      = shift;

  my $width  = shift;
  my $height = shift;

  my $units  = shift;

  $self -> {width}   = $width  . $units;
  $self -> {height}  = $height . $units;
}

sub center {
  my $self      = shift;

  $self -> {cx} = shift;
  $self -> {cy} = shift;
}

sub a4_portrait {
  my $self      = shift;

  $self -> width_height(210, 297, 'mm');
  $self -> unit('mm');

  $self -> center(-95.714286, 520);

  $self -> zoom (0.35);
}

sub zoom {
  my $self        = shift;

  $self -> {zoom} = shift;
}

sub unit {
#   
#   units can be: mm, in, pt, px, pc, m, mm, cm
#
#   1 in ~ 90 px
#   1 in ~ 72 pt

  my $self      = shift;

  $self -> {unit} = shift;
}

sub saveAs {
  my $self         = shift;
  my $dirFileName  = shift;

  my $fileName     = basename($dirFileName);


  open (my $svgFile, ">", $dirFileName) or die "Couldn't open $dirFileName";
  print $svgFile <<"EFG";
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   xmlns:dc="http://purl.org/dc/elements/1.1/"
   xmlns:cc="http://creativecommons.org/ns#"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:svg="http://www.w3.org/2000/svg"
   xmlns="http://www.w3.org/2000/svg"
EFG

  if (exists $self -> {gradientDefinitions}) {
    print $svgFile "   xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n";

  }

  print $svgFile <<"EFG";
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   width="$self->{width}"
   height="$self->{height}"
   version="1.1"
   inkscape:version="$self->{version}"
   sodipodi:docname="$fileName"
   id="what-is-this-id-good-for">
EFG

  if (exists $self->{gradientDefinitions} or exists $self->{filters}) {

    print $svgFile "  <defs\n";
    print $svgFile "     id=\"defs999\">\n";

    for my $grad (@{$self->{gradientDefinitions}}) {
       $grad -> write($svgFile);
    }

    # This loop does not write the layers itself. It
    # writes gradient definitions that might be applicable
    # for a layer.
    #
    # The layers are written further down.
    for my $layer (@{$self->{layers}}) {
      for my $elem (@{$layer->{elems}}) {

        if (exists $elem->{gradient}) {
          $elem->{gradient}->write($svgFile);
        }
      }
    }

    for my $filter(@{$self->{filters}}) {
      $filter->write($svgFile);
    }

    print $svgFile "  </defs>\n";
  }
  else {

    print $svgFile "  <defs\n";
    print $svgFile "     id=\"defs999\" />\n";
  }

print $svgFile <<"EFG";
  <sodipodi:namedview
     id="base"
     pagecolor="#ffffff"
     bordercolor="#666666"
     borderopacity="1.0"
     inkscape:pageopacity="0.0"
     inkscape:pageshadow="2"
     inkscape:zoom="$self->{zoom}"
     inkscape:cx="$self->{cx}"
     inkscape:cy="$self->{cy}"
     inkscape:document-units="$self->{unit}"
     inkscape:current-layer="$self->{currentLayer}"
     showgrid="false"
EFG

  print $svgFile <<"ABC";
     inkscape:window-width="1440"
     inkscape:window-height="838"
     inkscape:window-x="-8"
     inkscape:window-y="-8"
     inkscape:window-maximized="1" />
  <metadata
     id="metadata7">
    <rdf:RDF>
      <cc:Work
         rdf:about="">
        <dc:format>image/svg+xml</dc:format>
        <dc:type
           rdf:resource="http://purl.org/dc/dcmitype/StillImage" />
        <dc:title />
      </cc:Work>
    </rdf:RDF>
  </metadata>
ABC

  # Write the layers and their content.
  foreach my $layer (@{$self->{layers}}) {
    $layer->write($svgFile, 1);
  }

  print $svgFile "</svg>\n";
}

sub style_ {
#   «static method», called by Rect, Path, Text...  .style()

  my $elem             = shift;
  my $style_text       = shift;

  my %validStyles = map {$_->{name}, 1} @{$elem->{valid_styles}};

  my @styles = split ';', $style_text;

  for my $style (@styles) {
    my ($style_name, $style_value) = split ':', $style;

    if (exists $validStyles{$style_name}) {
      $elem->{style}->{$style_name} = $style_value;
    }
    else {
      die "$elem does not support style $style_name";
    }
  }
}

sub finalStyle_ {
#   «static method», called by Rect, Path, Text...  .write()

  my $elem = shift;

  my $styleText = '';

  for my $style (@{$elem->{valid_styles}}) {

      if ($style->{optional}) {
        if (exists $elem -> {style} -> {$style->{name}}) {
          if ($elem -> {style} -> {$style->{name}} ne $style->{default}) {
            $styleText .= ';' if $styleText;
            $styleText .= $style->{name} . ':' . $elem->{style} -> {$style->{name}}
          }
        }
      }
      else {
        $styleText .= ';' if $styleText;
        $styleText .= $style->{name} . ':' . $elem->{style} -> {$style->{name}};
      }
  }

  return $styleText;
}

###

sub layer {
  my $self      = shift;

  my $layerName = shift;

  my $layer     = new G;

  $layer -> makeLayer($layerName);

  push @{$self->{layers}}, $layer;

  $self -> {currentLayer} = $layer->{id};

  return $layer;
}

sub gradient {
    my $self = shift;

    my $gradient = new GradientDefinition(@_);

    push @{$self -> {gradientDefinitions}}, $gradient;

    return $gradient;
}

sub applyGradient_ {
  my $elem               = shift;
  my $gradientDefinition = shift;

  $elem -> {gradient} = new GradientUsage($gradientDefinition, @_);

  $elem -> style("fill:url(#$gradientDefinition->{type}Gradient$elem->{gradient}->{id})");
}

sub applyFilter_ {
  my $elem   = shift;
  my $filter = shift;

  $elem -> style('filter:url(#' . $filter->{id} . ')');
}

sub filter {
  my $self = shift;

  my $filter = new Filter(@_); # @_ is most probably the empty list ().

  push @{$self->{filters}}, $filter;

  return $filter;
}

# transformations {

sub transformation_ {

  my $elem = shift;

  return if exists $elem->{transformation};

  $elem -> {transformation} = new Matrix;
}

sub rotate_ {

  my $elem  = shift;
  my $alpha = shift;

  transformation_($elem);
  
  $elem -> {transformation} -> rotate($alpha);

}

# }
1;
