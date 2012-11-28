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

    :out := :in * 5;

  end;
});

$sth -> bind_param      (':in' , 11);

my $out;
$sth -> bind_param_inout(':out', \$out, 2);

$sth -> execute;

say "5 * 11 = ", $out;
