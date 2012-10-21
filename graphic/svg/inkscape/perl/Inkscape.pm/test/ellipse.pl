use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer = $inkscape -> layer('Layer 1');

my $ellipse = $layer -> ellipse(280, 530, 115, 42); # x, y, rx, ry

$ellipse -> style ('fill:#ff0000;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1');

$inkscape -> saveAs('out/ellipse.svg');
