/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/userdemo.c_v   552.2   13 Jun 1991  5:00:08  $
 |
 | $Log:   D:/beta/version/userdemo.c_v  $
 | 
 |    Rev 552.2   13 Jun 1991  5:00:08
 | turn on directories and parents
 | 
 |    Rev 552.1   17 Mar 1991 20:02:48
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | UserDemo.C : TCXL User-level Demonstration Program.
 |
 | Syntax:  USERDEMO [-switches]
 |
 |    -c  = CGA snow elimination
 |    -b  = BIOS screen writing
 |    -m  = force monochrome text attributes
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Also requires MenuDemo.C, EntrDemo.C and DemoMisc.C.
 | 2) Use the MakeDemo.Bat file to compile this program.
 *======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "demo\TCXLdemo.h"             /* TCXL demo-specific            */
#include <TCXLsel.h>                   /* TCXL selection/windows/video  */

/*----------------------------[ Global data ]---------------------------*/

IntT  CDC   LeftRow, LeftCol;          /* main menu coords              */
IntT  CDC   RightRow, RightCol;
IntT  CDC   DemoFast = 0;              /* window delay flag             */
ChrP  CDC   months[] =                 /* months table                  */
{
   "January", "February", "March", "April", "May", "June", "July",
   "August", "September", "October", "November", "December", NULL
};

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

LCL   IbldT CDC   UserItm[5] =         /*- Main Menu Items -------------*/
{  {  "Menu System",      'M', 0, 0, 0, 1, H_MENUING,   0, 0,
      NULL, MenuDemo,   NULL, NULL, NULL  },
   {  "Entry System",     'E', 0, 1, 0, 2, H_DATAENTRY, 0, 0,
      NULL, EntryDemo,  NULL, NULL, NULL  },
   {  "Selection System", 'S', 0, 2, 0, 3, H_LISTPICK,  0, 0,
      NULL, SelectDemo, NULL, NULL, NULL  },
   {  "Information",      'n', 0, 3, 0, 4, H_NONE,      0, 0,
      NULL, TcxlInfo,   NULL, NULL, NULL  },
   {  "Exit demo",        'x', 0, 4, 0, 5, H_NONE,      0, 0,
      NULL, NULL,       NULL, NULL, NULL  }
};
LCL   MbldT CDC   UserMnu =            /*- Main menu -------------------*/
{  &UserItm[0], 5,  0,  0,  0,  0, MNU_VER, BOX_SNG, LBLUE|_BLUE,
   LBLUE|_BLUE, LCYAN|_BLUE, WHITE|_BLUE, 0, BLUE|_LGREY,
   1, PreMenu1,  0, 19, 1, 0xFF, 0xFF, 0xFF
};

LCL   ChrP  CDC   prn_ports[] =        /* printer ports table           */
{
   "PRN", "LPT1", "LPT2", "COM1", "COM2", NULL
};

/*---------------------[ Local function prototypes ]--------------------*/

LCL   VOID  CTYP  PrePick1(NOARG);
LCL   VOID  CTYP  YouSelected(ChrP str);

/*=================[ The TCXL User-Level Demo Program ]=================*/

IntT CDC main(IntT argc, ChrP argv[])
{
   Initialize();                       /* initialize TCXL               */
   ParseCmdLine(argc, argv);           /* parse any options             */
   OpenBkgrnd();                       /* build screen                  */
   UserMnu.mbgr = MsByt(LeftRow);      /* set main-menu position        */
   UserMnu.mbgc = MsByt(LeftCol);
   UserMnu.menr = MsByt(RightRow);
   UserMnu.menc = MsByt(RightCol);
   MainMenu(&UserMnu);                 /* display/process main menu     */
   NormalExit();                       /* we're done                    */
   return(0);                          /* *** never executed ***        */
}

/*=======================[ Selection-system demo ]======================*
 | Demonstrate the string-selectection, file-selection, in-place
 | text-selection and attribute-selection features of TCXL. Called from
 | the main-menu [S]election item.
 *----------------------------------------------------------------------*/

VOID  CTYP  SelectDemo(NOARG)
{
   REG VcelFP  s;

   s = FarVsave(LGREY|_BLUE);          /* save the screen               */
   MouPush(MOU_FULL);                  /* full mouse support            */

   if(!WpopUp(CNT_CNT, 5, 11, 17, 68,  /* pop up the demo window        */
      3, LMAGENTA|_RED, LRED|_MAGENTA))
      ErrorExit(1);                    /* windowing error!              */

   AddShadow();                        /* add a shadow                  */
   Wputf("\033R\001\033C\003Select a month =>\033R\001\033C\003");
   HlpSet(H_STRPICK);                  /* set help category             */

   YouSelected(months[SelStr(LeftRow,  /* string select                 */
      32, LeftRow + 5, -1, 0, LGREEN|_RED, LCYAN|_RED, RED|_LGREY,
      months, 0, _VFVCP(PrePick1))]);
   Wputf("\033R\003\033C\003Now, select a file.\033R\003\033C\003");

   HlpSet(H_FILEPICK);                 /* set help category             */

   SelParOn();
   SelDirOn();
   YouSelected(SelFile(LeftRow,        /* file select                   */
      LeftCol - 18, LeftRow + 10, LeftCol + 39, 0, LCYAN|_RED,
      LGREY|_RED, RED|_LGREY, 1, "*.*", _VFVCP(AddShadow)));

                                       /* in-place text-select          */
   Wputf("\033R\005\033C\003Select a printer port:\033R\005\033C\003");
   YouSelected(prn_ports[SelTxt(5, 27, LMAGENTA|_MAGENTA, prn_ports, 0)]);

   HlpSet(H_PICKATTR);                 /*set help category              */
   Wputf("\033R\007\033C\003Select a text attribute:\033R\007\033C\003");
                                       /* attribute-selection           */
   YouSelected(VatrTxt(MsAtr(SelAttr(LeftRow - 6, LeftCol - 21, 0, 0,
      TRUE, _VFVCP(AddShadow)))));
   Wclose();                           /* close window                  */
   MouPop();                           /* restore mouse                 */
   FarVrestore(s);                     /* restore screen                */
   MoveBarDn();                        /* select next main-menu item    */
}  /* SelectDemo() */


/*-------------------[ String-select "open" function ]------------------*
 * Called when the string-select window is opened
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  PrePick1(NOARG)
{
   Wmessage("* *", BRD_BOT, 4, LGREEN|_RED);
   AddShadow();
}

/*---------[ Display the selected string or an error message ]----------*
 | Also prompt for a keypress 2 lines below the string/error message.
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  YouSelected(ChrP str)
{
   VposT rc;

   if(TcxlErr)                         /* error message                 */
      Wputf("\033EL%s", WerrMsg());
   else                                /* selected string               */
      Wputf("\033ELYou selected:  \033F\005%s\033F\004", str);
   HlpSet(H_LISTPICK);                 /* set help category             */
   WcurGet(rc);                        /* get cursor position           */
   PressAKey(MsByt(VposR(rc) + 2));    /* prompt for a key              */
}

/*- end of UserDemo.c --------------------------------------------------*/
