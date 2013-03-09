#Algorithm

##Algorithm::Diff

[LCS.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Algorithm/Diff/LCS.pl): the Longest Common Subsequence.

[turnAintoB.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Algorithm/Diff/turnAintoB.pl)

#Config

[run.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Config/run.pl).

#Digest

##Digest::MD5

[run.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Digest/MD5/run.pl).

[addfile.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Digest/MD5/addfile.pl) calculates the digest for a file rather than for a string.

#Data

##Data::Compare

[run.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Data/Compare/run.pl).

See also [List::Compare](https://github.com/ReneNyffenegger/development_misc/tree/master/perl/cpan/List/Compare).

#Date

##Date::Manip

[Manip.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Date/Manip.pl). 

##Date::Parse

[Parse.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Date/Parse.pl) converts
string representations of a time (such as *Thu Jan  1 02:00:00 1970*) to seconds since Jan 1st 1970.

#DBD

##DBD::Oracle

[all.sql](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/DBD/Oracle/ref_cursor/all.sql) starts
[01_table.sql](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/DBD/Oracle/ref_cursor/01_table.sql) to create a table and
[02_function.sql](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/DBD/Oracle/ref_cursor/02_function.sql) to create a function that
selects from the table via a *ref cursor* that the function returns.
[03_perl.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/DBD/Oracle/ref_cursor/03_perl.pl) has an anonymous block that
uses the function to get the ref cursor.
[04_perl.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/DBD/Oracle/ref_cursor/04_perl.pl) does basically the same thing, but
without the function.


#Encode

[from_utf8_to_latin1.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Encode/from_utf8_to_latin1.pl)

[list_encodings.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Encode/list_encodings.pl)

#File

##File::Copy

[Copy.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Copy/Copy.pl)

##File::Path

[rmtree.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Path/rmtree.pl) demonstrates how to use rmtree to
remove a directory.

##File::Slurp

[Slurp.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Slurp/Slurp.pl)

[Slurp_binmode.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Slurp/Slurp_binmode.pl)

##File::Spec

[Spec.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Spec/Spec.pl)

##File::Temp

[Temp.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/File/Temp/Temp.pl)

#Getopt


[default_value.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/default_value.pl)

[first.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/first.pl)

[hash_values.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/hash_values.pl)

[multiple_values.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/multiple_values.pl)

[no_values.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/no_values.pl)

[unnamed_parameter.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Getopt/Long/unnamed_parameter.pl)

#List

##List::Compare

[get_symmetric_difference.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/List/Compare/get_symmetric_difference.pl)

See also [Data::Compare](https://github.com/ReneNyffenegger/development_misc/tree/master/perl/cpan/Data/Compare)

##List::Maker

[run.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/List/Maker/run.pl)

#MP3

##MP3::Tag

[Tag.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/MP3/Tag/Tag.pl)

#Net

##Net::FTP

[ftp.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Net/FTP/ftp.pl)

#Scalar

##Scalar::Util

[blessed.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Scalar/Util/blessed.pl)

#Term

[ANSIColor01.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Term/ANSIColor.01.pl) and
[ANSIColor02.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Term/ANSIColor.02.pl). 

#Tie

##Tie::File

Modify files through an array.

[01_create_file.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Tie/File/01_create_file.pl),
[02_insert_file.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Tie/File/02_insert_lines.pl),
[03_modify_lines.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Tie/File/03_modify_lines.pl) and
[04_remove_line.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Tie/File/04_remove_line.pl).

[05_copy_array.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Tie/File/05_copy_array.pl) shows that the tied magic
is not copied to another array.

#Time

##Time::Local

Exports (among others) `timelocal` which is sort of the inverse of
[localtime.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/functions/localtime.pl).

See [Local.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Time/Local.pl).

##Time::localtime

[localtime.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/language/Time/localtime.pl) demonstrates
using `cimte` to get a string representation of dates.


#UNIVERSAL

`UNIVERSAL` is the *base class* for all classes (or packages).

[useClass.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/UNIVERSAL/useClass.pl) demonstrates that 
[Class.pm](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/UNIVERSAL/Class.pm) is inherited from UNIVERSAL and
that UNIVERSAL provides the four methods `can`, `DOES`, `isa` and `VERSION`.


#utf8

[is_utf8.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/utf8/is_utf8.pl)

#Win32

[GetShortPathName.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/Win32/GetShortPathName.pl)

#XML

[first.pl](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/XML/Parser/first.pl) reads and parses
[first.xml](https://raw.github.com/ReneNyffenegger/development_misc/master/perl/cpan/XML/Parser/first.xml).
