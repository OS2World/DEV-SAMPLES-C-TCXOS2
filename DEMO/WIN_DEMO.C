/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/win_demo.c_v   552.3   22 Jun 1991 14:03:50  $
 |
 | $Log:   D:/beta/version/win_demo.c_v  $
 | 
 |    Rev 552.3   22 Jun 1991 14:03:50
 | check correct return value from Wopen
 | 
 |    Rev 552.2   21 Apr 1991 12:02:02
 | add unix compatibility updates
 | 
 |    Rev 552.1   17 Mar 1991 20:02:50
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | Win_Demo.C : Demonstration of the TCXL window system. The demo is run
 | twice, once with delays, once without and shows some of the many
 | things that can be done with TCXL windows. WinDemo() is invoked from
 | the main menu of Mid_Demo.C.
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Use the MakeDemo.Bat file to compile this file.
 *======================================================================*/
#include "demo\TCXLdemo.h"

/*----------------------------[ Local data ]----------------------------*/

LCL   WndT  CDC   w[10];               /* window handle array           */

LCL   IntT  CDC   Siz1[] =             /* window sizes                  */
{  19, 19, 24, 24, 24, 19
};
LCL   IntT  CDC   Siz2[] =
{  60, 75, 75, 60, 45, 45
};
LCL   IntT  CDC   Siz3[] =
{   0, 8,  6,  1, 8,  2                /* fix screen overrun        jpl */
};
LCL   IntT  CDC   Siz4[] =
{   0,  4, 19, 13, 35, 39
};
LCL   ChrP  CDC   Wdm =                /* delay/no-delay pause message  */
   "Now that you've had a chance to see the various features "
   "of the TCXL Window System, we'd like to give you a chance "
   "to see the SAME demonstation again . . . this "
   "time, without the built-in delays.  Press any key to "
   "start this one running.  Watch out!";

/*---------------------[ Local function prototypes ]--------------------*/

LCL   VOID  CTYP  ActivDemo(NOARG);
LCL   VOID  CTYP  AttrDemo(NOARG);
LCL   VOID  CTYP  BordDemo(NOARG);
LCL   VOID  CTYP  ChgWindAttr(AtrT battr, AtrT wattr);
LCL   VOID  CTYP  CloseWinDemo(NOARG);
LCL   VOID  CTYP  CopyDemo(NOARG);
LCL   VOID  CTYP  DemoWait(NOARG);
LCL   VOID  CTYP  DisplayTitle(BytT tpos);
LCL   VOID  CTYP  DragWindow(IntT nsrow, IntT nscol);
LCL   VOID  CTYP  HideDemo(NOARG);
LCL   VOID  CTYP  HorzLine(BytT wrow, BytT wcol, IntT count, AtrT attr);
LCL   VOID  CTYP  MoveDemo(NOARG);
LCL   VOID  CTYP  MoveWindow(IntT nsrow, IntT nscol);
LCL   VOID  CTYP  ResizeDemo(NOARG);
LCL   VOID  CTYP  ScrollDemo(NOARG);
LCL   VOID  CTYP  SizeWindow(IntT nerow, IntT necol);
LCL   VOID  CTYP  TLineDemo(NOARG);
LCL   VOID  CTYP  TitleDemo(NOARG);
LCL   VOID  CTYP  VertLine(BytT wrow, BytT wcol, IntT count, AtrT attr);

/*=======================[ The TCXL window demo ]=======================*
 | Called from the [W]indow item of the Mid_Demo.C main menu.
 *----------------------------------------------------------------------*/

VOID  CTYP  WinDemo(NOARG)
{
   VcelFP   s;

   s = FarVsave(LGREY|_BLUE);          /* save screen                   */
   MouPush(MOU_FULL);                  /* full mouse support            */
                                       /* slowly, first, then FAST      */
   for(DemoFast = 0; DemoFast < 2; DemoFast++)
   {  ScrollDemo();                    /* scrolling                     */
      AttrDemo();                      /* attributes                    */
      BordDemo();                      /* borders                       */
      TitleDemo();                     /* titles                        */
      ResizeDemo();                    /* resizing                      */
      TLineDemo();                     /* text lines                    */
      MoveDemo();                      /* moving/dragging               */
      HideDemo();                      /* hiding/unhiding               */
      ActivDemo();                     /* activation                    */
      CopyDemo();                      /* copying                       */
      CloseWinDemo();                  /* close it down                 */
      if(!DemoFast)                    /* warn user not to blink ;-)    */
      {  WpopUp(CNT_CNT, 0, 0, 9, 35, 0, WHITE|_CYAN, YELLOW|_RED);
         Wputsw(Wdm);
         KeyWait();
      }
      else                             /* ask user if he/she missed it  */
      {  WpopUp(CNT_CNT, 0, 0, 2, 25, 0, WHITE|_CYAN, YELLOW|_RED);
         WputCen("Fast enough for you?");
         KeyTime(54);
      }
      Wclose();                        /* close the pop-up              */
   }
   DemoFast = 0;
   MouPop();                           /* restore mouse, screen         */
   FarVrestore(s);
   KeyClear();                         /* clear lurking keys            */
   MoveBarDn();                        /* next main-menu item           */
}  /* WinDemo() */

/*-----------------------[ Window scrolling demo ]----------------------*/

LCL   VOID  CTYP  ScrollDemo(NOARG)
{
   REG IntT    i, j;

   if(ERR_ARG == (w[0] = Wopen(1, 1, 11, 41, 2, LMAGENTA|_RED, LCYAN|_RED)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_SCROLL);                   /* set help category             */

   Wputf("\n  TCXL's window TTY output functions"
         "\n  such as Wputs() and Wputf() allow"
         "\n  scrolling and ANSI-like Escape code"
         "\n  sequences from inside of windows.");
   PressAKey(6);                       /* pause for a keypress          */

   Wgotoxy(8, 0);                      /* set cursor position           */
   for(i = 0; i < 10; i++)
   {  for(j = DGREY; j <= WHITE; j++)
      {  Wputf("\033F%cTCXL  ", j);    /* display "TCXL" over and over  */
         if(!DemoFast)                 /* changing attributes each time */
            _Delay(1);
      }
   }
}  /* ScrollDemo() */

/*-----------------------[ Window attribute demo ]----------------------*/

LCL   VOID  CTYP  AttrDemo(NOARG)
{
   if(ERR_ARG == (w[1] = Wopen(9, 35, 22, 65, 0, YELLOW|_BLUE, LCYAN|_BLUE)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_CHGATTR);                  /* set help category             */

   Wputs("\n  The WchgAtr() function"
        "\n  allows you to change the"
        "\n  attribute of the active"
        "\n  window.");
   PressAKey(6);                       /* pause for a keypress          */

   ChgWindAttr(LMAGENTA|_BLUE, WHITE|_GREEN);   /* change attributes    */
   ChgWindAttr(GREEN|_LGREY, LMAGENTA|_RED);
   ChgWindAttr(YELLOW|_BROWN, LCYAN|_BLUE);
   ChgWindAttr(YELLOW|_MAGENTA, YELLOW|_MAGENTA);
   ChgWindAttr(LCYAN|_MAGENTA, WHITE|_MAGENTA);
}  /* AttrDemo() */

/*---------------------[ Change window attributes ]---------------------*/

LCL   VOID  CTYP  ChgWindAttr(AtrT battr, AtrT wattr)
{
   WchgAtr(battr, wattr);              /* set attributes                */

   DemoWait();
}  /* ChgWindAttr() */

/*------------------------[ Window border demo ]------------------------*/

LCL   VOID  CTYP  BordDemo(NOARG)
{
   REG IntT i;

   HlpSet(H_CHGBORD);                  /* set help category             */
   WsetTxt(LGREEN|_MAGENTA);           /* text attribute                */

   Wputs("\n\n  The Wborder() function is"
           "\n  used to change the style"
           "\n  of the window's border.");
   PressAKey(10);                      /* pause for a keypress          */

   for(i = 5; i >= 0; i--)
   {  Wborder(MsByt(i));               /* keep changing border types    */
      DemoWait();
   }
}  /* BordDemo() */

/*-------------------------[ Window title demo ]------------------------*/

LCL   VOID  CTYP  TitleDemo(NOARG)
{
   if(ERR_ARG == (w[2] = Wopen(5, 20, 19, 45, 3, LCYAN|_GREEN, WHITE|_GREEN)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_WINTITLE);                 /* set help category             */

   Wputs("\n  The Wtitle() function"
         "\n  allows you to give a"
         "\n  window a title.");
   PressAKey(5);                       /* pause for a keypress          */

   DisplayTitle(TTL_LFT);              /* show off titles               */
   DisplayTitle(TTL_RGT);
   DisplayTitle(TTL_CNT);
}  /* TitleDemo() */

/*-----------------------[ Display window title ]-----------------------*/

LCL   VOID  CTYP  DisplayTitle(BytT tpos)
{
   Wtitle("[ My Title ]", tpos, LCYAN|_GREEN);

   DemoWait();
}  /* DisplayTitle() */

/*------------------------[ Window resize demo ]------------------------*/

LCL   VOID  CTYP  ResizeDemo(NOARG)
{
   IntT i;

   HlpSet(H_RESIZE);                   /* set help category             */
   WsetTxt(BLUE|_GREEN);               /* text attribute                */

   Wputs("\n\n\n  The Wsize() function"
             "\n  allows you to resize"
             "\n  the active window.");
   PressAKey(10);                      /* wait for a keypress           */

   for(i = 0; i < 6; i++)              /* resize the window             */
      SizeWindow(Siz1[i], Siz2[i]);
}  /* ResizeDemo() */

/*--------------------------[ Resize a window ]-------------------------*/

LCL   VOID  CTYP  SizeWindow(IntT r, IntT c)
{
   Wsize(r, c);
   DemoWait();
}  /* SizeWindow() */

/*-----------------------[ Window text-line demo ]----------------------*/

LCL   VOID  CTYP  TLineDemo(NOARG)
{
   if(ERR_ARG == (w[3] = Wopen(10, 3, 23, 41, 3, YELLOW|_BLUE, LMAGENTA|_BLUE)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_TEXTLINE);                 /* set help category             */

   Wputs("\n The WdrwHor() & WdrwVer() functions"
         "\n are used for drawing \"smart\" text"
         "\n lines which will even make their "
         "\n own corners and intersections!   ");
   PressAKey(6);                       /* pause for a keypress          */

   HorzLine( 6,  6, 24, LCYAN|_BLUE);  /* draw a fancy box with joins   */
   VertLine( 6,  6,  4, LCYAN|_BLUE);
   HorzLine(10,  6, 24, LCYAN|_BLUE);
   VertLine( 6, 30,  5, LRED|_BLUE);
   VertLine( 6, 18,  5, LRED|_BLUE);
   HorzLine( 7,  6, 25, LRED|_BLUE);
   HorzLine( 9,  6, 25, LGREEN|_BLUE);
   VertLine( 6, 11,  5, LGREEN|_BLUE);
   VertLine( 6, 23,  5, LGREEN|_BLUE);
   HorzLine( 8,  6, 25, LMAGENTA|_BLUE);
}  /* TLineDemo() */

/*----------------------[ Draw a horizontal line ]----------------------*/

LCL   VOID  CTYP  HorzLine(BytT r, BytT c, IntT n, AtrT a)
{
   WdrwHor(r, c, MsByt(n), 3, a);
   DemoWait();
}  /* HorzLine() */

/*-----------------------[ Draw a vertical line ]-----------------------*/

LCL   VOID  CTYP  VertLine(BytT r, BytT c, IntT n, AtrT a)
{
   WdrwVer(r, c, MsByt(n), 3, a);
   DemoWait();
}  /* VertLine() */

/*-------------------------[ Window move demo ]-------------------------*/

LCL   VOID  CTYP  MoveDemo(NOARG)
{
   IntT i;

   if(ERR_ARG == (w[4] = Wopen(4, 2, 20, 35, 2, YELLOW|_CYAN, YELLOW|_CYAN)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_WINMOVE);                  /* set help category             */

   Wputs("\n   To move the active window,"
         "\n   the Wmove() function is"
         "\n   used.");
   PressAKey(5);                       /* pause for a keypress          */

   for(i = 0; i < 6; i++)              /* move it around                */
      MoveWindow(Siz3[i], Siz4[i]);

   Wputs("\n\n   Or if you prefer flashier,"
           "\n   window movement, try"
           "\n   Wslide() instead.");
   PressAKey(9);                       /* pause for a keypress          */

   for(i = 0; i < 6; i++)              /* drag it around                */
      DragWindow(Siz3[i], Siz4[i]);
}  /* MoveDemo() */

/*---------------------------[ Move a window ]--------------------------*/

LCL   VOID  CTYP  MoveWindow(IntT r, IntT c)
{
   if (r+16 >= VidDep)                 /* make Window address       jpl */
      r = VidDep - 17;                 /*   adjust for smaller screens  */

   if(Wmove(r, c))
      ErrorExit(1);                    /* windowing error!              */

   DemoWait();
}  /* MoveWindow() */

/*---------------------------[ Drag a window ]--------------------------*/

LCL   VOID  CTYP  DragWindow(IntT r, IntT c)
{
   if(Wslide(r, c))
      ErrorExit(1);                    /* windowing error!              */

   DemoWait();
}  /* DragWindow() */

/*-----------------------[ Window hide/show demo ]----------------------*/

LCL   VOID  CTYP  HideDemo(NOARG)
{
   REG IntT i;

   HlpSet(H_WINHIDE);                  /* set help category             */
   WsetTxt(YELLOW|_CYAN);              /* text attribute                */

   Wputs("\n\n   The Whide() and Wunhide()"
           "\n   functions are used to hide"
           "\n   and unhide windows.");
   PressAKey(13);                      /* pause for a keypress          */

   for(i = 0; i < 5; i++)
   {  if(Whide())                      /* hide all, front to back       */
         ErrorExit(1);                 /* windowing error!              */

      DemoWait();
   }
   for(i = 0; i < 5; i++)
   {  if(Wunhide(0))                   /* unhide all, back to front     */
         ErrorExit(1);                 /* windowing error!              */

      DemoWait();
   }
}  /* HideDemo() */

/*-----------------------[ Window activate demo ]-----------------------*/

LCL   VOID  CTYP  ActivDemo(NOARG)
{
   REG IntT    i;

   if(ERR_ARG == (w[5] = Wopen(9, 44, 22, 78, 1, LCYAN|_CYAN, WHITE|_CYAN)))
      ErrorExit(1);                    /* windowing error!              */

   HlpSet(H_ACTIVATE);                 /* set help category             */

   Wputs("\n  TCXL's Wactiv() is used to"
        "\n  activate a window, making"
        "\n  it available for windowing"
        "\n  operations.");
   PressAKey(6);                       /* pause for a keypress          */

   for(i = 0; i < 6; i++)
   {  Wactiv(w[i]);                    /* activate windows 0 thru 5    */
      DemoWait();                      /* in order, back to front      */
   }
}  /* ActivDemo() */

/*-------------------------[ Window copy demo ]-------------------------*/

LCL   VOID  CTYP  CopyDemo(NOARG)
{
   HlpSet(H_WINCOPY);                  /* set help category             */
   WsetTxt(LCYAN|_CYAN);               /* text attribute                */

   Wputs("\n\n  The Wcopy() function is used"
           "\n  to copy the active window.");
   PressAKey(9);                       /* pause for a keypress          */

   if(!Wcopy(1, 1))
      ErrorExit(1);                    /* windowing error!              */

   DemoWait();
   if(!Wcopy(3, 40))
      ErrorExit(1);                    /* windowing error!              */

   DemoWait();
}  /* CopyDemo() */

/*---------------------[ Close out the window demo ]--------------------*/

LCL   VOID  CTYP  CloseWinDemo(NOARG)
{
   REG IntT    i;

   for(i = 0; i < 8; i++)
   {  Wclose();                        /* close all windows             */
      DemoWait();
   }
}  /* CloseWinDemo() */

/*-------------------[ Control delay in window demo ]-------------------*/

LCL   VOID  CTYP  DemoWait(NOARG)
{
   if(DemoFast)
#if   defined(__TERMINAL__)            /* if running to TTY         jpl */
      _TTYupdate();                    /* make sure up to date      jpl */
#else                                  /*                           jpl */
      return;                          /* no delay                      */
#endif                                 /*                           jpl */
   else
      _Delay(5);                       /* delay for 5 clock-ticks       */
}

/*- end of Win_Demo.C --------------------------------------------------*/

