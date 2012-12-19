use warnings;
use strict;

use feature 'say';

use Digest::MD5 qw(md5_hex);

say md5_hex('something, something else or the same');
