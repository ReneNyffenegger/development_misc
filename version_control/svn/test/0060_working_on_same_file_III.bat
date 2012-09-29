@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_6.html
@rem

@rem
@rem Now, Mike wants to commit his work, too. 
@rem

@pushd %MIKE_DIR%

@cd english

@svn commit fruits.txt -m "Added elderberry"

@rem
@rem Mike gets a 
@rem    svn: Commit failed (details follow):
@rem    svn: File '/project_text/english/fruits.txt' is out of date
@rem This means that there is a new version in the repository which
@rem he would overwrite with his commit. That should be (and is)
@rem prevented by Subversion. 
@rem
@rem Therefore, Mike needs to update the file first: 
@rem

@svn update fruits.txt

@rem
@rem The G indicates that the file was merged. That is, the support 
@rem team's changes (adding honeydews) are now in Mike's copy as 
@rem well.
@rem

@type fruits.txt

@rem
@rem Now, Mike is ready to commit his work: 
@rem

@svn commit fruits.txt -m "Added elderberry"


@popd
