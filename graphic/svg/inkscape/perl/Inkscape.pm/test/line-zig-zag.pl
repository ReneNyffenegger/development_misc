use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('Layer 1');

my $line = $layer_1 -> line_M( 82,66,
                              620,176,
                               97,312,
                              550,457,
                              179,586,
                              618,708,
                              127,832,
                              611,931);

$line -> style('stroke-width:10');

$inkscape -> zoom (0.5);
$inkscape -> saveAs('out/line-zig-zag.svg');
