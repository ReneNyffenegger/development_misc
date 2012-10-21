use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

$inkscape -> zoom(5.6);
$inkscape -> center(145, 711);

my $layer_1 = $inkscape -> layer('Layer 1');

my $circle = $layer_1 -> circle(100, 350, 3); # x, y, r

$circle->style('stroke:#880000;stroke-opacity:1;fill:#00d400;fill-opacity:1');
 
$inkscape -> saveAs('out/circle-dot.svg');
