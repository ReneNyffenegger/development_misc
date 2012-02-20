#
#   File from http://download.geofabrik.de/osm (switzerland.osm)
#
use warnings;
use strict;

my $osmFileName = $ARGV[0];

my $line_counter = 0;

my $osmFileOut;

my $osmFileOutCounter = 0;

open (my $osmFileIn , '<', $osmFileName);
open (   $osmFileOut, '>', $osmFileName . '.' . $osmFileOutCounter ++);


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

       print "osmFileOutCounter: $osmFileOutCounter line_counter: $line_counter\n";

       open ($osmFileOut, '>', $osmFileName . '.' . $osmFileOutCounter ++);
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
