# Try, for example:
#
#   perl unnamed_parameter.pl --val2 abc def
#
use strict;
use warnings;

use Getopt::Long;

my $val_1='n/a';
my $val_2='n/a';

my $ok = GetOptions('val1=s' => \$val_1,
                    'val2=s' => \$val_2);

print "ok: $ok\n";
print "val_1: $val_1\n";
print "val_2: $val_2\n";

print "Unnamed parameters:\n";
for my $unnamed_parameter (@ARGV) {
  print "$unnamed_parameter\n";
}
