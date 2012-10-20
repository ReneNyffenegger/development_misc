#
#   For a reason unbeknowest to me, the «bubble effect» disappears
#   as the image is zoomed in.
#
use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('Layer 1');

my $text = $layer_1 -> text(20, 50, ["Bubble text"]);

$text -> style('font-size:40px;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;text-align:start;line-height:125%;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;font-family:Verdana;-inkscape-font-specification:Verdana Bold');

my $filter = $inkscape -> filter;

$filter -> specularLighing;
$filter -> gaussianBlur;
$filter -> composite('atop', in2=>'SourceGraphic');

$text -> applyFilter($filter);

$inkscape -> zoom (1.4);
$inkscape -> center(115, 910);

$inkscape -> saveAs('out/filter-bubble-text.svg');
