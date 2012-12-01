These perl files are supposed to create svg files that also could have been produced by *inkscape*.

The idea is to first create an inkscape-svg file with these perl files, then to open the created files
in inkscape and do some finetuning to the graphic and then save it to a different file. Finally, the
perl-created and fine-tuned files can be diff'ed.

Very beta, currently!


# Tests

The `test` folter contains a few perl script that can be used to test the functionality. Each perl script produces an svg-file into the `test\out` folder and
compares the produced file with the corresponding `.expected.svg` file.

These tests are run with the [run_test.bat](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/run_test.bat) file.

## Line

[line.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line.pl) produces a stright line -
Expected file: [line.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line.expected.svg) 

[line-zig-zag.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line-zig-zag.pl) produces zig zag line using
the Layer's `line_M` method -
Expected file: [line-zig-zag.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line-zig-zag.expected.svg) 

[line-smooth-nodes.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line-smooth-nodes.pl)
creates a line with «smooth» edges. That is, as though a line would have been drawn with the Shift+F6 tool («*Draw Bezier curves and straight lines*») and then each node (except the
first and the last one) would have made smooth
(F2, then «*make selected node smooth*»).

the Layer's `line_M` method -
Expected file: [line-zig-zag.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/line-zig-zag.expected.svg) 

# Conversion

[convers.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/conversion.pl) converts the sizes in millimeters of
an A0 sheet to its corresponding pixel units. Uses [Conversion.pm](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/Conversion.pm) -
Expected file: [conversion.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/conversion.expected.svg) 

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

## Ellipse

[cirle-dot.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/ellipse.pl) produces an ellipse as though it had been drawn
with the arc tool - Expected file: [rect.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/ellipse.expected.svg) 

## Transformation (Matrix)

Uses [Matrix.pm](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/Matrix.pm) to create transformations.


[rotate-text-10deg.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-text-10deg.pl) rotates a text
10 degrees. - Expected file: [rotate-text-10deg.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-text-10deg.expected.svg) 

[rotate-text-36times.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-text-36times.pl) is similar to
`rotate-text-10deg`, but it creates 36 texts, each rotated 10 degrees more than the previous one
10 degrees. - Expected file: [rotate-text-36times.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-text-36times.expected.svg) 

[rotate-translate-text-36times.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-translate-text-36times.pl) and
[translate-rotate-text-36times.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/translate-rotate-text-36times.pl) both
translate (move) and rotate a text 36 times, but in different orders, thus producing different output (because order matters for matrix multiplications).
Expected files: 
[rotate-translate-text36times.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/rotate-translate-text-36times.expected.svg) and
[translate-rotate-text36times.expected.svg](https://raw.github.com/ReneNyffenegger/development_misc/master/graphic/svg/inkscape/perl/Inkscape.pm/test/translate-rotate-text-36times.expected.svg).
