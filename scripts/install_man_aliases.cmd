@echo off
setlocal
set "man3dir=%~1"
shift

:next_alias
if "%~1"=="" exit /b 0
for /f "tokens=1,2 delims==" %%A in ("%~1") do (
    copy /Y "%man3dir%\%%B" "%man3dir%\%%A.3" >NUL || exit /b 1
)
shift
goto next_alias
