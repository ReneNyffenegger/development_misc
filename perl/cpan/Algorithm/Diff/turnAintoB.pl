use warnings;
use strict;

use Algorithm::Diff;

my @seq_a = qw(       a x b y c z p d q 1 2 3 4 ! 5 6 7);
my @seq_b = qw( a b c a x b y c z       1 2 3 4 ? 5 6 7);

#  This is the array that will contain
#  the same values as @seq_b:
my @seq_B = ();


#
#  new computes the smallest set of additions and deletions
#  necessary to turn the first sequence into the second.
#
my $diff = new Algorithm::Diff(\@seq_a, \@seq_b);

while (my $hunk =   #  A hunk represents a contiguous section
                    #  of items which should be added, deleted
                    #  replaced, or left unchanged.
                    #  ---------------------------------------

           $diff -> Next()

      ) {

     print "\n";

  #  ----------------------------------

     print "$hunk: $hunk ";
   
     print "Diff: ", $diff->Diff(), " ";
   
     print "Same " if $diff->Same();
   
     print "\n";

     my @items_a = $diff -> Items(1);
     my @items_b = $diff -> Items(2);

     push @seq_B, @items_b;

     print "  A: " . (join "-", @items_a) . "\n";
     print "  B: " . (join "-", @items_b) . "\n";
}

print "------------------------\n";

print ((join "-", @seq_b),"\n");
print ((join "-", @seq_B),"\n");

