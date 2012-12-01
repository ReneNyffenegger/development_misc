
@rem
@rem   c: ... > batch_parameters.bat batch_parameters.bat
@rem   c: ... > batch_parameters.bat %CD%
@rem 

@echo off
@echo  Remove sorrounding quotation marks:
@echo    %~1
@echo.
@echo.

@echo  Expand to full path
@echo    %~f1
@echo.
@echo.

@echo  Drive letter
@echo    %~d1
@echo.
@echo.

@echo  Path
@echo    %~p1
@echo.
@echo.

@echo  Drive letter and path
@echo    %~dp1
@echo.
@echo.

@echo  Filename
@echo    %~n1
@echo.
@echo.

@echo  Extension
@echo    %~x1
@echo.
@echo.

@echo  Filename and extesion
@echo    %~nx1
@echo.
@echo.

@echo  Short name
@echo    %~s1
@echo.
@echo.

@echo  Attributes
@echo    %~a1
@echo.
@echo.

@echo  Date and Time
@echo    %~t1
@echo.
@echo.

@echo  Size
@echo    %~z1
@echo.
@echo.

@echo  Search in PATH
@echo    %~$PATH:1
@echo.
@echo.
