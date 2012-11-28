use warnings;
use strict;

use feature 'say';

# use lib '.';
use OracleUserPwDb;

use DBI;
use DBD::Oracle;

my $dbh = DBI->connect(OracleUserPwDb::conn()) or die;

my $sth = $dbh -> prepare ('select null a from dual union all select 1 a from dual');

$sth -> execute;

while (my $row = $sth -> fetchrow_hashref) {
  if (defined $row->{A}) {
    say $row->{A}
  }
  else {
    say '<null>';
  }
}

