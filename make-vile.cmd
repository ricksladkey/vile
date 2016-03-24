setlocal
call "%VS140COMNTOOLS%\..\..\vc\bin\amd64\vcvars64.bat"
nmake -f makefile.wnt NODEBUG=yes FLT=yes DBG=yes LEX=reflex TRACE=no CFG=vile VILEDEFS=-DUNICODE %*
