@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_7.html
@rem

@rem
@rem The way a branch is created in Subversion is to make a copy. 
@rem

@pushd %SUPPORT_DIR%
@cd project_text

@svn copy file:///%REPO_DIR_FS%/project_text file:///%REPO_DIR_FS%/project_text_R1.0 -m "Rel 1.0"

@svnlook tree %REPO_DIR%

@rem 
@rem Support will use project_text_R1.0 to work on. They don't 
@rem need project_text anymore: 
@rem
@rem TODO: is this true?
@rem

@rmdir /q /s project_text

@rem
@rem However, they need a working copy of project_text_R1. 
@rem

@svn checkout file:///%REPO_DIR_FS%/project_text_R1.0

@popd
