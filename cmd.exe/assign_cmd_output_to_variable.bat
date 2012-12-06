@for /f "delims=" %%i in ('hostname') do set hostname=%%i

@echo Hostname is: %hostname%
