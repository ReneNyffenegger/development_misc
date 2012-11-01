use warnings;
use strict;

use Scalar::Util 'blessed';

# --

my $var_1 = 'Hello World';
my $var_2 = {hello=>'world'};
my $var_3 = ['hello', 'world'];

# --

bless $var_2, "SomeClass";

# --

print "var_1 is undefined\n" unless defined blessed $var_1;
print "var_3 is undefined\n" unless defined blessed $var_3;

print blessed $var_2, "\n"
