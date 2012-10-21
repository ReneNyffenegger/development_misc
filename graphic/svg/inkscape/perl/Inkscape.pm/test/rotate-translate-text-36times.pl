use warnings;
use strict;
use Inkscape;

my $inkscape = new Inkscape('a4');

my $layer = $inkscape -> layer('Layer 1');

for my $deg (map {$_ * 10} (0 .. 35)) {

  my $text = $layer->text(0, 0, ["Rotation, then translation"]);
  
  $text -> style ('font-size:56px');
  
  $text -> rotate($deg * (3.14159265358 / 180));
  $text -> translate(100, 400);

}

$inkscape -> saveAs('out/rotate-translate-text-36times.svg');
