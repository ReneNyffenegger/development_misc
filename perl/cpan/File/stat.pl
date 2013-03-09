use warnings;
use strict;

use File::stat;
use Time::localtime;

my $datetime_string = ctime(stat('stat.pl')->mtime);

print $datetime_string;
