use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('Layer 1');

my $text = $layer_1 -> text(20, 50, ["Etched text"]);

$text -> style('font-size:40px;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;text-align:start;line-height:125%;writing-mode:lr-tb;text-anchor:start;fill:#00ff7a;fill-opacity:1;stroke:none;font-family:Verdana;-inkscape-font-specification:Verdana Bold');

my $filter = $inkscape -> filter;

my $offset_1 = $filter -> offset( 1,  1);
my $offset_2 = $filter -> offset(-1, -1, in=>'SourceAlpha');

$filter -> composite('out', in=>$offset_2, in2=>$offset_1);
$filter -> gaussianBlur;

$filter -> composite('in', in2=>'SourceGraphic');
$filter -> blend('darken', in2=>'SourceGraphic');

$text -> applyFilter($filter);

$inkscape -> zoom (1.24);
$inkscape -> center(270, 860);

$inkscape -> saveAs('out/filter-etched-text.svg');
