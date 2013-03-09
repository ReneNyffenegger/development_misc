#
#   Calculate the MD5 digest of a file,
#   in this case of $0 (that is: addfile.pl)
#
use warnings;
use strict;

use Digest::MD5;

my $md5 = new Digest::MD5;

open (my $fh, '<', $0) or die;
binmode $fh;

$md5->addfile($fh);

print $md5->hexdigest, "\n";

close $fh;
