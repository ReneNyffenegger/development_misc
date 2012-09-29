@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_9.html
@rem

@rem 
@rem In the meantime, it was discovered that there is a bug 
@rem in release 1. All fruits are written in the plural from 
@rem except elderberry which is in the singular form. This 
@rem must be changed. 
@rem

@cscript replace.vbs %SUPPORT_DIR%\project_text_R1.0\english\fruits.txt elderberry    elderberries
@cscript replace.vbs %SUPPORT_DIR%\project_text_R1.0\german\fruits.txt  Holunderbeere Holunderbeeren

@pushd %SUPPORT_DIR%
@cd project_text_R1.0
@cd english

@rem
@rem Now, let's examine the difference: 
@rem

@svn diff fruits.txt

@cd ..\german

@svn diff fruits.txt

@cd ..

@svn commit . -m "Correcting wrong singular form"

@popd
