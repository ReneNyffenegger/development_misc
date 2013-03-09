use warnings;
use strict;

use Date::Parse;

#
#     Convert string representations to 'seconds
#     since Jan 1st 1970'.
#
#     Use Time::localtime to get such string representations.
#     TODO: how are those seconds influenced by
#     local time zones and what not.

print "\n";
print str2time('Thu Jan  1 02:00:00 1970'),"\n";
print str2time('Mon May 19 02:00:00 1997'),"\n";
