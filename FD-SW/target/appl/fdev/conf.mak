#target/appl/fdev

SUBDIR := src
ISUBDIR := inc ..\fbif\inc ..\..\..\base\appl\ffbl\inc 

#A kludge because no time to mess with directories now
ISUBDIR +=..\..\..\nvram
