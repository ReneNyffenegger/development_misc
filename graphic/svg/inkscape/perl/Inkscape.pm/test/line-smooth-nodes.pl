use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('Some Layer name');

my $line = $layer_1 -> line_smooth_nodes(115,503,  25,422,  640,558,  420,584,  264,729);

$line -> style('stroke-width:10');

$inkscape -> saveAs('out/line-smooth-nodes.svg');
