use warnings;
use strict;

use XSLoaderTest;

my $a = 2.2;
my $b = 1.3;

#  Call the_desired_add_function in 
#  XSLoaderTest.c (via XSLoaderTest.pm and
#  DynaLoader)
my $c = XSLoaderTest::add($a, $b);

print "\n  c = $c\n\n";



