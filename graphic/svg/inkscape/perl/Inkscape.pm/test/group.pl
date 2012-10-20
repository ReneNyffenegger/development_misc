use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('Layer 1');

my $group = $layer_1 -> g;

my $rect  = $group -> rect(230, 200, 220, 220);
my $line1 = $group -> line(240, 210, 200, 200);
my $line2 = $group -> line(240, 410, 200,-200);

$inkscape -> saveAs('out/group.svg');
