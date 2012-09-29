@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_5.html
@rem

@rem
@rem In the meantime, an urgent bug fix must be made. It is required 
@rem that honeydews be appended to the fruits.txt. 
@rem
@rem This being a bug fix, it is made by the support team: 
@rem

@mkdir %SUPPORT_DIR%
@pushd %SUPPORT_DIR%

@rem 
@rem The support team maintains both languages, so they pull
@rem project_text rather than project_text\language
@rem

@svn checkout file:///%REPO_DIR_FS%/project_text

@rem
@rem The support team adds the honeydews. Note, elderberry is not 
@rem here because Mike has not yet commited his work. 
@rem

@cd project_text

@echo honeydews>>     english\fruits.txt

@svn diff english\fruits.txt

@rem 
@rem Similarly, the german translation for honeydews (Honigmelonen)
@rem is inserted. Note, Holunderbeere is already in the file because 
@rem Franz has commited his work. 
@rem

@echo Honigmelonen>>   german\fruits.txt

@svn diff german\fruits.txt

@rem
@rem The support team can now commit its work: 
@rem

@svn commit . -m "Support: added honeydews"

@popd
