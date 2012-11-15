use warnings;
use strict;

use Data::Compare;

use feature 'say';

my @array_1 = qw(foo bar baz);
my @array_2 = qw(foo bar baz);

say "array_1 differs from array_2" unless Compare(\@array_1, \@array_2);

my @array_3 = qw(foo bar baz);
my @array_4 = qw(bar foo baz);

say "array_3 differs from array_4" if     Compare(\@array_3, \@array_4);
