#Example1

This example is inspired by [perldoc](http://perldoc.perl.org/perlxstut.html#EXAMPLE-1).

I tried to reduce it to the bare minimum.

On Windows:

    perl Makefile.pl
    dmake

    perl test.pl

As I was unable to create running `t/test.t`, I just created the regular perl script
[test.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example1/test.pl) to check whether
`Ex1` is working.

`Ex::func()` calls the c programlet defined in [Ex1.xs](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example1/Ex1.xs):

    void
    func()
      CODE:
        printf("Ex1::func is called!\n");


#Example2

The interesting piece is in [Ex2.xs](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example2/Ex2.xs). It defines the function `add`: 

    double 
    add(double d1, double d2, double d3)
      CODE:
        RETVAL = d1 + d2 + d3;
      OUTPUT:
        RETVAL

`add` is used by [use_Ex2.xs](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example2/use_Ex2.xs):

    use Ex2;
    print "2.2 + 3.3 + 4.4 = " . Ex2::add(2.2, 3.3, 4.4) . "\n";

#Example3

[Ex3.xs](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example3/Ex3.xs) has the `OUTPUT:` section so that parameters can be *in-out* parameters.


#Example4

Call the function `add` (declared in [add.h](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example4/add.h) and defined in
[add.c](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example4/add.c)).

The [Ex4.xs](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example4/Ex4.xs) now has a

    #include "add.h"

[Makefile.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/xs/Example4/Makefile.pl) now passes

    OBJECT            => '$(O_FILES)'

to `WriteMakefile`.



