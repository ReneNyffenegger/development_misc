@rem
@rem  http://www.adp-gmbh.ch/misc/tools/svn/step_2.html
@rem

@rem
@rem  A new project (in form of a directory (and possibly subdirectories)) is added to the repository: 
@rem

@mkdir %PROJ_DIR%\project_text

@mkdir %PROJ_DIR%\project_text\english
@mkdir %PROJ_DIR%\project_text\german

@echo apples>     %PROJ_DIR%\project_text\english\fruits.txt
@echo bananas>>   %PROJ_DIR%\project_text\english\fruits.txt
@echo cherries>>  %PROJ_DIR%\project_text\english\fruits.txt
@echo dates>>     %PROJ_DIR%\project_text\english\fruits.txt
@echo figs>>      %PROJ_DIR%\project_text\english\fruits.txt
@echo grapes>>    %PROJ_DIR%\project_text\english\fruits.txt

@echo Aepfel>     %PROJ_DIR%\project_text\german\fruits.txt
@echo Bananen>>   %PROJ_DIR%\project_text\german\fruits.txt
@echo Kirschen>>  %PROJ_DIR%\project_text\german\fruits.txt
@echo Datteln>>   %PROJ_DIR%\project_text\german\fruits.txt
@echo Feigen>>    %PROJ_DIR%\project_text\german\fruits.txt
@echo Trauben>>   %PROJ_DIR%\project_text\german\fruits.txt

@rem 
@rem svn import actually adds a directory tree to the repository: 
@rem

@svn import %PROJ_DIR% file:///%REPO_DIR_FS% -m "initial import"

@rem
@rem  Again, let's see what's in the repository: 
@rem

@svnlook tree %REPO_DIR%

@rem
@rem  Everything that's needed is stored in the repository. 
@rem  The directory that was used for the import can safely be destroyed: 
@rem

@rmdir /s /q %PROJ_DIR%
