Rem change to the location of the file
cd %~dp0
set gnumake=%~dp0tools/gnumake.exe
gnumake -f auto.mak SHELL=cmd.exe
