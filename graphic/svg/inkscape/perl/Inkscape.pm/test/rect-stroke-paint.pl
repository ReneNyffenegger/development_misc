use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('Layer');

my $rect = $layer_1 -> rect(10, 100, 50, 50);

$rect -> style('stroke:#9dff00;stroke-width:20');

$inkscape -> saveAs('out/rect-stroke-paint.svg');
