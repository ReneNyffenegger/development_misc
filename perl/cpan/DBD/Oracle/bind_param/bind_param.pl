use warnings;
use strict;

use feature 'say';

use lib '..';
use OracleUserPwDb;

use DBI;
use DBD::Oracle;

my $dbh = DBI->connect(OracleUserPwDb::conn()) or die;

$dbh -> do ('create table tq84_bind_param(a number)');

my $sth = $dbh -> prepare (q{

  begin
    insert into tq84_bind_param values (:i);
  end;
});

$sth -> bind_param(':i', 42); $sth -> execute;
$sth -> bind_param(':i', 99); $sth -> execute;

# --

$sth = $dbh -> prepare(q{select a from tq84_bind_param});
$sth -> execute;

while (my $row = $sth -> fetchrow_hashref) {
  say $row->{A};  
}

$dbh -> do ('drop table tq84_bind_param');
