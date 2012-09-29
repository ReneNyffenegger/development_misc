@rem
@rem  http://www.adp-gmbh.ch/misc/tools/svn/step_1.html
@rem

@rem 
@rem The repository is a collection of files that make it possible 
@rem to store all commited revisions of files under version control. 
@rem With Subversion, they're all conviniently stored under 
@rem a directory which is created with svnadmin: 
@rem

@svnadmin create --fs-type fsfs %REPO_DIR%

@rem 
@rem Although the repository is opaque and its layout only of 
@rem marginal interest, one might still wonder what it contains: 
@rem

@dir %REPO_DIR%

@rem
@rem svnlook youngest displays the latest (=youngest) revision. 
@rem Up to now, no commit made, revision still 0: 
@rem

@svnlook youngest %REPO_DIR%

@rem
@rem svnlook tree shows the hierarchical layout of what is stored 
@rem in a repository. Up to now: no project added, only tree's 
@rem root here: 
@rem

@svnlook tree %REPO_DIR%
