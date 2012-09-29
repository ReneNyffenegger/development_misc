@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_3.html
@rem

@rem
@rem Franz (who understands german) is given the task of maintaining 
@rem the german subdirectory of project_text. So, he first gets his 
@rem working copy of the german directory (using the svn checkout command)
@rem

@mkdir %FRANZ_DIR%
@pushd %FRANZ_DIR%
@svn checkout file:///%REPO_DIR_FS%/project_text/german

@dir

@rem
@rem Now, he can accomplish his first task: changing Aepfel into Äpfel. 
@rem

@popd
@cscript replace.vbs "%FRANZ_DIR%\german\fruits.txt" "Aepfel" "Äpfel"

@type %FRANZ_DIR%\german\fruits.txt

@rem
@rem The svn status comes in handy to determine the status of 
@rem the files under version control: 
@rem

@svn st %FRANZ_DIR%\german

@rem
@rem The M means modified. 
@rem

@svn commit %FRANZ_DIR%\german\fruits.txt -m "Aepfel without Umlauts"

@rem
@rem The commit creates a new revision. This new revision can now 
@rem later be gotten from the repository. 
@rem

