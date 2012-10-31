use 5.016001;
use ExtUtils::MakeMaker;

WriteMakefile(
    NAME              => 'Ex4',
    VERSION_FROM      => 'lib/Ex4.pm',
    OBJECT            => '$(O_FILES)'
);
