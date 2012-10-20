use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('the name of the layer');

my $text = $layer_1 -> text(20, 50, ["This is the text's first line", "second line"]);

$inkscape -> saveAs('out/text.svg');
