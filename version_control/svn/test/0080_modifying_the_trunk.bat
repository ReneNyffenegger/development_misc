@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_8.html
@rem

@rem
@rem Franz and Mike get the task of adding Imbe and Jostaberry. 
@rem

@rem
@rem Mike wants to be sure he has the newest revision: 
@rem

@pushd %MIKE_DIR%
@cd english

@svn update

@echo imbes>>          fruits.txt
@echo jostaberries>>   fruits.txt

@svn commit fruits.txt -m "Added imbe and jostaberry"

@rem
@rem Similarly, Franz is going to change his fruits.txt: 
@rem

@cd %FRANZ_DIR%
@cd german

@rem
@rem Franz wants to be sure he has the newest revision. So he does 
@rem an update: 
@rem

@svn update fruits.txt

@rem
@rem The U signifies that the file was updated. This is because 
@rem the support team has added Holunderbeere which Franz
@rem didn't not yet have in his his working copy. 
@rem

@echo Imben>>         fruits.txt
@echo Jostabeeren>>   fruits.txt

@svn  commit fruits.txt -m "Adding Imben and Jostabeeren"

@popd

