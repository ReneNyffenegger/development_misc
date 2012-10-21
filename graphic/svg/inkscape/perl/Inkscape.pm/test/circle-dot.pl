use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

$inkscape -> zoom(5.6);
$inkscape -> center(145, 711);

my $layer_1 = $inkscape -> layer('Layer 1');

my $line = $layer_1 -> circle(100, 350, 3); # x, y, r
 
$inkscape -> saveAs('out/circle-dot.svg');
