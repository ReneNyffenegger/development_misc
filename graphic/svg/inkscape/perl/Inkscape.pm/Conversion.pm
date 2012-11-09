use warnings;
use strict;

package Conversion;

sub mm2in { # Millimeter to Inch
    my $mm = shift;

    return $mm/25.4;
}

sub in2px { # Inch 2 Pixel
    my $in = shift;

    # 90 seems to be the default "Dots per Inch" for
    # SVG.
    return 90*$in;
}

sub mm2px { # Millimeter to Pixel
    my $mm = shift;
    my $in = mm2in($mm);

    return in2px($in);
}

1;
