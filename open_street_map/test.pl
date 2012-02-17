use warnings;
use strict;

use OpenStreetMap;

my $osm = new OpenStreetMap;

print $osm -> capabilities;

#print $osm -> map(8.538386, 8.544888, 47.369598, 47.365929);

my $kv = $osm -> keyValueInMap(8.538, 8.539, 47.370, 47.369);

foreach my $k       (keys %{$kv                  }) { print "$k\n";
foreach my $v       (keys %{$kv->{$k}            }) { print "  $v\n";
foreach my $nwr     (keys %{$kv->{$k}->{$v}      }) { print "     $nwr\n";
foreach my $node_id (     @{$kv->{$k}->{$v}{$nwr}}) { print "         $node_id\n"; } } } }
