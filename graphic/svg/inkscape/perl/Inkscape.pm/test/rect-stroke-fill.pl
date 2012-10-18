use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('Layer');

my $rect = $layer_1 -> rect(50, 50, 300, 300);

$rect -> style('opacity:0.5;fill:#dbd89a;stroke:#e7c12b;stroke-width:40');

$inkscape -> saveAs('out/rect-stroke-fill.svg');
