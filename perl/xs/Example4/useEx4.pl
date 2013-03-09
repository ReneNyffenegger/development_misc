#
#   perl  -Ilib -Iblib\arch useEx4.pl
#
use warnings;
use strict;

use Ex4;

use feature 'say';

my $a = 4.1;
my $b = 5.2;

say "$a + $b = ", Ex4::add($a, $b);
