use warnings;
use strict;

# The package is declared to be Version 7.1
# This Version number will be returned with $obj->VERSION in useClass.pl
package Class 7.1;


sub new {
  return bless {}, shift;
}

sub some_method {
  my $x=4;
}

1;
