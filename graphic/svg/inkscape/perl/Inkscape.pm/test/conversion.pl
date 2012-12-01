use warnings;
use strict;

use Inkscape;
use Conversion;

my $inkscape = new Inkscape;

my $width_a0_mm  = 1189;
my $height_a0_mm =  841;

my $width_ao_px  = Conversion::mm2px($width_a0_mm );
my $height_a0_px = Conversion::mm2px($height_a0_mm);

$inkscape -> width_height($width_ao_px, $height_a0_px, 'px');
$inkscape -> unit('px');

$inkscape -> zoom(0.12345678);
$inkscape -> center(1600, 1300);

my $layer_1 = $inkscape -> layer('Layer 1');

my $line = $layer_1 -> line(0, 0, $width_ao_px, $height_a0_px);

$inkscape -> saveAs('out/conversion.svg');
