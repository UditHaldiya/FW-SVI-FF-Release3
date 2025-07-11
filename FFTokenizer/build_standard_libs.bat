@echo off

rem Time-stamp: <2012-06-27 15:00:50 GE-300010777>
cls

if exist c:\FF\DDL goto build

echo Please copy the DDL subdirectory from the 3.70.zip to c:\FF folder manually.
pause
goto end


:build
echo. 

echo This procedure will build whole Standard Library into c:/ff/release
echo directory, The full Library includes both of Version 4 and 5. 
echo.
echo It will take about twenty minuts.

pause press a key to start building...

if not exist c:\ff\release xcopy c:\ff\ddl\release c:\ff\release /S /Y /I /Q


set TOK_RELEASE_DIR=c:/FF/release/
copy /Y ddl\standard.sym standard.sym
cd c:\ff\ddl

call make_all_dd4.bat
call make_all_dd4_lib2.bat
call make_all_dd5.bat
call make_all_dd5_lib2.bat
call make_test_dd4.bat
call make_test_dd5.bat


echo ===================================================
echo  The library has been built.
echo ===================================================

:end
cd c:\ff

