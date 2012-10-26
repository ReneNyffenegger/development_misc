@rem
@rem  Two exe's are created with the »-mwindows« flag.
@rem  One with the entry point »WinMain«, the other with
@rem  the entry point »main«:
@rem
@rem  Both can be started from explorer and cmd.exe (and don't
@rem  seem to exhibit different behaviour from each other).
@rem
@rem  Note: the output of printf() is somehow swallowed.
@rem
@rem
@gcc -mwindows mwindows_mconsole.c -DENTRY="int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)" -o mwindows-WinMain.exe
@gcc -mwindows mwindows_mconsole.c -DENTRY="int main()"                                                                                      -o mwindows-main.exe

@rem
@rem  Two exe's are created with the »-mconsole« flag.
@rem  One with the entry point »WinMain«, the other with
@rem  the entry point »main«:
@rem
@rem  As they're compiled with the -mconsole flag, the 
@rem  required library GDI32 for TextOut() and GetStockObject() 
@rem  must be explicitely stated (»-lgdi32«).
@rem
@rem  Both can be started from explorer and cmd.exe (and don't
@rem  seem to exhibit different behaviour from each other).
@rem
@rem  Note, in contrast to the mwindows-*.exe's,
@rem  these exe's won't »return« control to cmd.exe until
@rem  the started Windos Application is closed.
@rem  Also, when started from explorer, an extra »console
@rem  window« is opened.
@rem  The output of printf() is not swallowed (this is
@rem  probably the reason for the extra console window).
@rem
@gcc -mconsole mwindows_mconsole.c -DENTRY="int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)" -lgdi32 -o mconsole-WinMain.exe
@gcc -mconsole mwindows_mconsole.c -DENTRY="int main()"                                                                                      -lgdi32 -o mconsole-main.exe

