use strict;
use warnings;

package XSLoaderTest;


require XSLoader;

my  $dllNameWithoutDLL = 'theDesired';
our $VERSION = '0.01';

#
# Load the DLL...
# This will call the function boot_theDesired
# in XSLoaderTest.c
#
XSLoader::load($dllNameWithoutDLL, $VERSION);

# Since this package does not define
# a sub 'add', DynaLoader will call the
# function the_desired_add_function (in 
# XSLoaderTest.c). That function is found
# because it is "registered" with the 
# XS macro newXS.

1;
