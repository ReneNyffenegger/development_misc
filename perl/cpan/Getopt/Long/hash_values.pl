# hash_values.pl --translation one=eins --translation two=zwei
use strict;
use warnings;

use Getopt::Long;


my %translations = ();

GetOptions('translation=s%' => \%translations);

for my $english_word (keys %translations) {
  print "$english_word was translated into $translations{$english_word}\n";
}
