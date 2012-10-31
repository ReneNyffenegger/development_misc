# use 5.010001;

use ExtUtils::MakeMaker;

WriteMakefile(
    NAME              => 'Ex2',
    VERSION_FROM      => 'Ex2.pm', # finds $VERSION
    LIBS              => [''], # e.g., '-lm'
    DEFINE            => '-DEX2_DEFINE=\"Defined_In_Makefile.pl\"',
    INC               => '-I.',
);
