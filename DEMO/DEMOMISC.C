/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/demomisc.c_v   552.16   29 Sep 1991 14:07:20  $
 |
 | $Log:   D:/beta/version/demomisc.c_v  $
 | 
 |    Rev 552.16   29 Sep 1991 14:07:20
 | use help for TcxlInfo
 | 
 |    Rev 552.15   29 Sep 1991 13:46:30
 | added _heapgrow() call for Watcom
 | 
 |    Rev 552.14   29 Sep 1991 13:21:14
 | added farmalloc #defines for Watcom
 | 
 |    Rev 552.13   22 Jun 1991 14:03:44
 | check correct return value from Wopen
 | 
 |    Rev 552.12   21 Jun 1991 16:24:20
 | code consolidation/reduction
 | 
 |    Rev 552.11   21 Jun 1991 14:06:48
 | change top line
 | 
 |    Rev 552.10   19 Jun 1991 15:41:40
 | added Topspeed header for alloc
 | 
 |    Rev 552.9   13 Jun 1991  4:55:10
 | use NlsYes for GetYn prompts
 | 
 |    Rev 552.8   01 Jun 1991  6:59:36
 | don't bother to home the mouse; clean MoveBarDn
 | 
 |    Rev 552.7   17 May 1991 11:55:48
 | do correct large model conditional
 | 
 |    Rev 552.6   21 Apr 1991 16:06:40
 | Fix Typos
 | 
 |    Rev 552.5   21 Apr 1991 12:01:54
 | add unix compatibility updates
 | 
 |    Rev 552.4   15 Apr 1991  6:40:34
 | zortech header fix
 | 
 |    Rev 552.3   15 Apr 1991  6:17:14
 | Fix Typos
 | 
 |    Rev 552.2   23 Mar 1991  9:50:04
 | account for NlsYes characters in GetYn prompts
 | 
 |    Rev 552.1   17 Mar 1991 20:02:52
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | DemoMisc.C : Miscellaneous common utility functions for the various
 | TCXL demonstration programs.
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) FarVsave() and FarVrestore() will ONLY work correctly in small-data
 |    models (small, medium).  In large-data models (compact, large),
 |    they may fail due to heap collisions.  There's only a far heap in
 |    large-data.
 *======================================================================*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <TCXL_os.h>
#include "demo\TCXLdemo.h"             /* TCXL demo-specific            */
#if(_TCXL_cc_ == 22)                   /* needed for Zortech            */
#  include <dos.h>
#endif
#if(_TCXL_cc_ == 23)                   /* needed for MicroSoft C        */
#  include  <malloc.h>
#  define     farmalloc(s)   _fmalloc(s)
#  define     farfree(p)     _ffree(p)
#endif
#if(_TCXL_cc_ == 25)                   /* needed for Watcom C           */
#  include  <malloc.h>
#  define     farmalloc(s)   _fmalloc(s)
#  define     farfree(p)     _ffree(p)
#endif
#if(_TCXL_cc_ == 24)                   /* needed for TopSpeed C         */
#  include <alloc.h>
#endif
#include <TCXLmem.h>                   /* TCXL memory system            */
#include <TCXLfar.h>                   /* TCXL far-memory               */
#include <TCXLcod.h>                   /* TCXL key-codes                */
#include <TCXLnls.h>                   /* TCXL NLS sub-system           */

/*----------------------------[ Local data ]----------------------------*/

LCL   VcelFP   CDC   savescrn;         /* ptr to saved DOS screen       */

LCL   ChrP  CDC   error_text[] =       /* global error message table    */
{  NULL,                               /* errnum = 0, no error          */
   NULL,                               /* errnum = 1, windowing error   */
   "Usage : TCXLDEMO [-switches]\n\n"  /* errnum = 2, syntax error      */
   "\t-c = CGA snow elimination\n"
   "\t-b = BIOS screen writing\n"
   "\t-m = force monochrome text attributes",
   "Out of memory!",                   /* errnum = 3, out of memory     */
   "Far Heap Exhausted!"               /* errnum = 4, out of far heap   */
};

LCL   ChrP CDC QuitMsg = "\n Quit demo, are you sure? \033A\156Y\b";

/*================[ Add a shadow to the current window ]================*/

VOID  CTYP  AddShadow(NOARG)
{
   Wshadow(LGREY|_BLACK);              /* simple, ain't it?             */
}  /* AddShadow() */

/*===============[ Confirm the user really wants to quit ]==============*/

VOID  CTYP  ConfirmQuit(NOARG)
{
   KbndP    kblist;

   MouHide();                          /* hide mouse, if visible        */
   kblist = KbndChg(NULL);             /* hide any existing hot keys    */

   if(ERR_ARG == Wopen(9, 26, 13, 55, 0, /* pop up a confirmation window*/
         WHITE|_BROWN, WHITE|_BROWN))
      ErrorExit(1);                    /* windowing error!              */

   AddShadow();                        /* add shadow, ask user          */
   QuitMsg[30] = NlsYes;
   Wputs(QuitMsg);
   KeyClear();                         /* flush any lurking keys        */
   CurPush(CUR_SHO, -1, -1, -1);       /* show cursor, save state       */
   if(KwGetYn(NlsYes) == 'Y')          /* user said quit                */
      NormalExit();

   Wclose();                           /* close window                  */
   CurPop();                           /* restore cursor                */
   KbndChg(kblist);                    /* restore any hidden hot keys   */
   MouShow();                          /* show the mouse, if we hid it  */
}  /* ConfirmQuit() */

/*=======================[ Abnormal termination ]=======================*
 | If <e> is 1, it's a windowing system error.  Otherwise look up the
 | error in the error message table.
 *----------------------------------------------------------------------*/

VOID  CTYP   ErrorExit(IntT e)
{
   if(e)
   {  if(e == 1)                       /* window-system error           */
      {  if(Wperror(WerrMsg()))        /* use window if possible    jpl */
            Werror();
      }
      else                             /* look up error message         */
      {  if (Wperror(error_text[e]))   /* use window if possible    jpl */
            printf("\n%s\n", error_text[e]);
      }
      CurPop();                        /* restore cursor                */
      exit(e);                         /* _TcxlTerm() will clean up     */
   }
}  /* ErrorExit() */

/*===============[ Save the screen image on the far heap ]==============*/

#if (_TCXL_dat_ == 0)      /* small data memory models -- use far heap  */

VcelFP   CTYP  FarVsave(AtrT Atr)
{
   VcelFP   FarPtr;
   VcelP    NearPtr;
#if   (_TCXL_cc_ == 22)                /* Zortech uses a DwdT           */
   DwdT     sz;
#else                                  /* everybody else uses a WrdT    */
   WrdT     sz;
#endif

   if(NULL == (NearPtr = Vsave()))     /* normal Vsave()                */
      ErrorExit(3);                    /* out of memory!                */

   sz = (VidDep * VidWid * SIZ(VcelT)) + 1;
   if(NULL == (FarPtr = (VcelFP)farmalloc(sz)))
      ErrorExit(4);                    /* out of far heap!              */

   _PutFar((BytFP)FarPtr, (BytP)NearPtr, sz);   /* copy to far heap     */
   free(NearPtr);                      /* free normal buffer            */
   Vclear(Atr);                        /* clear the screen              */
   return(FarPtr);                     /* return far-heap pointer       */
}  /* FarVsave() */

#else                      /* large data memory models -- use near heap */

VcelFP   CTYP  FarVsave(AtrT Atr)
{
   VcelP    NearPtr;

   if(NULL == (NearPtr = Vsave()))     /* normal Vsave()                */
      ErrorExit(3);                    /* out of memory!                */

   Vclear(Atr);                        /* clear the screen              */
   return(NearPtr);                    /* return heap pointer           */
}

#endif

/*===========[ Restore saved screen image from the far heap ]===========*/

#if (_TCXL_dat_ == 0)      /* small data memory models -- use far heap  */

VOID  CTYP  FarVrestore(VcelFP FarPtr)
{
   VcelP    NearPtr;
   WrdT     sz;

   sz = (VidDep * VidWid * SIZ(VcelT)) + 1;
   if(NULL == (NearPtr = (VcelP) malloc(sz)))
      ErrorExit(3);                    /* out of memory!                */

   _GetFar((BytP)NearPtr, (BytFP)FarPtr, sz);   /* copy from far heap   */
   farfree(FarPtr);                    /* free far buffer               */
   Vrestore(NearPtr);                  /* restore the screen            */
}  /* FarVrestore() */

#else                      /* large data memory models -- use near heap */

VOID  CTYP  FarVrestore(VcelFP FarPtr)
{
   Vrestore(FarPtr);
}

#endif

/*===============[ Initialize TCXL for the demo program ]===============*/

VOID  CTYP  Initialize(NOARG)
{
#if(_TCXL_cc_ == 25)                   /* needed for Watcom C           */
   _heapgrow();
#endif
   TcxlInit();                         /* general initialization        */
   KextOff();                          /* no extended key BIOS          */
   CurPush(CUR_HID, CUR_NOR, 0, 0);    /* save the cursor state, hide   */
                                       /*    and home the cursor        */
   savescrn = FarVsave(LGREY|_BLACK);  /* save the screen               */

   KbndSet(Key_A_X, ConfirmQuit, 0);   /* bind [Alt-X] to ConfirmQuit() */

   HlpDef("TCXLDEMO.HLP", Key_F1,      /* initialize help system,       */
      YELLOW|_RED, YELLOW|_RED,        /*  help key = [F1]              */
      LRED|_RED, WHITE|_RED, RED|_LGREY, BOX_DBL, _VFVCP(PreHelp));

   LeftRow = ((VidDep - 1) / 2) - 5;   /* set up display coordinates    */
   RightRow = LeftRow + 6;
   LeftCol = ((VidWid - 1) / 2) - 9;
   RightCol = LeftCol + 19;

}  /* Initialize() */

/*================[ Define and process a main demo menu ]===============*
 | First, push global help category onto help stack, so that when [F1] is
 | pressed while the selection bar is on an item without help, the global
 | help category will be used. Build the main menu defined by the Mbld
 | object at <mp> and process it
 *----------------------------------------------------------------------*/

VOID  CTYP  MainMenu(MbldP mp)
{
   HlpPush(H_GLOBAL);                  /* push global help catagory     */

   MnuBuild(mp);                       /* define the main menu          */
   if(MnuGet() == -1)                  /* process the menu              */
      if(TcxlErr > W_ESCPRESS)
         ErrorExit(1);                 /* window error                  */

   HlpDrop();                          /* pop help category off stack   */
}  /* MainMenu() */

/*===========[ Move the selection bar down in the Main Menu ]===========*
 | Select the next menu item by getting the address of the current menu,
 | then setting the current tag-id to the tag-id of the next menu item.
 | If we had had not numbered the menu item tag-ids sequentially, this
 | would not work.
 *----------------------------------------------------------------------*/

VOID  CTYP  MoveBarDn(NOARG)
{
   REG TagT t = IdfTag(ItmCur());
   if(t < 10)                          /* from main menu only           */
      ItmNxt(t + 1);                   /* select next item              */
}  /* MoveBarDn() */

/*========================[ Normal termination ]========================*
 | Restore the original screen and cursor before exiting to DOS with
 | ERRORLEVEL 0.
 *----------------------------------------------------------------------*/

VOID  CTYP  NormalExit(NOARG)
{
   FarVrestore(savescrn);              /* restore the screen            */
   MouPop();                           /* restore the mouse             */
   CurPop();                           /* restore the cursor            */
   exit(0);                            /* _TcxlTerm() will clean up     */
}  /* NormalExit() */


/*==[ Main background, program title and system information windows ]===*/

ChrT Ins1[] = "INSTALLED";
ChrT Ins2[] = "NOT INSTALLED";

VOID  CTYP  OpenBkgrnd(NOARG)
{
   ChrT  str[90];
                                       /* demo background window        */
   if(ERR_ARG == Wopen(0, 0, VidDep - 2, VidWid - 1, 5, 0, LGREEN|_GREEN))
      ErrorExit(1);                    /* windowing error!              */

                                       /* system information pop-up     */
   if(!WpopUp(CNT_HOR, VidDep - 8, 0, VidDep - 3, 60, 0, LGREY|_RED,
         LGREY|_RED))
      ErrorExit(1);                    /* windowing error!              */

   AddShadow();                        /* add a shadow, display status  */
#if defined(_TCXLos2_)
   sprintf(str, "OS/2 version: %d.%d\n",
      (_SysVer >> 8) & 0xFF, _SysVer & 0xFF);
   WputCen(str);

   sprintf(str, "This program is running as a %s application\n",
      _SysFul ? "full-screen" : "VIO-windowed");
   WputCen(str);

   sprintf(str, "in screen group %d.\n", _SysSgp);
   WputCen(str);

   sprintf(str, "Process ID: %d   Parent's process ID: %d",
      _SysPid, _SysPpd);
   WputCen(str);
#else
   sprintf(str, "DPMI Status: %s   VCPI Status: %s\n",
      (MemDPMI ? Ins1 : Ins2),
      (MemVCPI ? Ins1 : Ins2));
   WputCen(str);

   sprintf(str, "Total EMS: %dK   Free EMS: %dK\n",
      MemEtot * 16, MemEfre * 16);
   WputCen(str);

   sprintf(str, "Free XMS: %dK   HMA is %s\n", MemXtot,
      (MemHfre ? "AVAILABLE" : "IN USE"));
   WputCen(str);

   sprintf(str, "Ultravision is %s   Screen Size is %dx%d",
      (TcxlUv ? Ins1 : Ins2), VidWid, VidDep);
   WputCen(str);
#endif

   WsetFil('\xB0');                    /* bottom status bar, fancy fill */
   if(ERR_ARG == Wopen(VidDep - 1, 0, VidDep - 1, VidWid - 1, 5, 0, 
         LGREY|_RED))
      ErrorExit(1);                    /* windowing error!              */

   Wprts(0, 1, LGREY|_RED, "[F1]=Help");
   WprtCen(0, LGREY|_RED, "Select demonstration to view.");
   Wprtrj(0, MsByt(VidWid - 2), LGREY|_RED, "[Alt-X]=Quit");
   WsetFil(' ');                       /* blank fill again              */
                                       /* program title pop-up          */
   if(!WpopUp(CNT_HOR, 0, 12, 4, 67, 0, LRED|_MAGENTA, LRED|_MAGENTA))
      ErrorExit(1);                    /* windowing error!              */

   AddShadow();                        /* add a shadow, display text    */
   WprtCen(0, WHITE|_MAGENTA,
      "Welcome to the TesSeRact CXL Demonstration Program!");
   WprtCen(2, LCYAN|_MAGENTA,
      "Copyright (c) 1987-1991, Innovative Data Concepts");
}  /* OpenBkgrnd() */

/*=======[ Parse the command line for valid invocation switches ]=======*
 | If any valid switches are found, set the appropriate video variable.
 | If any invalid switches are found, display a syntax message. <ac> and
 | <av> are the <argc> and <argv> arguments to main().
 *----------------------------------------------------------------------*/

VOID  CTYP  ParseCmdLine(IntT ac, ChrP av[])
{
   REG IntT    i, j;
   ChrP        p;

   for(i = 1; i < ac; i++)
   {  p = av[i];
      if(*p == '-' || *p == '/')
      {  for(j = 1; *(p + j); j++)
         {  switch(NlsToLower(*(p + j)))
            {  case 'c':               /* CGA video                     */
                  VidParm(VP_CGA);
                  break;

               case 'b':               /* BIOS video                    */
                  VidParm(VP_BIO);
                  break;

               case 'm':               /* monochrome video              */
                  VidParm(VP_MON);
                  break;

               default:                /* unknown switch                */
                  ErrorExit(2);        /* syntax error!                 */
            }
         }
      }
      else                             /* unknown parameter             */
         ErrorExit(2);                 /* syntax error!                 */
   }
}  /* ParseCmdLine() */

/*======[ Parse a MMDDYY date string into separate numeric values ]=====*
 | <b> is the date string, <m>, <d>, and <y> point to integers to receive
 | the month, day and year
 *----------------------------------------------------------------------*/

VOID  CTYP  ParseDate(ChrP b, IntP m, IntP d, IntP y)
{
   ChrT  t[7];

   strcpy(t, b);
   *y = 1900 + atoi(t + 4);            /* year                          */
   *(t + 4) = EOS;
   *d = atoi(t + 2);                   /* day                           */
   *(t + 2) = EOS;
   *m = atoi(t);                       /* month                         */
}  /* ParseDate() */

/*=======================[ Help "open" function ]=======================*
 | Called when the user presses the help key and the help window is
 | opened.
 *----------------------------------------------------------------------*/

VOID  CTYP  PreHelp(NOARG)
{
   AddShadow();                        /* add a shadow to window        */
   KbndSet(Key_A_X, ConfirmQuit, 0);   /* bind Alt[X] as exit key       */
}  /* PreHelp() */

/*=====================[ Main menu "open" function ]====================*
 | Called when the main demo menu window is opened.
 *----------------------------------------------------------------------*/

VOID  CTYP  PreMenu1(NOARG)
{
   AddShadow();                        /* add a shadow                  */
}  /* PreMenu1() */

/*======[ Display a pause message, then pause for for a keypress ]======*
 | <r> is the window-row to display on.
 *----------------------------------------------------------------------*/

VOID  CTYP  PressAKey(BytT r)
{
   PressAKey1(r, 36);                  /* wait for 2 seconds            */
}  /* PressAKey() */

/*======[ Display a pause message, then pause for for a keypress ]======*
 | <r> is the window-row to display on, <w> is the number of clock-ticks
 | to wait.
 *----------------------------------------------------------------------*/

VOID  CTYP  PressAKey1(BytT r, IntT w)
{
   AtrT a;

   if(DemoFast)                        /* check for window-demo delay   */
      return;

   a = MsAtr((_BLINK|YELLOW)|(WdfDat(WctlAct) & (~WHITE)));      /* jpl */
   WprtCen(r, a, "Press a key");       /* display message               */
   if(w == -1)
      KeyWait();                       /* wait for a key                */
   else
   {  if((ChrT)KeyTime(w) == ESC)      /* quit on [Esc]                 */
         ConfirmQuit();
   }
   WprtCen(r, a, "           ");       /* erase message                 */
}

/*=========[ Display window of information about TCXL and IDC ]=========*
 | Called from the [I]nformation item in the main demo menu
 *----------------------------------------------------------------------*/

VOID  CTYP  TcxlInfo(NOARG)
{
   HlpAdd(H_GLOBAL);                   /* save old, set new help  y     */
   HlpGet();
   HlpDrop();
}  /* TcxlInfo() */
