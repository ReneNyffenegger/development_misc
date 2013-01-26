use warnings;
use strict;

use Time::localtime;

print "\n";

#     Zero seconds after January 1st 1970
print ctime(0), "\n";

#     One Year later
print ctime(  365 * 24*60*60), "\n";

#     10000 days after January 1st 1970:
print ctime(10000 * 24*60*60), "\n";
