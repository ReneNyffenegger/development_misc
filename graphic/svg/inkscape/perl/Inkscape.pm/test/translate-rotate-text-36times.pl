use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer = $inkscape -> layer('Layer 1');

for my $deg (map {$_ * 10} (0 .. 35)) {

  my $text = $layer->text(0,0, ["Translation, then rotation"]);
  
  $text -> style ('font-size:56px');
  
  $text -> translate(100, 400);
  $text -> rotate($deg * (3.14159265358 / 180));
}

$inkscape -> saveAs('out/translate-rotate-text-36times.svg');
