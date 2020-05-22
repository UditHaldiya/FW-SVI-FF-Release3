@echo off
rem Time-stamp: <2012-06-27 15:55:45 GE-300010777>

set FFTokenizerpath=C:\FF\TOK\BIN
set dictfile=C:\FF\DDL\standard.dct
set includepath=C:\FF\DDL
set releasepath=C:\FF\release
set imagepath=C:\FF\DDL\HTK
set option4=

IF "%~1"=="" goto Useage
IF "%~1"=="-?" goto Useage
IF "%~2"=="-4" goto Version4

goto Tokenlizing
:Useage


echo   Usage: TokDD DDFile [-4]
echo.
echo  DDFile: DD souce file(ddl). 
echo.
echo      -4: Option for generating compatible generates 4.x 
echo          compatible binary files(.ffo/.sym).
echo.
echo      -?: This help.
goto end

:Version4
Set Option4=-4

:Tokenlizing

if not exist standard.sym copy c:/ff/ddl/standard.sym .

echo BUILDING: %1

%FFTokenizerpath%\ffpretok.exe %Option4% -d %dictfile% -I%includepath% -R %releasepath% -p "%imagepath%" %1 _tmptok

call %FFTokenizerpath%\ff_tok32.exe _tmptok

:end