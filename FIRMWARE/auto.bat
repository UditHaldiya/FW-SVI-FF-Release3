Rem change to the location of the file
cd %~dp0
tools\gnumake.exe -f auto.mak SHELL=cmd.exe 
