use warnings;
use strict;

my ($seconds, $minutes, $hour, $day, $month, $year, $weekday, $yearday, $isdts) = localtime(time);

print "seconds: $seconds\n";
print "minutes: $minutes\n";
print "hour:    $hour\n";
print "day:     $day\n";
print "month:   $month\n";    # Note January is month 0, december is month 11!
print "year:    $year\n";
print "weekday: $weekday\n";  # 0 = Sunday, 6 = Saturday 
print "yearday: $yearday\n";  # 0 = January 1st!
print "isdts:   $isdts\n";    # 1 = Daylight saving time

