use warnings;
use strict;

use List::Maker;

my $start =   2;
my $end   = 105;
my $step  =  10;

print           "<$start..$end x $step>\n";
print map "  $_\n", <$start..$end x $step>;

print "-" x 10;

print           "< 7r10> [random number between 7 and 10]\n";
print "  ", < 0r10 >, "\n";
