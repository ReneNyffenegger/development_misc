#use warnings;
#use strict;

use feature 'say';
package LoadAuto;


sub someMethod {
  say @_;
}

sub AUTOLOAD {

  my $unkownMethod = $AUTOLOAD;

  someMethod("Method $unkownMethod is unknown, parameters: ", @_);
}

1;
