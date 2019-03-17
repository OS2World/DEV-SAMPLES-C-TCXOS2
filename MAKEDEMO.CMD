echo off
echo .                                                                      .
echo *=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
echo  Copyright (c) 1987-1991, Innovative Data Concepts. All Rights Reserved
echo .                                                                      .
echo Building Demo Program ...
:
if [%TCXL_C%]==[Z] goto ZORTECH
if [%TCXL_C%]==[z] goto ZORTECH
if [%TCXL_C%]==[J] goto JPI
if [%TCXL_C%]==[j] goto JPI
if [%TCXL_C%]==[W] goto WATCOM
if [%TCXL_C%]==[w] goto WATCOM
if [%TCXL_C%]==[6] goto MQ6
if [%TCXL_C%]==[5] goto MQ5
echo No TCXL_C Environment Variable Found
goto NOENV
:
:MQ6
if [%1]==[M] goto MSC6
if [%1]==[m] goto MSC6
if [%1]==[Q] goto QC25
if [%1]==[q] goto QC25
goto NOARGS
:
:MQ5
if [%1]==[M] goto MSC5
if [%1]==[m] goto MSC5
if [%1]==[Q] goto QC2
if [%1]==[q] goto QC2
:
:NOARGS
echo .
echo ERROR: No Command Line Parameters Given For MSC/QC Compile
echo .
echo         Compiler            Syntax
echo  ----------------------------------------------
echo         MSC 6.0            MakeDemo M
echo         MSC 5.1            MakeDemo M
echo         QC  2.5            MakeDemo Q
echo         QC  before 2.5     MakeDemo Q
echo         Zortech C++        MakeDemo
echo         TopSpeed C/C++     MakeDemo
echo         Watcom C           MakeDemo
echo .
:
:NOENV
echo Set Environment Variables With The Command SET VAR=VALUE
echo .
echo Compiler   MSC 5.1       MSC 6.0   ZORTECH  TopSpeed  Watcom
echo        QC before 2.5     QC 2.5
echo SET TCXL_C=  5             6         Z        J        W
goto ND
:
:MSC6
CL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\UserDemo.c demo\MenuDemo.c demo\EntrDemo.c demo\DemoMisc.c demo\UserDemo.def LIB\TCXLM6S.LIB >TCXLDemo.Log
CL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\Mid_Demo.c demo\Win_Demo.c demo\Str_Demo.c demo\DemoMisc.c demo\Mid_Demo.def LIB\TCXLM6S.LIB >>TCXLDemo.Log
goto DONE
:
:MSC5
CL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\UserDemo.c demo\MenuDemo.c demo\EntrDemo.c demo\DemoMisc.c demo\UserDemo.def LIB\TCXLM5S.LIB >TCXLDemo.Log
CL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\Mid_Demo.c demo\Win_Demo.c demo\Str_Demo.c demo\DemoMisc.c demo\Mid_Demo.def LIB\TCXLM5S.LIB >>TCXLDemo.Log
goto DONE
:
:QC25
QCL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\UserDemo.c demo\MenuDemo.c demo\EntrDemo.c demo\DemoMisc.c demo\UserDemo.def LIB\TCXLM6S.LIB >TCXLDemo.Log
QCL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\Mid_Demo.c demo\Win_Demo.c demo\Str_Demo.c demo\DemoMisc.c demo\Mid_Demo.def LIB\TCXLM6S.LIB >>TCXLDemo.Log
goto DONE
:
:QC2
QCL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\UserDemo.c demo\MenuDemo.c demo\EntrDemo.c demo\DemoMisc.c demo\UserDemo.def LIB\TCXLM5S.LIB >TCXLDemo.Log
QCL /AS /G2s /W3 /Ot /Zp /Lp /IINC /I. demo\Mid_Demo.c demo\Win_Demo.c demo\Str_Demo.c demo\DemoMisc.c demo\Mid_Demo.def LIB\TCXLM5S.LIB >>TCXLDemo.Log
goto DONE
:
:WATCOM
WCL /fpi /i=inc /ms /oaxt /s /w4 /i=. /lp demo\UserDemo.c demo\MenuDemo.c demo\EntrDemo.c demo\DemoMisc.c LIB\TCXLWCS.LIB >TCXLDemo.Log
WCL /fpi /i=inc /ms /oaxt /s /w4 /i=. /lp demo\Mid_Demo.c demo\Win_Demo.c demo\Str_Demo.c demo\DemoMisc.c LIB\TCXLWCS.LIB >>TCXLDemo.Log
goto DONE
:
:ZORTECH
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\UserDemo.c -odemo\userdemo.obj >TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\MenuDemo.c -odemo\MenuDemo.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\EntrDemo.c -odemo\EntrDemo.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\DemoMisc.c -odemo\DemoMisc.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\Mid_Demo.c -odemo\Mid_Demo.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\Win_Demo.c -odemo\Win_Demo.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -S- -s- -c -ms -IINC -I. demo\Str_Demo.c -odemo\Str_Demo.obj >>TCXLDemo.Log
ZTC -b -o+all -o+w -ms -IINC -I. demo\UserDemo.obj demo\MenuDemo.obj demo\EntrDemo.obj demo\DemoMisc.obj LIB\TCXLZTS.LIB >>TCXLDemo.Log
ZTC -b -o+all -o+w -ms -IINC -I. demo\Mid_Demo.obj demo\Win_Demo.obj demo\Str_Demo.obj demo\DemoMisc.obj LIB\TCXLZTS.LIB >>TCXLDemo.Log
goto DONE
:
:JPI
TSC makedemo.pr /ms /w+ /m >TCXLDemo.Log
goto DONE
:
:Done
copy TCXLDemo.Log con >nul
:
:ND
echo .                                                                      .
echo *=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
echo  Copyright (c) 1987-1991, Innovative Data Concepts. All Rights Reserved
echo .                                                                      .
echo Done
