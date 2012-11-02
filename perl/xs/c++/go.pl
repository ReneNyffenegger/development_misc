#
#   http://www.johnkeiser.com/perl-xs-c++.html
#

use warnings;
use strict;

system ('rmdir /s /q Perl2CppTest');

# ---

system ('h2xs -A -n Perl2CppTest');

# ---

open (my $xs, '<', 'Perl2CppTest/Perl2CppTest.xs');
my @xs_lines = <$xs>;
close $xs;

open ($xs, '>', 'Perl2CppTest/Perl2CppTest.xs');

print $xs "#ifdef __cplusplus\n";
print $xs "extern \"C\" {\n";
print $xs "#endif\n";

print $xs $_ for @xs_lines;

print $xs "#ifdef __cplusplus\n";
print $xs "}\n";
print $xs "#endif\n";

close $xs;
