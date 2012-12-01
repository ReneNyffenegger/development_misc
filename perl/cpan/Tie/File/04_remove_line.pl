use warnings;
use strict;

use Tie::File;

tie my @lines, 'Tie::File', 'file.txt' or die;

my $last_line = pop @lines;

print "$last_line removed\n";

untie @lines;
