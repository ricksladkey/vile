setlocal
call "%VS140COMNTOOLS%\..\..\vc\bin\amd64\vcvars64.bat"
nmake -f makefile.wnt DBG=yes FLT=yes LEX=reflex TRACE=no CFG=winvile VILEDEFS=-DUNICODE %*
