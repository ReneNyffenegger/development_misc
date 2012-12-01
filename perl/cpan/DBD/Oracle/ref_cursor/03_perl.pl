use DBI;
use DBD::Oracle qw(:ora_types);

use warnings;
use strict;

print "User: ";     my $user = <STDIN>;
print "Password: "; my $pw   = <STDIN>;
print "SID: ";      my $sid  = <STDIN>;

chomp($user, $pw, $sid);

my $dbh = DBI->connect("dbi:Oracle:$sid", $user, $pw);

my $sth = $dbh -> prepare("
declare
  rc sys_refcursor;
begin
  :rc := perl_refcursor_func(:p_a);
end;
");

$sth->bind_param(":p_a", 5);

my $sth_cursor;
$sth->bind_param_inout(":rc", \$sth_cursor, 0, {ora_type => ORA_RSET });

$sth->execute();

while (my $r = $sth_cursor->fetchrow_hashref) {
  print $r->{A}, "\n";
}
