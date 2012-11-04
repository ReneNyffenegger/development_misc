use strict;
use warnings;
use Net::FTP;
use File::Basename;

my $ftp;

print "Host: ";           my $host = <STDIN>;
print "Username: ";       my $user = <STDIN>;
print "Password: ";       my $pw   = <STDIN>;
print "Local Filename: "; my $file = <STDIN>; 
print "Remote Path: ";    my $path = <STDIN>;

chomp($host,$user,$pw,$path, $file);

$ftp=Net::FTP->new($host);
$ftp->login($user,$pw) or die "could not login";

$ftp->cwd($path) or die "could not cwd $path";
$ftp->ascii;
$ftp->put($file) or die "could not put $file";
$ftp->site("chmod 600 " . basename($file));

$ftp -> quit;
