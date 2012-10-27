use warnings;
use strict;

use File::Path 'rmtree';

if (-d 'TestRmTreeDir') {
  print "removing TestRmTreeDir\n";
  removeDirectory();
}
else {
  print "creating TestRmTreeDir\n";
  createDirectory();
}


sub removeDirectory {
  rmtree 'TestRmTreeDir';
}

sub createDirectory {

  mkdir 'TestRmTreeDir';
  
  open (my $fh, '>', 'TestRmTreeDir/File.txt') or die;
  
  print $fh 'Some text goes into the file';
  
  close $fh;

}
