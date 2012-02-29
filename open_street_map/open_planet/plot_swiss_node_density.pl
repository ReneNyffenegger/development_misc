#   Plots a density image with the values created by the
#   script 'swiss_node_density.sql' (found in the table
#  'swiss_node_density'.

use warnings;
use strict;

use DBI;
use GD;

my $width_km     = 348;
my $height_km    = 220;
my $pixel_per_km =   4;  # be sure to take same value as in 'swiss_node_density.sql'

my $dbh = DBI -> connect('DBI:mysql:osm', 'osmuser', $ENV{'OSM_PASSWORD'}) or die;

#  In order to logarithmically scale the color density, we first determine
#  the maximum density for a pixel
my $sth_max_density = $dbh -> prepare ('select max(c) max_density from swiss_node_density') or die;
   $sth_max_density -> execute or die;
my $max_density = $sth_max_density->fetchrow_hashref->{max_density};

#  The value determined here ($log_) can later be used to
#  scale a pixel's density such that 

my $log_ = log($max_density ** (1/255));
#  -------------------------------------

my $sth_pixels = $dbh -> prepare ('select x, y, c from swiss_node_density');
$sth_pixels -> execute;

#  Aren't color palettes so-passé?
GD::Image -> trueColor(1);

my $plot = new GD::Image($width_km*$pixel_per_km, 220*$pixel_per_km); 
while (my $pixel = $sth_pixels -> fetchrow_hashref) {

  #  note: log(0) is not defined, but we don't expect
  #  the value 0 for a pixel as the table swiss_node_density
  #  was created with the count() aggregate function, and
  #  this doesn't produce an entry for a pixel without any
  #  nodes in it:
  my $logarithmic_density = int(log($pixel->{c}) / $log_);

  $plot->setPixel($pixel->{x}, $height_km*$pixel_per_km - $pixel->{y}, $plot->colorResolve(0, 0, $logarithmic_density));
}

open (my $plot_out, '>', 'swiss_node_density.png');
binmode $plot_out;

print $plot_out $plot -> png;

close $plot_out;
