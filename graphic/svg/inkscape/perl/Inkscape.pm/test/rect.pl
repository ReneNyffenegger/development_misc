use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('the name of the layer');

my $rect = $layer_1 -> rect(10, 100, 50, 50);

$inkscape -> saveAs('out/rect.svg');
