use warnings;
use strict;

use Time::Local;


# Get seconds since system epoch for
#
#     Oct 25th 2012, 7:45am
#

my $seconds =    0;
my $minutes =   45;
my $hour    =    7;

my $day     =   25;
my $month   =    9;  # Note! October is the 10th month, but timelocal expectes 9 for October!
my $year    = 2012;

print timelocal($seconds, $minutes, $hour, $day, $month, $year), "\n";
