#   The most simple options are the ones that take no values...
#

use strict;
use warnings;

use Getopt::Long;

my $flag_1 = ''; # turn flag on with --flag_1
my $flag_2 = ''; # turn flag on with --flag_2

GetOptions('flag_1' => \$flag_1, 'flag_2' => \$flag_2);

print "The following flags were set:\n";
print "flag_1: " . ($flag_1 ? "yes" : "no") . "\n";
print "flag_2: " . ($flag_2 ? "yes" : "no") . "\n";
