#
#   Extract all sql statements that are found in the files 
#   within and under a directory (that is specified with
#   the first script argument).
#
#   The second argument defines the file that is printed.
#
#   Currently finds only SQL statements that actually
#   are SELECT statements.
#
#   ----------------------------------------------------------
use warnings;
use strict;
use File::Find;

die "Two arguments required" unless @ARGV == 2;

my $search_root = $ARGV[0];
my $output_file = $ARGV[1];

die "$search_root is not a directory" unless -d $search_root;
die "$output_file alredy exists"      if     -e $output_file;

open (my $output_file_h, ">", $output_file);

find (\&search_in_file, $search_root);

close $output_file_h;

sub search_in_file {

    my $file_name = $File::Find::name;

    return unless -f $file_name;

    open (my $file_h, "<", $file_name);


    my $in_sql = 0;

    #  If an SQL is found, print also the filename where it was
    #  found, but be sure to only print the filename at most once.
    my $file_name_printed = 0;

    while (<$file_h>) {
    
      if ($in_sql) {
    
        if (  m/^((\w|\s|#|\$|:|\.|'|=|"|<|>|\(|\)|\%|"|\*|,|\!|\-|\+|\/)+)/  ) {
          print $output_file_h $&;
        }
        else {
          print $output_file_h "\n\n";
          $in_sql = 0;
        }
    
      }
      else {
    
        #    Currently: search for "select" sql statements only. They must not
        #    be preceeded by a grant (such as 'grant select on TABLE to USER').
        if ( m/((?<!grant )select(\w|\s|#|\$|:|\.|'|=|"|<|>|\(|\)|\%|"|\*|,|\!|\-|\+|\/)+)/gi) {

          unless ($file_name_printed) {
            print $output_file_h "File $file_name {\n";
            $file_name_printed=1;
          }

          print $output_file_h $&;
          $in_sql = 1;
        }
    
      }
    
    }

    if ($file_name_printed) {
      print $output_file_h "}\n";
    }

    close $file_h;
}
