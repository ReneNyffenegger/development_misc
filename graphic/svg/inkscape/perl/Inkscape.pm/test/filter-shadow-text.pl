use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('Layer 1');

my $text = $layer_1 -> text(20, 50, ["Shadow text"]);

$text -> style('font-size:40px;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;text-align:start;line-height:125%;writing-mode:lr-tb;text-anchor:start;fill:#f78a08;fill-opacity:1;stroke:none;font-family:Verdana;-inkscape-font-specification:Verdana Bold');

my $filter = $inkscape -> filter;

             $filter -> gaussianBlur(stdDeviation => 1.5, in => 'SourceAlpha');
my $offset = $filter -> offset(2,2);
             $filter -> merge($offset, 'SourceGraphic');

$text -> applyFilter($filter);

$inkscape -> zoom (1.24);
$inkscape -> center(70, 860);

$inkscape -> saveAs('out/filter-shadow-text.svg');
