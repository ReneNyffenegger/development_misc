#language

The folder [language](https://github.com/ReneNyffenegger/development_misc/tree/master/perl/language#readme) contains examples for the perl language itself. The examples are filled as
I have time to write a small scriptlet.

#CPAN

The folder [cpan](https://github.com/ReneNyffenegger/development_misc/tree/master/perl/cpan#readme) contains examples for Perl modules found on CPAN. The examples are filled as 
I discover them and have time to write a small scriptlet.

#Misc

##Installing a module with strawberry

The following installs `Date::Manip`

    perl -MCPAN  -e shell
    install Date::Manip
    exit

##What make program was used to configure and build Perl?

    perl -V:make
