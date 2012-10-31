use strict;
use warnings;

use Getopt::Long;


use vars qw($opt);
$opt = { "help" => \&Usage, };

Getopt::Long::GetOptions(
    $opt,
    "help",
    "flag_1=s",
    "other_flag=s",
);

print("\n");

for my $option_given (qw{flag_1 other_flag}) {
  if (exists $opt->{$option_given}) {
    printf("Option %-10s: %s\n", $option_given, $opt->{$option_given} );
  }
}

print("\n");


sub Usage {
  print STDERR <<"USAGE";

Usage: perl $0 [options]

Possible options are:

  --flag_1=<a flag>      Use <a flags> for the flag you want 
                         to specify.

  --other_flag=<other>   Use <other> as you may wish.

USAGE
}
