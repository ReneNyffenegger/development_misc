use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('the name of the layer');

my $rect = $layer_1 -> rect(115, 150, 500, 500,  # x, y, width, height
                            rx=>30, ry=>100);

$rect -> style ('opacity:0.84065935;fill:#e187b5;fill-opacity:0.82010582;stroke:#552f55;stroke-width:40;stroke-linecap:round;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none');

$inkscape -> saveAs('out/rect-round-corners-rx-ry.svg');
