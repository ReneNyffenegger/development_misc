use warnings;
use strict;

use Tie::File;

unlink 'file.txt' if -e 'file.txt';

tie my @lines, 'Tie::File', 'file.txt' or die;

push @lines, 'one';
push @lines, 'two';
push @lines, 'five';
push @lines, 'six';

untie @lines;
