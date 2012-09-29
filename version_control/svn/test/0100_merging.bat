@rem
@rem http://www.adp-gmbh.ch/misc/tools/svn/step_10.html
@rem

@rem
@rem Franz and Mike want to apply the changes of the bugfix 
@rem (elderberry=>elderberries) into their working copy: 
@rem

@rem
@rem When the project_text_R1 directory was copied into the 
@rem repository, the revision 6 was created. When the bugfix was
@rem commited, revision 9 was created. So, we have to apply (merge) 
@rem all changes between revision 6 and 9 that happened in the 
@rem project_text_R1 directory. 
@rem

@pushd %MIKE_DIR%
@cd english

@svn merge -r6:9 file:///%REPO_DIR_FS%/project_text_R1.0/english .

@rem
@rem If Mike now looks at his file, he will see the bugfix: 
@rem

@type fruits.txt

@rem
@rem So, he can commit this new file: 
@rem

@svn commit . -m "Applied bugfix in Rel 1"

@rem
@rem Franz does the very thing on his part: 
@rem

@cd %FRANZ_DIR%
@cd german


@svn merge -r6:9 file:///%REPO_DIR_FS%/project_text_R1.0/german .

@svn commit . -m "Applied bugfix in Rel 1"

@popd
