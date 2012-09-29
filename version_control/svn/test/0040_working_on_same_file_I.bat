@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_4.html
@rem

@rem
@rem The project manager decides that there needs to be a fruit 
@rem whose english name starts with e: elderberry. 
@rem
@rem Mike, the maintainer for the english part, changes that in the 
@rem english file:
@rem
@rem Of course, he needs his own working copy, just like Franz does: 
@rem

@mkdir %MIKE_DIR%
@pushd %MIKE_DIR%
@svn checkout file:///%REPO_DIR_FS%/project_text/english

@rem
@rem This is of course a hack to simulate adding a text line:
@rem

@del                  english\fruits.txt
@echo apples>         english\fruits.txt
@echo bananas>>       english\fruits.txt
@echo cherries>>      english\fruits.txt
@echo dates>>         english\fruits.txt
@echo elderberry>     english\fruits.txt
@echo figs>>          english\fruits.txt
@echo grapes>>        english\fruits.txt

@popd

@rem
@rem Of course, Franz will have to modify (that is: to add 
@rem Holunderbeere) the german text as well: 
@rem

@pushd %FRANZ_DIR%
@cd german

@rem 
@rem TODO Umlaut wrong with dos and windows and what do I knw
@rem

@del                   fruits.txt
@echo Äpfel>           fruits.txt
@echo Bananen>>        fruits.txt
@echo Kirschen>>       fruits.txt
@echo Datteln>>        fruits.txt
@echo Holunderbeere>>  fruits.txt
@echo Feigen>>         fruits.txt
@echo Trauben>>        fruits.txt

@svn diff fruits.txt

@rem 
@rem Franz commits his work. Note, Mike did not. 
@rem

@svn commit fruits.txt -m "Added Holunderbeere (for elderberry)"

@popd
