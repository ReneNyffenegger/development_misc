use warnings;
use strict;

use Time::localtime;

#
#     Print String representations of
#     some timestamps.
#
#     Use Date::Parse to convert them
#     back again. TODO: how are those
#     seconds influenced by local time
#     zones and what not.
#

print "\n";

#     Zero seconds after January 1st 1970
print ctime(0), "\n";

#     One second after January 1st 1970
print ctime(1), "\n";

#     One Year later
print ctime(  365 * 24*60*60), "\n";

#     10000 days after January 1st 1970:
print ctime(10000 * 24*60*60), "\n";
