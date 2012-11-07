#build Boost with MinGW

As per [my question on stackoverflow](http://stackoverflow.com/questions/13256788/building-boost-1-52-with-mingw).

First, `bjam` needs to be built:

    C:\boost_1_52_0> cd tools\build\v2\engine
    C:\boost_1_52_0> build.bat mingw

Then, `bjam` is used to build `boost`:

    C:\boost_1_52_0> copy bin.ntx86\bjam.exe ..\..\..\..

    C:\boost_1_52_0> cd ..\..\..\..

    C:\boost_1_52_0> bjam --toolset=gcc

    C:\boost_1_52_0> @rem bjam --toolset=gcc --butomplete stage
    C:\boost_1_52_0> @rem bjam   toolset=gcc --butomplete stage
    
A simpler but identical way is:

    C:\boost_1_52_0> bootstrap.bt
    C:\boost_1_52_0> bjam --toolt


The libraries are then placed into **state/lib**.
