use warnings;
use strict;

use Encoding;

print join "\n", Encode->encodings();

print "\n\n:all\n-----\n\n";
print join "\n", Encode->encodings(':all');
