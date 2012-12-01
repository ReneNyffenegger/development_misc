use warnings;
use strict;

use Tie::File;

tie my @lines, 'Tie::File', 'file.txt' or die;

# the magic is not copied if the tied array is copied.
my @lines_copy = @lines;

push @lines_copy, 'Six';

untie @lines;
untie @lines_copy;
