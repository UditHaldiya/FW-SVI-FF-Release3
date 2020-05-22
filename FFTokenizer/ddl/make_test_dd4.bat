@echo off
echo Foundation Fieldbus DD Standard Library
echo (c) 1996-2010 Fieldbus Foundation.  All rights reserved.
echo This will tokenize a test DD which includes all standard DDs
pause Press ctrl-c to stop now; otherwise press a key to continue...

echo fftok -4 ff_test.ddl
call fftok -4 ff_test.ddl

goto END

:END

ECHO DONE
