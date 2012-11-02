use warnings;
use strict;

use feature 'say';

use Config;

#     Textual summary of major perl configuration
#     values.
print Config::myconfig();
print '-' x 80, "\n";

# print Config::config_sh();
# print '-' x 80, "\n";
#
# print Config::config_re('???');
# print '-' x 80, "\n";


say "libpth:   ", $Config{'libpth'};
say "path_sep: ", $Config{'path_sep'};
