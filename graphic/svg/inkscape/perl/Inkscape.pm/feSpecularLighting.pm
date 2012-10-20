use warnings;
use strict;
package feSpecularLighting;

my $id = 1;
sub new {
  my     $self = {};
  bless  $self, shift;

  $self  -> {id}    = 'feSpecularLighting' . $id++;

  $self  -> {in}    = 'SourceAlpha';

  $self  -> {color} = "rgb(187,187,187)";

  #  This constant affects the 
  # «phong lightin model»
  $self  -> {constant} = '11.111111111111111'; 

  #  The exponent for the specular term. Larger
  #  is mory «shiny»
  $self -> {exponent}  = '10.912195121951219';

  $self -> {kernelUnitLength} = '10';

  # The value of surfaceScale amplifies the heights
  # of the bump map defined by the input alpha channel.
  $self -> {surfaceScale}     = '5.2356020942407877';


  $self -> {lightSource} = <<"E";
        <feDistantLight
           id="feDistantLight3229"
           azimuth="0" />
E

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile <<"E";
      <feSpecularLighting
         id="$self->{id}"
         in="$self->{in}"
         lighting-color="$self->{color}"
         specularConstant="$self->{constant}"
         specularExponent="$self->{exponent}"
         kernelUnitLength="$self->{kernelUnitLength}"
         surfaceScale="$self->{surfaceScale}">
E

   print $svgFile $self->{lightSource};

print $svgFile "      </feSpecularLighting>\n";
}

1;
