@set   FILE=%1
@del  out\%FILE%.svg
@perl %FILE%.pl
@perl diff.pl  out\%FILE%.svg %FILE%.expected.svg
