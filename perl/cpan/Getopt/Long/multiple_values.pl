# multiple_values.pl --value=foo --value=bar --value=more
use strict;
use warnings;

use Getopt::Long;


my @values = ();

GetOptions('value=s' => \@values);

if (@values) {
  print "\nThe following values were found:\n  " . join ("\n  ", @values) . "\n";
}
else {
  print "\n\n--value=value_1 --value=value_2 ... --value=value_n\n\n";
}

