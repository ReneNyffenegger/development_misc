use strict;
use warnings;

use Test::More tests => 3;
BEGIN {use_ok('Ex2')};


is (&Ex2::add(  3,   5,   1),  9, 'Adding integers');
is (&Ex2::add(5.2, 3.4, 1.4), 10, 'Adding floats/doubles');
