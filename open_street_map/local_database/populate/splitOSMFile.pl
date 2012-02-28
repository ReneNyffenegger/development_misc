#   
#   One of the frustrating experiences when I tried to load an OpenPlanet OSM
#   File was that it seemed to be too large to be handled by Perl and or
#   the expat XML Parser.
#
#   Therefore, the OSM XML file is now split into smaller parts that 
#   should pose no problem to Perl/expat/XML.
#
use warnings;
use strict;

my $osmFileName = $ARGV[0];

my $line_counter = 0;

my $osmFileOut;

my $osmFileOutCounter = 0;

open (my $osmFileIn , '<', $osmFileName);

my $outOsmFileName = $osmFileName . '.' . ++$osmFileOutCounter;
open (   $osmFileOut, '>', $outOsmFileName);
print "$outOsmFileName\n";

while (my $line = <$osmFileIn>) {


  $line =~ s/version="\d+"//;
  $line =~ s/changeset="\d+"//;
  $line =~ s/user="[^"]*"//;
  $line =~ s/uid="\d+"//;
  $line =~ s/timestamp="[^"]*"//;
  $line =~ s/^ *//;

  if ($line_counter++ > 100000) {

    if ($line =~ m#</node> *$# or $line =~ m#</way> *$# or $line =~ m#</relation> *$#) #
    {

       print $osmFileOut $line;

       print $osmFileOut "\n</osm>\n";

       close $osmFileOut;

       $outOsmFileName = $osmFileName . '.' . ++$osmFileOutCounter;
       open (   $osmFileOut, '>', $outOsmFileName);
       print "$outOsmFileName\n";

       print $osmFileOut "<?xml version='1.0' encoding='UTF-8'?>\n";
       print $osmFileOut "<osm version=\"0.6\" generator=\"pbf2osm\">\n";

       $line_counter = 0;
    }
    else {
      print $osmFileOut $line
    }
  }
  else {
      print $osmFileOut $line
  }

}

close $osmFileOut;
