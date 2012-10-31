use warnings;
use strict;

use MP3::Tag;

if (@ARGV < 1) {
  print "\n  specify Filename\n\n";
  exit;
}

my $mp3_filename = $ARGV[0];

my $mp3 = MP3::Tag->new($mp3_filename);

my ($title, $track, $artist, $album, $comment, $year, $genre) = $mp3->autoinfo();

print "title:   $title\n";
print "track:   $track\n";
print "artist:  $artist\n";
print "album:   $album\n";
print "comment: $comment\n";
print "year:    $year\n";
print "genre:   $genre\n";

$mp3->close();
