use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer = $inkscape -> layer('Layer 1');

my $text = $layer->text(27,507, ["Rotate text 10 degrees"]);

$text -> style ('font-size:56px');

$text -> rotate(10 * (3.14159265358 / 180));

$inkscape -> saveAs('out/rotate-text-10deg.svg');
