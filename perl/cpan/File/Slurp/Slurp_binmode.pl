use warnings;
use strict;

use File::Slurp;

my  $temp_file_name = 'c:/temp/slurp_binmode.txt';

write_temp_file();

read_temp_file(0);
read_temp_file(1);


sub read_temp_file  {

    my $with_bin_mode = shift;;
    my $file_text;

    if ($with_bin_mode) {
    #    With binmode necessary to read the \x0d\x0a as such...
        $file_text = read_file($temp_file_name, binmode => ':raw');
    }
    else {
    #    ... otherwise, the \x0a is omitted.
        $file_text = read_file($temp_file_name);
    }


    print "Binmode: $with_bin_mode, length: " . length($file_text) . "\n";

    my @characters = split "", $file_text;
    for my $character (@characters) {
      printf("%02x ", ord($character));
    }

    print "\n\n";
}

sub write_temp_file {

    open (my $file, '>', $temp_file_name);

    binmode($file);

    my $txt = "line one\x{0d}\x{0a}line two";

    print "Going to write " . length($txt) . " bytes\n";

    print $file $txt;

    close $file;

};
