/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call 1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   tcxldemo.h     552.2   23 Mar 1991 13:08:52  $
 |
 | $Log:   tcxldemo.h    $
 *-D--------------------------------------------------------------------*
 | TCXLdemo.h : Definitions and prototypes for the TCXL 5.5 demo programs
 *-N-----------------------[ Notes and Caveats ]------------------------*
 |
 *======================================================================*/
#ifndef  _TCXLdemo_                    /* only once!                    */
#  ifndef   _TCXLinp_
#     include  <TCXLinp.h>             /* TCXL input                    */
#  endif
#  ifndef   _TCXLcur_
#     include  <TCXLcur.h>             /* TCXL cursor                   */
#  endif
#  ifndef   _TCXLmnu_
#     include  <TCXLmnu.h>             /* TCXL menu/window/video        */
#  endif
#  ifndef   _TCXLhlp_
#     include  <TCXLhlp.h>             /* TCXL help                     */
#  endif
/*-----------------------[ help category numbers ]----------------------*/

#define  H_NONE       0
#define  H_GLOBAL     1
#define  H_WINDOWING  2
#define  H_MENUING    3
#define  H_LISTPICK   4
#define  H_STRPICK    5
#define  H_FILEPICK   6
#define  H_DATAENTRY  7
#define  H_EDITKEYS   8
#define  H_DATE       9
#define  H_FIRSTNAME 10
#define  H_INITIAL   11
#define  H_LASTNAME  12
#define  H_CITY      13
#define  H_STATE     14
#define  H_ZIPCODE   15
#define  H_COMPILER  16
#define  H_AMOUNT    17
#define  H_NUMERIC   18
#define  H_PULLDOWN  19
#define  H_FILE      20
#define  H_EDITING   21
#define  H_LOAD      22
#define  H_SAVE      23
#define  H_RENAME    24
#define  H_NEW       25
#define  H_DIRECTORY 26
#define  H_EXECUTE   27
#define  H_OSSHELL   28
#define  H_QUIT      29
#define  H_SCROLL    30
#define  H_CHGATTR   31
#define  H_CHGBORD   32
#define  H_WINTITLE  33
#define  H_RESIZE    34
#define  H_TEXTLINE  35
#define  H_WINMOVE   36
#define  H_WINHIDE   37
#define  H_ACTIVATE  38
#define  H_WINCOPY   39
#define  H_PICKATTR  40
#define  H_INPUT     41
#define  H_STRINGS   42
#define  H_DEFAULTS  43
#define  H_RUN       44
#define  H_OPTIONS   45

/*---------------------------[ Data objects ]---------------------------*
 | Example of using arrays of data structures to define/declare sets of
 | TCXL function arguments in an understandable and maintainable form.
 | See UserDemo.C, EntrDemo.C, MenuDemo.C, Mid_demo.C, and DemoMisc.C for
 | usage of this objects. Note that the elements of this structure are
 | WORD-ALIGNED for speed of access, without padding.
 *----------------------------------------------------------------------*/

TYP struct _Info              /* Information displayed by TcxlInfo()    */
{  BytT     row;                       /* row to display on             */
   AtrT     Atr;                       /* display attribute             */
   ChrP     Str;                       /* string to display             */
}  INFO;

/*----------------------------[ Global data ]---------------------------*/

GBL   INFO  CDC   TcxlI[];             /* TcxlInfo() strings            */
GBL   ChrP  CDC   months[];            /* month-name table              */
GBL   IntT  CDC   LeftRow, LeftCol;    /* main menu coords              */
GBL   IntT  CDC   RightRow, RightCol;
GBL   IntT  CDC   DemoFast;            /* window wait flag              */

/*------------------------[ Function prototypes ]-----------------------*
 | Local functions are prototyped in their respective modules. The actual
 | demo functions are called as "select" functions from the main menus of
 | UserDemo.C and Mid_Demo.C via function pointers. The remaining global
 | utility functions in DemoMisc.C are common to both demo programs.
 *----------------------------------------------------------------------*/

VOID  CTYP  EntryDemo(NOARG);          /* Entry System demo             */
VOID  CTYP  InputDemo(NOARG);          /* Input System demo             */
VOID  CTYP  MenuDemo(NOARG);           /* Menu System demo              */
VOID  CTYP  SelectDemo(NOARG);         /* Selection System demo         */
VOID  CTYP  StringDemo(NOARG);         /* Strings System demo           */
VOID  CTYP  WinDemo(NOARG);            /* Window System demo            */
                              /*- Utility functions in MiscDemo.C ------*/
VOID  CTYP  AddShadow(NOARG);          /* Add a shadow to window        */
VOID  CTYP  ConfirmQuit(NOARG);        /* Confirm user wants to quit    */
VOID  CTYP  ErrorExit(IntT errnum);    /* Error termination             */
VOID  CTYP  FarVrestore(               /* Restore screen from far heap  */
   VcelFP FarPtr);
VcelFP   CTYP  FarVsave(AtrT Atr);     /* Save screen on far heap       */
VOID  CTYP  Initialize(NOARG);         /* Initialize TCXL for demo      */
VOID  CTYP  MainMenu(MbldP mp);        /* Display/process main menu     */
VOID  CTYP  MoveBarDn(NOARG);          /* Select next main-menu item    */
VOID  CTYP  NormalExit(NOARG);         /* Normal termination            */
VOID  CTYP  OpenBkgrnd(NOARG);         /* Display demo background       */
VOID  CTYP  ParseCmdLine(IntT argc,    /* Parse command-line switches   */
   ChrP argv[]);
VOID  CTYP  ParseDate(ChrP buf,        /* Parse MMDDYY date string      */
   IntP month, IntP day, IntP year);
VOID  CTYP  PreHelp(NOARG);            /* Help-system "open" function   */
VOID  CTYP  PreMenu1(NOARG);           /* Main-menu "open" function     */
VOID  CTYP  PressAKey(BytT wrow);      /* Pause and wait for a keypress */
VOID  CTYP  PressAKey1(BytT wrow,
   IntT wait);
VOID  CTYP  TcxlInfo(NOARG);           /* Display TCXL info window      */
#endif   /* _TCXLdemo_ : end of TCXLdemo.h -----------------------------*/
