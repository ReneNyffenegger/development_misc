@set   FILE=%1
@del  out\%FILE%.svg 2>nul
@perl %FILE%.pl
@perl diff.pl  out\%FILE%.svg %FILE%.expected.svg
