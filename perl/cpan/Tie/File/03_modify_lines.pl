use warnings;
use strict;

use Tie::File;

tie my @lines, 'Tie::File', 'file.txt' or die;

# make first letter of each line uppercase;
s/(.)/\U$1/ for @lines;

untie @lines;
