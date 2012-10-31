use warnings;
use strict;

use Test::More tests => 2;

BEGIN {use_ok('Ex4')};


my $a = 4.1;
my $b = 5.2;

is (Ex4::add($a, $b), $a+$b, "$a+$b should be " . ($a+$b));

1;
