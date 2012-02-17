use warnings;
use strict;

use OpenStreetMap;

my $osm = new OpenStreetMap;

print $osm -> capabilities;

print $osm -> map(8.538386, 8.544888, 47.369598, 47.365929);
