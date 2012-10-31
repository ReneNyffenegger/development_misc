use warnings;
use strict;

use Test::More tests => 2;

BEGIN {use_ok('Ex3')};


my $a = 4;
# mutliply $a by 2, returning it to $a
Ex3::in_out($a);

is ($a, 8, 'in_out() should multiply the argument by 2');

1;
