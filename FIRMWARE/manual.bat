Rem change to the location of the file
cd %~dp0
gnumake -f auto.mak appserverc=%1 SHELL=cmd.exe
