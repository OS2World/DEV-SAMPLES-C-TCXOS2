/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   mid_demo.c     552.0   17 Mar 1991 18:28:24  $
 |
 | $Log:   mid_demo.c    $
 *-D--------------------------------------------------------------------*
 | Mid_Demo.C : TCXL Middle-level Demonstration Program.
 |
 | Syntax:  MID_DEMO [-switches]
 |
 |    -c  = CGA snow elimination
 |    -b  = BIOS screen writing
 |    -m  = force monochrome text attributes
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Also requires Str_Demo.C, Win_Demo.C and DemoMisc.C.
 | 2) Use the MakeDemo.Bat file to compile this program.
 *======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "demo\TCXLdemo.h"             /* TCXL demo-specific            */

/*----------------------------[ Global data ]---------------------------*/

IntT  CDC   LeftRow, LeftCol;          /* main menu coords              */
IntT  CDC   RightRow, RightCol;
IntT  CDC   DemoFast = 0;              /* window delay flag             */

/*----------------------------[ Local data ]----------------------------*/

LCL   ChrT  CDC   date[7], phone[11], ssan[10]; /* input demo fields    */

/*-----------[ Main menu item-build and menu-build objects ]------------*
 | Elements for each item IbldT are:
 |    istr, ichr, imsk, irow, icol, itag, ihlp, ikey, iusr,
 |    ibef, isel, iaft, itxt, isub
 | Elements for the menu MbldT are:
 |    mitm, mcnt, mbgr, mbgc, menr, menc, mtyp, mfrt, mfra,
 |    mwat, mtat, msat, mnat, mbat,
 |    mtag, mopn, musr, mwid, mofs, mdtr, mdtc, mdat
 | The structures are defined in <TCXLmnu.h>.
 *----------------------------------------------------------------------*/

LCL   IbldT CDC   Mid_Itm[5] =         /*- Main Menu Items -------------*/
{  {  "Window System",  'W', 0, 0, 0, 1, H_WINDOWING, 0, 0,
      NULL, WinDemo,    NULL, NULL, NULL  },
   {  "Input System",   'I', 0, 1, 0, 2, H_INPUT,     0, 0,
      NULL, InputDemo,  NULL, NULL, NULL  },
   {  "Strings System", 't', 0, 2, 0, 3, H_STRINGS,   0, 0,
      NULL, StringDemo, NULL, NULL, NULL  },
   {  "Information",    'n', 0, 3, 0, 4, H_NONE,      0, 0,
      NULL, TcxlInfo,   NULL, NULL, NULL  },
   {  "Exit demo",      'x', 0, 4, 0, 5, H_NONE,      0, 0,
      NULL, NULL,       NULL, NULL, NULL  }
};
LCL   MbldT CDC   Mid_Mnu =            /*- Main menu -------------------*/
{  &Mid_Itm[0], 5,  0,  0,  0,  0, MNU_VER, BOX_SNG, LBLUE|_BLUE,
   LBLUE|_BLUE, LCYAN|_BLUE, WHITE|_BLUE, 0, BLUE|_LGREY,
   1, PreMenu1,  0, 19, 1, 0xFF, 0xFF, 0xFF
};

/*================[ The TCXL Middle-Level Demo Program ]================*/

IntT CDC main(IntT argc, ChrP argv[])
{
   Initialize();                       /* initialize for demo           */
   ParseCmdLine(argc, argv);           /* parse command-line switches   */
   OpenBkgrnd();                       /* display opening screen        */
   Mid_Mnu.mbgr = MsByt(LeftRow);      /* set main-menu position        */
   Mid_Mnu.mbgc = MsByt(LeftCol);
   Mid_Mnu.menr = MsByt(RightRow);
   Mid_Mnu.menc = MsByt(RightCol);
   MainMenu(&Mid_Mnu);                 /* display/process main menu     */
   NormalExit();                       /* exit normally                 */
   return(0);                          /* *** never executed ***        */
}  /* main() */

/*=========================[ Input-system demo ]========================*
 | Called from the [I]nput mani menu item
 *----------------------------------------------------------------------*/

VOID  CTYP  InputDemo(NOARG)
{
   VcelFP   s;

   s = FarVsave(LGREY|_BLUE);          /* save the screen               */
   CurSave();                          /* save cursor state             */
   if(!WpopUp(CNT_CNT, 5, 21, 15,      /* pop up the demo window        */
      58, 3, LGREEN|_MAGENTA, LGREEN|_MAGENTA))
      ErrorExit(1);                    /* windowing error!              */

   Wtitle("[ Single-Line Input ]",     /* add a title                   */
      TTL_CNT, LGREEN|_MAGENTA);
   HlpSet(H_DATAENTRY);                /* set help category             */
   AddShadow();                        /* add a shadow                  */
   WsetTxt(WHITE|_MAGENTA);            /* text attribute                */
   if(KwGetFmt(phone,                  /* phone-number field            */
         "'\n\n  Phone Number?    "
         "'!R--!'('!+!###!-!') '!+!###!-!'-'!+!####"))
      ConfirmQuit();                   /* check user response           */
   WsetTxt(WHITE|_MAGENTA);            /* text attribute                */

   if(KwGetFmt(ssan,                   /* social security number field  */
         "'\n\n  Soc Sec Number?  "
         "'!R-!<01234567>##!-!'-'!+!##!-!'-'!+!####"))
      ConfirmQuit();                   /* check user response           */
   WsetTxt(WHITE|_MAGENTA);            /* text attribute                */

   if(KwGetFmt(date,                   /* date field                    */
         "\"\n\n  Today's Date?    "
          "\"!R-!<01>#!-!'/'!+!<0123>#!-!'/'!+!'19'##"))
      ConfirmQuit();                   /* check user response           */
   Wclose();                           /* close the window              */
   CurPop();                           /* restore original cursor state */
   FarVrestore(s);                     /* restore the screen            */
   KeyClear();                         /* flush any lurking keys        */
   MoveBarDn();                        /* select next main menu item    */
}  /* InputDemo() */
/*- end of Mid_Demo.c --------------------------------------------------*/

