use strict;
use warnings;

use Date::Manip;

#                          # Prints something like
parse_date('today'     );  # 2012102500:00:00 (on Oct 25th 2012).
parse_date('yesterday' );  # 2012102400:00:00 (on Oct 25th 2012).
parse_date('08/28/1970');  # 1970082800:00:00
parse_date('8am'       );  # 2012102508:00:00
parse_date('8:13am'    );  # 2012102508:00:00
parse_date('8:13:22am' );  # 2012102508:00:00
parse_date('now'       );  # 2012102508:00:00

#

my $now   = ParseDate('now');
my $later = ParseDate('8:13am');

#  %s extracts seconds since Jan 1st 1970. So it's possible to get the difference 
#  of two dates in seconds:
print "Difference between $now and $later: " . (UnixDate($later, "%s") - UnixDate($now, "%s")) . " seconds\n"; 

sub parse_date {
  my $txt = shift;

  printf("%-20s %s\n", "$txt:", ParseDate($txt));
}
