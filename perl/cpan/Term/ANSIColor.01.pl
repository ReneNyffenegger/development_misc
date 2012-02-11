#
#   How is it possible to have 'bold' colors for the background as well?
#

use Win32::Console::Ansi;
use Term::ANSIColor;

use strict;
use warnings;

print "\n";

my @predefined_colors = qw(black  red  green  yellow  blue  magenta  cyan  white);

for my $foreground_color (@predefined_colors) {
for my $bold ('clear ', 'bold ') {
for my $background_color (@predefined_colors) {

  print color "$bold$foreground_color";
  print color "on_" . $background_color;
  printf " %8s ", $foreground_color;

# bright colors not always supported:
# print color "bright_$predefined_color";
# print "bright $predefined_color\n";

} print "\n" }} 

print color "reset";

print "\n";
