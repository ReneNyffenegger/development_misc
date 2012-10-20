use warnings;
use strict;

use File::Compare;

if (File::Compare::compare_text($ARGV[0], $ARGV[1])) {
  print "$ARGV[0] differs from $ARGV[1]\n";
}
