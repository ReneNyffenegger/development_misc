use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer_1 = $inkscape -> layer('Layer');

my $gradient = $inkscape -> gradient('linear', [ ['#db079a', 1  ],
                                                 ['#245d9a', 0.6]
                                               ]);

my $rect = $layer_1 -> rect(50, 50, 650, 950);

$rect -> applyGradient($gradient, 72, 65, 698, 997);

$rect -> style("stroke:#e80023;stroke-width:5");

$inkscape -> saveAs('out/rect-fill-gradient.svg');
