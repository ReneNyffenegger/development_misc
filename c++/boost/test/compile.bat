@set BOOST_VERSION=1_52
@set BOOST_ROOT=C:\git_hub_renenyffenegger\development_misc\c++\boost\boost_1_52_0

@del link_to_library.exe

@g++ link_to_library.cpp -I%BOOST_ROOT% -L%BOOST_ROOT%/stage/lib -lboost_regex-mgw46-mt-%BOOST_VERSION% -o link_to_library.exe

@link_to_library.exe
