@echo off

rem
rem      rename   foo*.jpg to
rem               bar*.jpg
rem
rem      http://stackoverflow.com/a/3811991/180275
rem

setlocal enabledelayedexpansion
set      old=foo
set      new=bar

for /f "tokens=*" %%f in ('dir /b *.jpg') do (
  set newname=%%f
  set newname=!newname:%old%=%new%!
  move "%%f" "!newname!"
)
