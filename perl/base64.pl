use warnings;
use strict;

use MIME::Base64;

if (@ARGV != 1) {
  print "\n";
  print "  Specifiy filename to encode or decode\n";
  print "\n";
  print "  If filename ends in .64, the file is decoded and\n";
  print "  saved to file without .64\n";
  print "  Otherwise, the file is encoded and saved to file\n";
  print "  with .64 suffix.\n";
  print "\n";
  exit;
}

my $file_name = shift @ARGV;
my $file_name_out;
my $chunk_size;
my $modus;

if (($file_name_out) = ($file_name =~ /(.*)\.64$/)) {
   $modus      = 'decode';
   $chunk_size =  77;
}
else {
   $file_name_out = "$file_name.64";
   $modus      = 'encode';
   $chunk_size =  57;
}

if (-e $file_name_out) {
  print "\n";
  print "  $file_name_out already exists, I don't want to\n";
  print "  overwrite it.\n";
  print "\n";
  exit;
}

unless (-f $file_name) {
  print "\n";
  print "  $file_name doesn't seem to exist.\n";
  print "\n";
  exit;
}

open (my $in_h , '<', $file_name    );
open (my $out_h, '>', $file_name_out);

binmode $in_h;
binmode $out_h;

my $buf;
# TODO chunk_size might be multiplied with an
#      appropriate value.
#      The documentation suggests 60 for this
#      value.
while (read($in_h, $buf, $chunk_size)) {
  if ($modus eq 'decode') {
     print $out_h decode_base64($buf);
  }
  else {
     print $out_h encode_base64($buf);
  }
}


close $in_h;
close $out_h;

print "$file_name was ${modus}d to $file_name_out\n";
