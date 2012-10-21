These perl files are supposed to create svg files that also could have been produced by *inkscape*.

The idea is to first create an inkscape-svg file with these perl files, then to open the created files
in inkscape and do some finetuning to the graphic and then save it to a different file. Finally, the
perl-created and fine-tuned files can be diff'ed.

Very beta, currently!


## Rect


[rect.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect.pl) produces a simple rectangle -
Expectd file: [rect.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect.expected.svg) 

[rect-round-corners.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect-round-corners.pl) 
uses the rect's `ry` attribute for a round corner - Exptected file: [rect-round-corners.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect-round-corners.expected.svg) 
