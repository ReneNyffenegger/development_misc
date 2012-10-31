use warnings;
use strict;

use Encode;

my $auml = "\x{c3}\x{89}";

printf("UTF-8  : %s\n", unpack('H*', $auml));

Encode::from_to($auml, 'utf8', 'latin-1');

printf("Latin-1: %s\n", unpack('H*', $auml));
