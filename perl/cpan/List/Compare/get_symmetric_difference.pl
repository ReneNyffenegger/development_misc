use warnings;
use strict;

use List::Compare;

# ----------------------------------------------

my @u = qw(  abc def ghi jkl mno      );
my @v = qw(      def ghi jkl mno pqr  );

my $c = new List::Compare(\@u, \@v);

print join "\n", $c->get_symmetric_difference;

print "\n\n";

# ----------------------------------------------

my @w = qw(  abc abc def ghi jkl mno      );
my @x = qw(          def ghi jkl mno pqr  );

my $d = new List::Compare(\@w, \@x);

print join "\n", $d->get_symmetric_difference;

# ----------------------------------------------
