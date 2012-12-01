@ set PERLPATH=C:\tools\strawberry\perl

@ gcc -I%PERLPATH%\lib\CORE -s -c -O2     -fno-strict-aliasing -mms-bitfields  -I%PERLPATH%\lib\CORE   XSLoaderTest.c

@ dlltool --def XSLoaderTest.def --output-exp dll.exp

@ g++ -o theDesired.dll -mdll -s -L"%PERLPATH%\lib\CORE" -L"C:\tools\strawberry\c\lib" XSLoaderTest.o %PERLPATH%\lib\CORE\libperl516.a   dll.exp 

@ perl useXSLoaderTest.pl

@ del XSLoaderTest.o
@ del dll.exp
@ del theDesired.dll
