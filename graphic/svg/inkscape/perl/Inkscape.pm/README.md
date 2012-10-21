These perl files are supposed to create svg files that also could have been produced by *inkscape*.

The idea is to first create an inkscape-svg file with these perl files, then to open the created files
in inkscape and do some finetuning to the graphic and then save it to a different file. Finally, the
perl-created and fine-tuned files can be diff'ed.

Very beta, currently!


# Tests

The `test` folter contains a few perl script that can be used to test the functionality. Each perl script produces an svg-file into the `test\out` folder and
compares the produced file with the corresponding `.expected.svg` file.

These tests are run with the [run_test.bat](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/run_test.bat) file.

## Rect


[rect.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect.pl) produces a simple rectangle -
Expected file: [rect.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect.expected.svg) 

[rect-round-corners.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect-round-corners.pl) 

[rect-round-corners-rx-ry.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect-round-corners-rx-ry.pl) 
is mostly the same thing as `rect-round-corners`, but uses both attributes, `rx` and `ry` - Expected file: [rect-round-corners.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rect-round-corners-rx-ry.expected.svg) 

## Circle

Inkscape seems not too comfortable with the svg `<circle>` tags. Probably because they cannot produce ellipses and arcs. But as Inkscape can read `<circle>` tags,
they're also included here:

[cirle-dot.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/cirle-dot.pl) produces a black dot -
Expected file: [rect.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/cirle-dot.expected.svg) 
