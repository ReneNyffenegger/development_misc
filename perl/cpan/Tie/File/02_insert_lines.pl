use warnings;
use strict;

use Tie::File;

unlink 'file.txt' unless -e 'file.txt';

tie my @lines, 'Tie::File', 'file.txt' or die;

splice @lines, 2, 0, 'three', 'four';

untie @lines;
