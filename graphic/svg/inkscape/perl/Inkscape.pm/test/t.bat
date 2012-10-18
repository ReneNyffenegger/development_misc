@set   FILE=%1
@del  out\%FILE%.svg
@perl %FILE%.pl
@fc   out\%FILE%.svg %FILE%.expected.svg
