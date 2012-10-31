use warnings;
use strict;

use File::Slurp;
use File::Temp qw/tempfile tempdir/;

# A Tempfile is created.
# This temp file will survive the end
# of this process. e.g. it won't be
# deleted.
my ($fh, $filename) = tempfile;

print $fh "This tempfile was written by $0\n";

print "$filename written\n";

# ---

# Another Tempfile is created. 
# this one will be deleted when the object goes out of scope.
# In this script: when the process ends.
my $tmp_file_will_be_deleted = File::Temp->new();

printf "%s will be deleted\n", $tmp_file_will_be_deleted->filename;

# TODO: For some reason, the string written into the
#       tempfile won't be there...
print $tmp_file_will_be_deleted "some content of tempfile\nthat will be deleted\n";


print "reading file:\n" . read_file($tmp_file_will_be_deleted->filename);

# Sleeping, so that the existence of the file can be checked.
sleep 20;
