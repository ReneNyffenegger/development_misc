An application that is compiled with `minGw's -mwindows` compiler option does not print
anything to the console by default. Here, this would be [app.c](https://raw.github.com/ReneNyffenegger/development_misc/master/windows/captureStdOutErr/app.c).
See also [compiler options](https://github.com/ReneNyffenegger/development_misc/blob/master/c%2B%2B/gcc/compiler_options/mwindows_mconsole.bat).

On [kaioa.com](http://kaioa.com/node/63), I found a piece of code, that I copied almost unchanged to 
[wrapper.c](https://raw.github.com/ReneNyffenegger/development_misc/master/windows/captureStdOutErr/wrapper.c). This code
is able to capture the strings printed with `printf() `in `app.c` and print them on its own console. 
