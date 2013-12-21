setlocal
del *.obj
call "%VS110COMNTOOLS%\..\..\vc\bin\amd64\vcvars64.bat"
set INCLUDE=%INCLUDE%;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\include
nmake -f makefile.wnt DBG=yes FLT=yes LEX=reflex TRACE=no CFG=vile VILEDEFS=-DUNICODE %*
