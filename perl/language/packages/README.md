[Ex1.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/packages/Ex1.pl) demonstrates that "top level" (that is not
part of a sub) is executed when the package is `use`d. [Ex1.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/packages/Ex1.pl)
uses [Ex1.pm](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/packages/Ex1.pm) which, in turn, prints (that is: `say`s)
*This line is printed when the package is 'used'*.

[LoadAuto.pm](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/packages/LoadAuto.pm) demonstrates that "unknown package methods"
are resolved in a method named `AUTOLOAD`. The name of the unknown method is passed in the variable `$AUTOLOAD`. `LoadAuto.pm` is used by
[LoadAuto.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/packages/LoadAuto.pl).

