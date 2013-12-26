setlocal
call "%VS110COMNTOOLS%\..\..\vc\bin\amd64\vcvars64.bat"
set INCLUDE=%INCLUDE%;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\include
nmake -f makefile.wnt NODEBUG=yes FLT=yes DBG=yes LEX=reflex TRACE=no CFG=vile VILEDEFS=-DUNICODE EDITORCONFIG_HOME="C:\Program Files\editorconfig" %*
