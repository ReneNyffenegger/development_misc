@set REPO_DIR=c:\temp\svn_test

@REM
@REM The repository with forward slashes:
@REM
@set REPO_DIR_FS=c:/temp/svn_test


@set PROJ_DIR=c:\temp\svn_proj

@set FRANZ_DIR=c:\temp\svn_franz
@set MIKE_DIR=c:\temp\svn_mike
@set SUPPORT_DIR=c:\temp\svn_support

@if exist %REPO_DIR%     rmdir /s /q %REPO_DIR%
@if exist %PROJ_DIR%     rmdir /s /q %PROJ_DIR%
@if exist %FRANZ_DIR%    rmdir /s /q %FRANZ_DIR%
@if exist %MIKE_DIR%     rmdir /s /q %MIKE_DIR%
@if exist %SUPPORT_DIR%  rmdir /s /q %SUPPORT_DIR%

@mkdir %REPO_DIR%
@mkdir %PROJ_DIR%
