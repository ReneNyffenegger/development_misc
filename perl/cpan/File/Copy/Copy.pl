use warnings;
use strict;
use File::Copy;

copy($0, "$0.copied");

move ("$0.copied", "$0.moved");
