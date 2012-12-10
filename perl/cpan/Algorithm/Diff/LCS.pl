#
#   LCS: Longest Common Subsequence.
#

use warnings;
use strict;

use Algorithm::Diff;

my @seq_1 = qw(       a x b y c z p d q);
my @seq_2 = qw( a b c a x b y c z      );

my @lcs = Algorithm::Diff::LCS(\@seq_1, \@seq_2);

print "\n  ";
print join " ", @lcs;
print "\n";
