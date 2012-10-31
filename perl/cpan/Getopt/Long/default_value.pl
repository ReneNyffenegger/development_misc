use strict;
use warnings;

use Getopt::Long;

my $default_value='DEF';
my $override = $default_value;

GetOptions('override=s' => \$override);

print "\n";

if ($override eq $default_value) {
    print "Value was not overridden, use --override if needed\n";
}
else {
    print "Default value overridden with $override\n";
}
