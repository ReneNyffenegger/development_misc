use warnings;
use strict;

my $time_1 = time;

sleep 5;

my $time_2 = time;

print "Sleep slept for " . ($time_2 - $time_1) . " seconds.\n";
