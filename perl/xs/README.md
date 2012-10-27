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
