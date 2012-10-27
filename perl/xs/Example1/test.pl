# I didn't find out how to write a test-case in the 't' directory...
# 
# Therefore the "test" must be executed manually.
# The string printed is found in Ex1.xs
#
BEGIN {
  use Cwd; 
#
# Prevent error Messages
# ---------------------
#
#   Can't locate Ex1.pm in @INC
    push @INC, getcwd() . '/lib';
#
#   Can't locate loadable object for module Ex1 in @INC
    push @INC, getcwd() . '/blib/arch/auto/Ex1';
}

use Ex1;

Ex1::func();
