use Inkscape;

my $inkscape = new Inkscape;

$inkscape -> a4_portrait;

my $layer_1 = $inkscape -> layer('the name of the layer');

my $line = $layer_1 -> line(10, 100, 50, -50);

$inkscape -> saveAs('out/line.svg');
