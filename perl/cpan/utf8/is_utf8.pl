#  See also
#   ..\..\..\..\meta\character_sets\perl\readme.txt

use warnings;
use strict;


my $string_1 = "No Smiley";        # UTF8 Flag will not be set!
my $string_2 = "Smiley \x{263A}";  # UTF8 Flag will be set!

print "is_utf8: " . utf8::is_utf8($string_1) . "\n";
print "is_utf8: " . utf8::is_utf8($string_2) . "\n";
