/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/menudemo.c_v   552.15   30 Sep 1991  6:33:32  $
 |
 | $Log:   D:/beta/version/menudemo.c_v  $
 | 
 |    Rev 552.15   30 Sep 1991  6:33:32
 | a bit more room for debugger
 | 
 |    Rev 552.14   30 Sep 1991  6:16:52
 | fix missing _TcxlI
 | 
 |    Rev 552.13   28 Sep 1991 12:19:32
 | more zortect code reduction
 | 
 |    Rev 552.12   07 Sep 1991 18:19:18
 | back out change
 | 
 |    Rev 552.10   22 Jun 1991 14:03:48
 | check correct return value from Wopen
 | 
 |    Rev 552.9   22 Jun 1991 13:58:32
 | put back DispSureMsg()
 | 
 |    Rev 552.8   21 Jun 1991 16:24:24
 | code consolidation/reduction
 | 
 |    Rev 552.7   21 Jun 1991  6:02:06
 | shut up MS6 warnings
 | 
 |    Rev 552.6   13 Jun 1991 11:30:38
 | Fix bad col setting for KbndMou
 | 
 |    Rev 552.5   01 Jun 1991  7:14:20
 | Fix Typos
 | 
 |    Rev 552.4   01 Jun 1991  7:02:20
 | add hotkeys to top menus, and KbndMou stuff
 | 
 |    Rev 552.3   21 Apr 1991 12:02:00
 | add unix compatibility updates
 | 
 |    Rev 552.2   05 Apr 1991  8:35:56
 | set correct initial item in Default menu
 | 
 |    Rev 552.1   17 Mar 1991 20:03:00
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | MenuDemo.C : TCXL Menu-system demonstration
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Use the MakeDemo.Bat file to compile this file.
 *======================================================================*/
#include <stdio.h>
#include <TCXL_os.h>                   /* TCXL DOS functions            */
#if (_TCXL_cc_ < 128) && !defined(_TCXLos2_)
#include <dos.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "demo\TCXLdemo.h"             /* TCXL demo-specific            */
#include <TCXLstr.h>                   /* TCXL string functions         */
#include <TCXLsel.h>                   /* TCXL selection system         */
#include <TCXLent.h>                   /* TCXL entry system             */
#include <TCXLvUV.h>                   /* TCXL UltraVision/video        */
#include <TCXLfmt.h>                   /* TCXL conversion functions     */
#include <TCXLcod.h>                   /* TCXL key-codes                */

/*----------------------------[ Local data ]----------------------------*/

LCL   ChrP  CDC   LinArr[] =           /* screen lines table            */
{  "25 Lines", "43 Lines", "50 Lines", NULL
};

#if !defined(_TCXLos2_)
LCL   ChrP  CDC   UvArr[] =            /* Ultravision screen modes      */
{  "80x25",                   "80x43 EGA, 80x50 VGA",
   "80x34 EGA, 80x36 VGA",    "80x60 EGA, 80x63 VGA",
   "94x25",                   "94x43 EGA, 94x50 VGA",
   "94x36",                   "94x63",
   "108x25",                  "108x43 EGA, 108x50 VGA",
   "108x34 EGA, 108x36 VGA",  "108x60 EGA, 108x63 VGA",
   "120x25",                  "120x43 EGA, 120x50 VGA",
   "120x36",                  "120x63",
   "132x25",                  "132x44, 132x50 SuperVGA",
   "132x36",                  "132x60",
   NULL
};
#endif

#if !defined(_TCXLos2_)
LCL   IntT  CDC   UvMode[] =           /* Ultravision mode numbers      */
{  0x11, 0x12, 0x13, 0x14, 0x19, 0x1A, 0x1B, 0x1C,
   0x21, 0x22, 0x23, 0x24, 0x31, 0x32, 0x39, 0x3A,
   0x33, 0x34, 0x3B, 0x3C, 0
};
#endif
LCL   ChrT  CDC   Rmargin[] = "Right margin     72";
LCL   ChrT  CDC   Lmargin[] = "Left margin       0";
#if !defined(_TCXLos2_)
LCL   ChrP  CDC   UvVal[21];
LCL   IntT  CDC   UvMd[21];
#endif
LCL   ChrP  CDC   Edemo[] =            /* Editor demo text              */
{
   "This is a sample editor interface to demonstrate how TCXL's menuing ",
   "functions can be used to create a pull-down menu system.  Use the ",
   "arrow keys to move the selection bar around and use the [Esc] key to ",
   "back up to the previous menu.  Pressing [F1] will bring up ",
   "context-sensitive help.  Select [Q]uit from any menu to exit the ",
   "Menu Demonstration.  Be sure to try some of the menu options in ",
   "the pull-down menus.  In particular, you might try to change ",
   "the left and right margins under the <D>efault option, or to ",
#if !defined(_TCXLos2_)
   "adjust the screen size if you have an EGA/VGA, or use Ultravision.",
#else
   "adjust the screen size if you have an EGA/VGA.",
#endif
   NULL,
   "  Since you have a mouse, you can use it to move around and ",
   "select options!  You can also click the left mouse button on the ",
   "highlighted words below to jump to a different part of this program:\n",
   NULL
};

INFO TcxlI[] =          /* text displayed in Information screen         */
{  {  1, WHITE|_RED,
     "The TesSeRact(TM) CXL User Interface Development System" },
   {  2, WHITE|_RED,
      "Copyright (c) 1987-1991, Innovative Data Concepts" },
   {  3, WHITE|_RED,
      "All Rights Reserved" },
   {  5, BLACK|_RED,
      "TCXL is a Full-Featured C Development System that supports" },
   {  6, BLACK|_RED,
      "Microsoft, Borland, Zortech, JPI, & Watcom Compilers (DOS)," },
   {  7, BLACK|_RED,
      "as well as portability to Unix, OS/2 and 386 Protected Mode" },
};

/*---------------------[ Local function prototypes ]--------------------*/

LCL   VOID  CTYP  ChangeSize(NOARG);
LCL   VOID  CTYP  Directory(NOARG);
LCL   VOID  CTYP  DispSureMsg(NOARG);
LCL   VOID  CTYP  DoNothing(NOARG);
LCL   VOID  CTYP  DrawEditor(IntT Lmar, IntT Rmar);
LCL   VOID  CTYP  Execute(NOARG);
LCL   VOID  CTYP  OsShell(NOARG);
LCL   VOID  CTYP  OsShell1(ChrP Cmd);
LCL   VOID  CTYP  PopupDemo(NOARG);
LCL   VOID  CTYP  QuitWindow(NOARG);
LCL   VOID  CTYP  RMargin(NOARG);
LCL   VOID  CTYP  SetupMenu(NOARG);
LCL   VOID  CTYP  ToggleBlock(NOARG);
LCL   VOID  CTYP  ToggleYN(NOARG);
LCL   VOID  CTYP  UpdateClock(NOARG);
LCL   IntT  CTYP  ValidMarg(ChrP Input);
#if !defined(_TCXLos2_)
LCL   IntT  CTYP  ValidModes(NOARG);
#endif

/*-------------[ Demo item-build and menu-build objects ]---------------*
 | Note that the *entire* demo menu-tree is defined here, from the top
 | bar down through the pop-up.  This is done here to include local
 | function pointers after the prototypes are defined. The structures are
 | defined in <TCXLmnu.h>. Elements for each item IbldT are:
 |    istr, ichr, imsk, irow, icol, itag, ihlp, ikey, iusr,
 |    ibef, isel, iaft, itxt, isub
 | Elements for each menu MbldT are:
 |    mitm, mcnt, mbgr, mbgc, menr, menc, mtyp, mfrt, mfra,
 |    mwat, mtat, msat, mnat, mbat,
 |    mtag, mopn, musr, mwid, mofs, mdtr, mdtc, mdat
 *----------------------------------------------------------------------*/

LCL   IbldT  CDC   FilItm[8] =         /*- "File" pulldown items -------*/
{  {  "Load",          'L', 0,       0, 0, 20, H_LOAD,      0,      0,
       NULL,      DoNothing, NULL,       NULL, NULL   },
   {  "Save",          'S', 0,       1, 0, 21, H_SAVE,      0,      0,
       NULL,      DoNothing, NULL,       NULL, NULL   },
   {  "Rename",        'R', 0,       2, 0, 22, H_RENAME,    0,      0,
       NULL,      DoNothing, NULL,       NULL, NULL   },
   {  "New",           'N', 0,       3, 0, 23, H_NEW,       0,      0,
       NULL,      DoNothing, NULL,       NULL, NULL   },
   {  "Directory  F5", 'D', 0,       4, 0, 24, H_DIRECTORY, Key_F5, 0,
       NULL,      Directory, NULL,       NULL, NULL   },
   {  "Execute    F6", 'E', 0,       5, 0, 25, H_EXECUTE,   Key_F6, 0,
       NULL,      Execute,   NULL,       NULL, NULL   },
   {  "OS Shell   F7", 'O', ITM_BEF, 6, 0, 26, H_OSSHELL,   Key_F7, 0,
       NULL,      OsShell,   NULL,       NULL, NULL   },
   {  "Quit",          'Q', ITM_ALL, 7, 0, 27, H_QUIT,      0,      0,
      QuitWindow, NULL,      QuitWindow, NULL, NULL   }
};
LCL   MbldT CDC   FilMnu =             /*- "File" pulldown menu --------*/
{  &FilItm[0], 8,  2,  1, 11, 17, MNU_PUL|MNU_SAV, BOX_SNG, LGREY|_BLUE,
   _BLUE, YELLOW|_BLUE, LCYAN|_BLUE, 0, YELLOW|_MAGENTA,
   20, NULL,  0, 15,  1, 0xFF, 0xFF, 0xFF
};
LCL   IbldT CDC   EdtItm[7] =          /*- "Edit" pulldown items -------*/
{  {  "Cut",         'C', 0,       0, 0, 29, H_NONE, 0, 0,
       NULL, DoNothing,   NULL, NULL, NULL  },
   {  "Paste",       'P', ITM_NSL, 1, 0, 30, H_NONE, 0, 0,
       NULL, DoNothing,   NULL, NULL, NULL  },
   {  "cOpy",        'O', ITM_NSL, 2, 0, 31, H_NONE, 0, 0,
       NULL, DoNothing,   NULL, NULL, NULL  },
   {  "block Begin", 'B', 0,       3, 0, 32, H_NONE, 0, 0,
       NULL, ToggleBlock, NULL, NULL, NULL  },
   {  "block End",   'E', ITM_NSL, 4, 0, 33, H_NONE, 0, 0,
       NULL, ToggleBlock, NULL, NULL, NULL  },
   {  "Insert line", 'I', 0,       5, 0, 34, H_NONE, 0, 0,
       NULL, DoNothing,   NULL, NULL, NULL  },
   {  "Delete line", 'D', 0,       6, 0, 35, H_NONE, 0, 0,
       NULL, DoNothing,   NULL, NULL, NULL  },
};
LCL   MbldT CDC   EdtMnu =             /*- "Edit" pulldown menu --------*/
{  &EdtItm[0], 7,  2, 14, 10, 28, MNU_PUL|MNU_SAV, BOX_SNG, LGREY|_BLUE,
   _BLUE, YELLOW|_BLUE, LCYAN|_BLUE, CYAN|_BLUE, YELLOW|_MAGENTA,
   29, NULL,  0, 13,  1, 0xFF, 0xFF, 0xFF
};
LCL   IbldT CDC   DefItm[8] =          /*- "Defaults" pulldown items----*/
{  {  Lmargin,               'L', ITM_ALL, 0, 0, 37, H_NONE, 0, 0,
       NULL, RMargin,   NULL, NULL, NULL  },
   {  Rmargin,               'R', ITM_ALL, 1, 0, 38, H_NONE, 0, 0,
       NULL, RMargin,   NULL, NULL, NULL  },
   {  "Tab width         4", 'T', 0,       2, 0, 39, H_NONE, 0, 0,
       NULL, DoNothing, NULL, NULL, NULL  },
   {  "tab eXpansion   yes", 'X', 0,       4, 0, 40, H_NONE, 0, 0,
       NULL, ToggleYN,  NULL, NULL, NULL  },

   {  "Insert mode     yes", 'I', 0,       5, 0, 41, H_NONE, 0, 0,
       NULL, ToggleYN,  NULL, NULL, NULL  },
   {  "iNdent mode     yes", 'N', 0,       6, 0, 42, H_NONE, 0, 0,
       NULL, ToggleYN,  NULL, NULL, NULL  },
   {  "Word wrap mode   no", 'W', 0,       7, 0, 43, H_NONE, 0, 0,
       NULL, ToggleYN,  NULL, NULL, NULL  },
   {  "Save defaults",       'S', 0,       9, 0, 44, H_NONE, 0, 0,
       NULL, DoNothing, NULL, NULL, NULL  }
};
LCL   MbldT CDC   DefMnu =             /*- "Defaults" pulldown menu ----*/
{  &DefItm[0], 8,  2, 30, 13, 52, MNU_PUL|MNU_SAV, BOX_SNG, LGREY|_BLUE,
   _BLUE, YELLOW|_BLUE, LCYAN|_BLUE, 0, YELLOW|_MAGENTA,
   38, SetupMenu,  0, 21,  1, 0xFF, 0xFF, 0xFF
};
LCL   IbldT CDC   OptItm[5] =          /*- "Options" pulldown items ----*/
{  {  "screen siZe",        'Z', ITM_ALL, 0, 0, 47, H_NONE, 0, 0,
       NULL, ChangeSize, NULL, NULL, NULL  },
   {  "Backup files   yes", 'B', 0,       1, 0, 48, H_NONE, 0, 0,
       NULL, ToggleYN,   NULL, NULL, NULL  },
   {  "bOxed display   no", 'O', 0,       2, 0, 49, H_NONE, 0, 0,
       NULL, ToggleYN,   NULL, NULL, NULL  },
   {  "Load options",       'L', 0,       3, 0, 50, H_NONE, 0, 0,
       NULL, DoNothing,  NULL, NULL, NULL  },
   {  "Save options",       'S', 0,       4, 0, 51, H_NONE, 0, 0,
       NULL, DoNothing,  NULL, NULL, NULL  }
};
LCL   MbldT CDC   OptMnu =             /*- "Options" pulldown menu -----*/
{  &OptItm[0], 5,  2, 56,  8, 77, MNU_PUL|MNU_SAV, BOX_SNG, LGREY|_BLUE,
   _BLUE, YELLOW|_BLUE, LCYAN|_BLUE, 0, YELLOW|_MAGENTA,
   47, NULL,  0, 20,  1, 0xFF, 0xFF, 0xFF
};
LCL   IbldT CDC   QitItm[2] =          /*- "Quit" pulldown items -------*/
{  {  "No",  'N', ITM_AFT, 2, 0, 53, H_NONE, 0, 0,
      NULL, NULL, NULL, NULL, NULL  },
   {  "Yes", 'Y', ITM_ALL, 3, 0, 54, H_NONE, 0, 0,
      NULL, NULL, NULL, NULL, NULL  }
};
LCL   MbldT CDC   QitMnu =             /*- "Quit" pulldown menu --------*/
{  &QitItm[0], 2,  2, 60,  7, 78, MNU_PUL, BOX_SNG, LGREY|_BLUE,
   _BLUE, YELLOW|_BLUE, LCYAN|_BLUE, WHITE|_BLUE, YELLOW|_MAGENTA,
   53, DispSureMsg,  0, 17, 7, 0xFF, 0xFF, 0xFF
};

LCL   IbldT CDC   TopItm[6] =          /*- Main bar items --------------*/
{  {  "File",     'F', ITM_PUL, 0,  2, 19, H_FILE,     Key_A_F, 0,
      NULL,       NULL,      NULL,       NULL, &FilMnu  },
   {  "Editing",  'E', ITM_PUL, 0, 15, 28, H_EDITING,  Key_A_E, 0,
      NULL,       NULL,      NULL,       NULL, &EdtMnu  },
   {  "Defaults", 'D', ITM_PUL, 0, 31, 36, H_DEFAULTS, Key_A_D, 0,
      NULL,       NULL,      NULL,       NULL, &DefMnu  },
   {  "Run",      'R', 0,       0, 47, 45, H_RUN,      Key_A_R, 0,
      NULL,       PopupDemo, NULL,       NULL, NULL    },
   {  "Options",  'O', ITM_PUL, 0, 59, 46, H_OPTIONS,  Key_A_O, 0,
      NULL,       NULL,      NULL,       NULL, &OptMnu  },
   {  "Quit",     'Q', ITM_PUL, 0, 73, 52, H_NONE,     Key_A_Q, 0,
      QuitWindow, NULL,      QuitWindow, NULL, &QitMnu  }
};
LCL   MbldT CDC   TopMnu =             /*- Main bar menu ---------------*/
{  &TopItm[0], 6,  1,  1,  1, 0, MNU_HOR, BOX_SPA, CYAN,
   CYAN|_BLUE, YELLOW|_BLUE, LCYAN|_BLUE, 0, YELLOW|_MAGENTA,
   19, NULL,  0,  0,  0, 0xFF, 0xFF, 0xFF
};

LCL   IbldT CDC   PopItm[6] =          /*- Pop-up menu items -----------*/
{  {  "Add",    'A', 0, 0,  0, 55, H_NONE, 0, 0,
      NULL, NULL, NULL, "Create a new record",                  NULL  },
   {  "Delete", 'D', 0, 0,  8, 56, H_NONE, 0, 0,
      NULL, NULL, NULL, "Delete an existing record",            NULL  },
   {  "Print",  'P', 0, 0, 19, 57, H_NONE, 0, 0,
      NULL, NULL, NULL, "Print hardcopy of existing record",    NULL  },
   {  "Show",   'S', 0, 0, 28, 58, H_NONE, 0, 0,
      NULL, NULL, NULL, "Display an existing record on screen", NULL  },
   {  "Update", 'U', 0, 0, 36, 59, H_NONE, 0, 0,
      NULL, NULL, NULL, "Modify an existing record",            NULL  },
   {  "Quit",   'Q', 0, 0, 45, 60, H_NONE, 0, 0,
      NULL, NULL, NULL, "Quit and return to pull-down menu",    NULL  }
};
LCL   MbldT CDC   PopMnu =             /*- Pop-up menu -----------------*/
{  &PopItm[0], 6,  7, 15, 10, 65, MNU_HOR, BOX_SNG, LRED,
   LCYAN|_BLUE, LMAGENTA|_BLUE, WHITE|_BLUE, 0, YELLOW|_LGREY,
   55, NULL,  0, 0, 0, 1, 0, LGREEN|_BLUE
};

/*=========[ The TCXL Menu Demo, a simulated editor interface ]=========*
 | Called from the [M]enuing item of the UserDemo.C main menu
 *----------------------------------------------------------------------*/

VOID  CTYP  MenuDemo(NOARG)
{
   IntT     s = 0;
   IntT     Lines;
   IntT     Line1 = 0, Line2 = 0;
   VcelFP   VidArea;

   KbndIdle(UpdateClock);              /* start clock display           */
   HlpPush(H_PULLDOWN);                /* push help category            */

#ifndef TCXLDBG
#if(_TCXL_cc_ != 2) && !defined(_TCXLos2_)  /* not for Zortech or OS/2  */
   _CerrPush(_IFFPCP(_AltCrit));       /* install alternate CritErr     */
#endif
#endif

#if !defined(_TCXLos2_)
   if(_VuvAct)                         /* draw editor display           */
      Lines = _VuvGet();
   else
#endif
      Lines = VidDep;
   cvtic(&Rmargin[16], VidWid - 8, 3);
   VidArea = FarVsave(LGREY|_BLACK);
   CurSave();                          /* save cursor state             */
redraw:                                /* come here to redraw the menu  */
   if((s == 37) || (s == 38))
      KquePut('D');
   else
      if(Line1 != Line2)
      {  if((s == 47) || (s >= 100))
         {  KquePut('O');
            KquePut('Z');
         }
      }
#if !defined(_TCXLos2_)
   if(_VuvAct)
      Line1 = _VuvGet();
   else
#endif
      Line1 = VidDep;
   if(atoi(&Rmargin[16]) > VidWid - 3)
      cvtic(&Rmargin[16], VidWid - 8, 3);
   DrawEditor(atoi(&Lmargin[16]), atoi(&Rmargin[16]));

   TopMnu.menc = MsByt(VidWid - 2);    /* adjust end-column             */
   MnuBuild(&TopMnu);                  /* build the menu tree           */

   s = MnuGet();                       /* process the menu              */

   while(KbndClr(Key_M_ClkL) == 0)     /* clear left mouse macros       */
      ;

   if(s == -1 && TcxlErr > W_ESCPRESS)
      ErrorExit(1);                    /* windowing error!              */

   Wclose();                           /* close up windows              */
   Wclose();
#if !defined(_TCXLos2_)
   if(_VuvAct)
      Line2 = _VuvGet();
   else
#endif
      Line2 = VidDep;
   if((s == 37) || (s == 38) || (s == 47) || (s >= 100))
      goto redraw;
#if !defined(_TCXLos2_)
   if(_VuvAct)                         /* Ultravision                   */
   {  if(Lines != _VuvGet())
         _VuvSet(Lines);
   }
   else                                /* ordinary BIOS                 */
#endif
   {  if(Lines != VidDep)
         VsetLin(Lines);
   }
   CurPop();                           /* restore cursor                */
   FarVrestore(VidArea);               /* restore screen                */
   KbndIdle(NULL);                     /* kill the clock                */
   HlpDrop();                          /* pop the help stack            */

#ifndef TCXLDBG
#if(_TCXL_cc_ != 2) && !defined(_TCXLos2_) /* not for Zortech or OS/2   */
   _CerrPop();                         /* restore CritErr-handler       */
#endif
#endif

   MoveBarDn();                        /* select next main-menu item    */
}  /* MenuDemo() */

/*------------------------[ Change screen size ]------------------------*/

LCL   VOID  CTYP  ChangeSize(NOARG)
{
   IntT   s, t, w;

   CurSave();                          /* save cursor state             */
   w = VidWid;                         /* current video width           */
#if !defined(_TCXLos2_)
   if(_VuvAct)                         /* UltraVision active            */
   {  t = ValidModes();                /* display selection list        */
      s = SelStr(4, 45, 12, 74, 0, LGREY|_BLUE, YELLOW|_BLUE,
            YELLOW|_MAGENTA, UvVal, t, NULL);

      if(s >= 0)                       /* set selected mode             */
         _VuvSet(UvMd[s]);
   }
   else                                /* no UltraVision                */
#endif
   {  if(VidWid != 80)                 /* has to be 80 columns          */
         Wperror("Invalid Screen Width to Demonstrate");

      else                             /* EGA or higher BIOS            */
      {  if(_VidTyp() != -1)           /* select number of lines        */
            s = SelStr(4, 57, 8, 71, 0, LGREY|_BLUE, YELLOW|_BLUE,
                   YELLOW|_MAGENTA, LinArr,
                   ((VidDep == 43) ? 1 : ((VidDep == 50) ? 2 : 0)), NULL);
            switch(s)
            {  case 0:
                  s = 25;
                  break;

               case 1:
                  s = 43;
                  break;

               case 2:
                  s = 50;
                  break;
            }
            if(s > 2)
               VsetLin(s);
      }
   }
   if(w != VidWid)                     /* update right margin           */
      cvtic(&Rmargin[16], VidWid - 8, 3);
   CurPop();                           /* restore cursor-state          */
}

/*--------[ Display a quick 'n' dirty directory of current path ]-------*
 | Uses new TCXL  functions that are compiler independent                                    ]
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  Directory(NOARG)
{
   ChrT        fs[49], f1[49];
   IntT        i, f, l, n;
   _FfbT       fb;

   strcpy(fs, "*.*");
   CurPush(CUR_SHO, -1, -1, -1);       /* show cursor, save state       */
   if(ERR_ARG == Wopen(4, 14, 20, 59, 0, /* open the window             */
      YELLOW|_BLUE, YELLOW|_BLUE))
      ErrorExit(1);                    /* windowing error!              */

   Wtitle("[ Directory ]", TTL_CNT, YELLOW|_BLUE);
                                       /* open form window, define form */
   if(ERR_ARG == Wopen(6, 6, 8, 49, 0, LCYAN|_RED, LCYAN|_RED))
      ErrorExit(1);                    /* windowing error!              */

   Wtitle("[ Filespec ]", TTL_CNT, LCYAN|_RED);
   EntDef(BLUE|_LGREY, BLUE|_LGREY, 1);
   EntFld(0, 1, fs, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
      FLD_TRM, 13, 2, NULL, H_EDITKEYS);
   i = EntGet(13);                     /* get user input, close window  */
   Wclose();
   if(13 == i)
   {  Wclear();                        /* clear directory window        */
      WsetTxt(LCYAN|_BLUE);            /* set text attribute            */
      l = n = 0;
      f = _FndFst(fs, &fb, 0);         /* build the directory display   */
      LOOP                             /*- endless loop ----------------*/
      {  if(f)                         /* nothing found                 */
            break;

         f1[0] = '\0';
         for(i = 0; (i < 3) && !f; i++)
         {  n++;                       /* next line                     */
            sprintf(fs, "%s%-15s", f1, _FfbNam(fb));
            strcpy(f1, fs);
            f = _FndNxt(&fb);          /* find next file                */
         }
         strtrim(f1);
         Wputf(" %s\n", f1);
         l++;
         if(l >= 14)                   /* more files to display ...     */
         {  Wputf("\033" "A\x1A Press a key to continue....\033" "A\x1B");
            i = (ChrT) KeyTime(36);
            Wputf("\r");
            if(i == ESC)
               break;
            l = 0;
         }
      }
                                       /* display summary               */
      Wputf("\033" "A\x1A Files found:  %d  Press a key....", n);
      KeyTime(36);
   }
   CurPop();                           /* restore cursor state          */
   Wclose();                           /* close the window              */
}  /*Directory() */

/*-------------------[ Display "Are you sure" prompt ]------------------*/

LCL   VOID  CTYP  DispSureMsg(NOARG)
{
   Wprts(0, 2, WHITE|_BLUE, "Are you sure?");
}  /* DispSureMsg() */

/*---------------[ Dummy function for several menu items ]--------------*/

LCL   VOID  CTYP  DoNothing(NOARG)
{
}  /* DoNothing() */

/*---------------------[ Draw a fake editor screen ]--------------------*/

LCL   VOID  CTYP  DrawEditor(IntT Lmar, IntT Rmar)
{
   IntT i = 0, j;

   if(ERR_ARG == Wopen(0, 0, VidDep - 1, VidWid - 1, 0, CYAN, CYAN))
      ErrorExit(1);                    /* can't open the window!        */

   WdrwHor(1, 0, MsByt(VidWid - 2),    /* draw the editor screen        */
      0, CYAN);
   if(ERR_ARG == Wopen(3, Lmar + 1, VidDep - 2, Rmar + 1, BOX_SPA, CYAN, 
         CYAN))
      ErrorExit(1);                    /* can't open the window!        */

   Wgotoxy(0, 0);                      /* home the cursor               */
   WsetTxt(YELLOW);                    /* set text attribute            */

   while(Edemo[i]  != NULL)            /* display the sample text       */
      Wputsw(Edemo[i++]);

   if(MouEnab)                         /* gee, we've got rats!          */
   {  i++;
      while(Edemo[i]  != NULL)         /* display the sample text       */
         Wputsw(Edemo[i++]);

      WposGet(&j, &i);                 /* current text-row              */
      Wgotoxy(MsAtr(j+1),MsAtr(19));
      j = WdfPosR(WctlAct);
      i = WdfPosC(WctlAct);
                                       /* set hot spot to position      */
      KbndMou(Key_M_ClkL, TcxlInfo, j, i, 11);
      KbndMou(Key_M_ClkL, EntryDemo, j, i + 16, 10);
      KbndMou(Key_M_ClkL, SelectDemo, j, i + 31, 11);
      Wputs("\033XInformation\033X     \033XEntry Demo\033X"
         "    \033XSelect Demo\033X");
   }

   WposGet(&j, &i);                    /* current text-row              */
   j++;

   i = 0;
   do
   {  WprtCen(MsByt(TcxlI[i].row + j), TcxlI[i].Atr, TcxlI[i].Str);
   }  while(++i < 6);

}  /* DrawEditor() */

/*-----------------------[ Execute a DOS command ]----------------------*/

LCL   VOID  CTYP  Execute(NOARG)
{
   ChrT        cd[61];

   if(ERR_ARG == Wopen(8, 7, 10, 70, 0, LGREY|_RED, LGREY|_RED))
      ErrorExit(1);

   Wtitle("[ Execute DOS Command ]", TTL_CNT, LGREY|_RED);
   EntDef(BLUE|_LGREY, BLUE|_LGREY, 1);
   EntFld(0, 1, cd,
      "************************************************************",
      FLD_TRM, 14, 0, NULL, H_EDITKEYS);
   if(14 == EntGet(14))                /* display the form              */
      OsShell1(cd);                    /* shell out with command        */
   Wclose();                           /* close window                  */
}  /* Execute() */

/*-----------[ The [O]S Shell function under the [F]ile menu ]----------*/

LCL   VOID  CTYP  OsShell(NOARG)
{
   OsShell1("");                       /* shell out with no command     */
}  /* OsShell() */

/*------------------[ Do the real work for OsShell() ]------------------*/

LCL   VOID  CTYP  OsShell1(ChrP Cmd)
{
   VcelFP   s;
   ChrT     c;

   c = *Cmd;
   CurPush(CUR_SHO, -1, -1, -1);       /* show cursor, save state       */
   MouHide();                          /* hide mouse if shown           */
   s = FarVsave(LGREY|_BLACK);         /* save the screen               */
   if(c == EOS)                        /* no command -- need an 'Exit'  */
      printf("Type EXIT to return....\n");

#if defined(__IBMAIX__) || defined(__SCOXENIX__)
   _TTYshell(Cmd);                     /*  so TTY is cleaned up     jpl */
#else
   system(Cmd);                        /* send the command to DOS       */
#endif

   if(c != EOS)                        /* got a command -- wait for key */
   {  printf("Press a key to return....\n");
      KeyWait();
   }
   FarVrestore(s);                     /* restore screen                */
   CurPop();                           /* restore cursor                */
   MouShow();                          /* show the mouse if we hid it   */
}  /* OsShell1() */

/*--------[ Display a sample popup menu with text descriptions ]--------*/

LCL   VOID  CTYP  PopupDemo(NOARG)
{
   HlpPush(H_PULLDOWN);                /* set help category             */
   MnuBuild(&PopMnu);                  /* build the pop-up menu         */
   MnuGet();                           /* display the menu              */
   HlpDrop();                          /* drop help category            */
}  /* PopupDemo() */

/*---------------[ Display the [Q]uit item pop-up window ]--------------*
 | Called anytime the selection bar moves on or off a [Q]uit menu item.
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  QuitWindow(NOARG)
{
   LCL WndT    h = 0;

   if(h)
   {  Wactiv(h);                       /* activate window               */
      Wclose();                        /* then close it                 */
      h = 0;
   }
   else                                /* open window                   */
   {  h = Wopen(14, 41, 17, 70, 0, YELLOW|_RED, WHITE|_RED);
      Wputs(" Quit takes you back to the\n demo program's main menu.");
   }
}  /* QuitWindow() */

/*------[ Get new [R]ight margin setting for the [D]efault menu ]-------*/

LCL   VOID  CTYP  RMargin(NOARG)
{
   EntDef(WHITE|_CYAN, WHITE|_CYAN, 1);
   EntFld(IdfPosR(ItmCur()), 17, (IdfStr(ItmCur())) + 16,
         "999", FLD_DEC, 15, 1, ValidMarg, 0);
   EntGet(15);
   ItmDsp((IdfTag(ItmCur())));
}  /* RMargin() */

/*--------------------[ Set up the [D]efaults menu ]--------------------*/

LCL   VOID  CTYP  SetupMenu(NOARG)
{
   WdrwHor(3, 0, 21, 0, LGREY|_BLUE);
   WdrwHor(8, 0, 21, 0, LGREY|_BLUE);
}  /* SetupMenu() */

/*-------[ Toggle "block marking" on and off in the fake editor ]-------*/

LCL   VOID  CTYP  ToggleBlock(NOARG)
{
   LCL IntT    b = OFF;
   IntT c;

   if(b)
   {  b = OFF;
      c = 32;
   }
   else
   {  b = ON;
      c = 33;
   }
   ItmEna(c);
   ItmDis(c ^ 0x01);
   ItmNxt(c);
   if(ERR_ARG != Wopen(11, 30, 15, 49, 0, LGREY|_MAGENTA, WHITE|_MAGENTA))
   {  Wputf("\n Block is now o%s", b ? "n" : "ff");
      _Delay(10);
      Wclose();
   }
}

/*------[ Toggles the yes/no status of some pull-down menu items ]------*
 | This is to show modifying and redisplaying a menu item's string. We do
 | this by getting the address of the current item's struct, then
 | modifying the string pointed to by the istr element.  The redisp flag
 | is set so that when you return to the menu, the screen will be
 | automatically updated.
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  ToggleYN(NOARG)
{
   IdfP i;
   ChrP s, y;
   LCL ChrT yes[] = "yes", no[] = " no";

   i = ItmCur();
   s = ItmGet(IdfTag(i));
   y = s + strlen(s) - 3;
   strcpy(y, strcmp(y, yes) ? yes : no);
   ItmDsp(IdfTag(i));
}

/*------------[ Update the on-screen clock once per second ]------------*/

LCL   VOID  CTYP  UpdateClock(NOARG)
{
   LCL DwdT    t;
   DwdT x;                             /* make a little faster      jpl */

   if(t < (x = _Timer()))
   {  Vprints(0, 70, LGREEN, SysTime(1));
      t = x + 18;
   }
}

/*--------[ Validates the [R]ight margin setting from RMargin()   ]-----*/

ChrT Lft[] = "Left Margin Too Large!";
ChrT Rgt[] = "Right Margin Too Small!";
LCL   IntT  CTYP  ValidMarg(ChrP Input)
{
   IntT Val, Err = 0;
   ChrP Msg;

   Val = cvtci(Input);

   if((Val > (VidWid - 3)) || (Val < 0))
   {  Wperror("Invalid Margin!");
      Err = 1;
   }
   if(IdfTag(ItmCur()) == 37)
   {  if(Val >= cvtci(&Rmargin[16]))
      {  Msg = Lft;
         goto e2;
      }
   }
   else
   {  if(cvtci(&Lmargin[16]) >= Val)
      {  Msg = Rgt;
e2:      Wperror(Msg);
         Err = 1;
      }
   }
   return(Err);
}

#if !defined(_TCXLos2_)
/*--------------[ Build arrays of valid Ultravision modes ]-------------*/

LCL   IntT  CTYP  ValidModes(NOARG)
{
   int   i, n, q, r;

   q = _VuvGet();
   n = 0;

   for(i = 0; UvMode[i] != 0; i++)
   {  if(_VuvVal(UvMode[i]) == 0)
      {  UvVal[n] = UvArr[i];
         UvMd[n++] = UvMode[i];
         if(q == UvMode[i])
            r = n - 1;
      }
   }
   UvVal[n] = NULL;
   return(r);
}
#endif
