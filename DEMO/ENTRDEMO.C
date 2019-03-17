/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/entrdemo.c_v   552.17   27 Sep 1991 14:22:14  $
 |
 | $Log:   D:/beta/version/entrdemo.c_v  $
 | 
 |    Rev 552.17   27 Sep 1991 14:22:14
 | copy correct string in PickCompiler
 | 
 |    Rev 552.16   26 Sep 1991 16:23:58
 | make zortech even smaller
 | 
 |    Rev 552.15   26 Sep 1991  8:24:06
 | use new FldUpd function
 | 
 |    Rev 552.14   31 Aug 1991 14:04:26
 | make zortech fit
 | 
 |    Rev 552.13   26 Jun 1991 12:57:24
 | Fix Typos
 | 
 |    Rev 552.12   26 Jun 1991 12:39:20
 | fix demo compiler selection
 | 
 |    Rev 552.11   21 Jun 1991 16:24:30
 | code consolidation/reduction
 | 
 |    Rev 552.10   20 Jun 1991 16:38:50
 | remove unused local
 | 
 |    Rev 552.9   17 Jun 1991  7:18:00
 | remove printorder
 | 
 |    Rev 552.8   13 Jun 1991  4:55:12
 | use NlsYes for GetYn prompts
 | 
 |    Rev 552.7   21 Apr 1991 12:01:58
 | add unix compatibility updates
 | 
 |    Rev 552.6   09 Apr 1991  0:13:44
 | have PickCompiler access format fields directly
 | 
 |    Rev 552.5   05 Apr 1991  6:38:08
 | Fix Typos
 | 
 |    Rev 552.4   05 Apr 1991  6:35:42
 | clear the field before stuffing in PickCompiler
 | 
 |    Rev 552.3   04 Apr 1991 17:50:36
 | Make EntKey() last-key buffer work correctly
 |
 |    Rev 552.2   23 Mar 1991  9:50:06
 | account for NlsYes characters in GetYn prompts
 |
 |    Rev 552.1   17 Mar 1991 20:02:56
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | EntrDemo.C : Demonstration of the TCXL entry system.
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Use the MakeDemo.Bat file to compile this file.
 | 2) This demo makes use of new TCXL 5.52 EntBuild() and MnuBuild()
 |    facilities.  See <TCXLent.h> and <TCXLmnu.h> for further
 |    information about them
 *======================================================================*/
#include "demo\TCXLdemo.h"
#include <TCXLstr.h>
#include <TCXLent.h>
#include <TCXLprn.h>
#include <TCXLcod.h>
#include <string.h>

LCL   VOID  CTYP  EntMode(BytT im);

/*----------------------------[ Local data ]----------------------------*/

#define  DEMO_CNT 13

LCL   ChrT  CDC   date[7];             /* entry field buffers           */
LCL   ChrT  CDC   firstname[16];       /* ALLOW SPACE FOR TRAILING NUL! */
LCL   ChrT  CDC   initial[2];
LCL   ChrT  CDC   lastname[26];
LCL   ChrT  CDC   address[41];
LCL   ChrT  CDC   city[21];
LCL   ChrT  CDC   state[3];
LCL   ChrT  CDC   zipcode[10];
LCL   ChrT  CDC   phone[11];
LCL   ChrT  CDC   compiler[16];
LCL   ChrT  CDC   amtenc[8];
LCL   ChrT  CDC   comments[71];
LCL   ChrT  CDC   company[41];

/*---------------------[ Local function prototypes ]--------------------*/

LCL   IntT  CTYP  CheckDate(ChrP b);
LCL   VOID  CTYP  DisplayDate(NOARG);
LCL   VOID  CTYP  EntMode(BytT im);
LCL   KeyT  CTYP  GetKey(NOARG);
LCL   VOID  CTYP  PickCompiler(NOARG);

/*----------[ Demo entry form-build and field-build objects ]-----------*
 | These must be defined here to reference local functions.
 *----------------------------------------------------------------------*/

LCL   FbldT   CDC   DemFld[DEMO_CNT] =    /*- field-build object list --*/
{  {  "Date",        1,  3, date,         /* prompt, buffer             */
       1, 16, "<01>#'/'<0123>#'/'##",     /* position, format           */
      NULL, CheckDate, DisplayDate,       /* "before", "valid", "after" */
      Key_A_D,  1, H_DATE,                /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "First Name",  3,  3, firstname,    /* prompt, buffer             */
       3, 16, "MMMMMMMMMMMMMMM",          /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_F,  2, H_FIRSTNAME,           /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "Initial",     3, 37, initial,      /* prompt, buffer             */
      3, 47, "U'.'",                      /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_I,  3, H_INITIAL,             /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "Last Name",   5,  3, lastname,     /* prompt, buffer             */
       5, 16, "MMMMMMMMMMMMMMMMMMMMMMMMM",/* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_L,  4, H_LASTNAME,            /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "Company",     7,  3, company,      /* prompt, buffer             */
       7, 16, "****************************************",
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_O,  5, H_NONE,                /* hotkey, item-tag, help-tag */
      FLD_MIX | FLD_TRM, 0, FLD_INI       /* features, user, input-mode */
   },
   {  "Address",     9,  3, address,      /* prompt, buffer             */
       9, 16, "****************************************",
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_A,  6, H_NONE,                /* hotkey, item-tag, help-tag */
      FLD_MIX | FLD_TRM, 0, FLD_INI       /* features, user, input-mode */
   },
   {  "City",       11,  3, city,         /* prompt, buffer             */
      11, 16, "MMMMMMMMMMMMMMMMMMMM",     /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_C,  7, H_CITY,                /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "State",      11, 41, state,        /* prompt, buffer             */
      11, 50, "UU",                       /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_S,  8, H_STATE,               /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "Zip Code",   13,  3, zipcode,      /* prompt, buffer             */
      13, 16, "#####'-'%%%%",             /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_Z,  9, H_ZIPCODE,             /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   },
   {  "Phone",      13, 31, phone,        /* prompt, buffer             */
      13, 40, "'('###') '###'-'####",     /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_P, 10, H_NONE,                /* hotkey, item-tag, help-tag */
      FLD_NWR | FLD_TRM, 0, FLD_INI       /* features, user, input-mode */
   },
   {  "Compiler",   15,  3, compiler,     /* prompt, buffer             */
      15, 16, "***************",          /* position, format           */
      PickCompiler, NULL, NULL,           /* "before", "valid", "after" */
      Key_A_O, 11, H_COMPILER,            /* hotkey, item-tag, help-tag */
      FLD_MIX | FLD_TRM, 0, FLD_INI       /* features, user, input-mode */
   },
   {  "Amount",     15, 37, amtenc,       /* prompt, buffer             */
      15, 46, "$$$$.$$",                  /* position, format           */
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_M, 12, H_AMOUNT,              /* hotkey, item-tag, help-tag */
      FLD_CUR | FLD_TRM, 0, FLD_INI       /* features, user, input-mode */
   },
   {  "Comments",   17,  3, comments,     /* prompt, buffer             */
      17, 16, "***********************************\n"
              "***********************************",
      NULL, NULL, NULL,                   /* "before", "valid", "after" */
      Key_A_N, 13, H_NONE,                /* hotkey, item-tag, help-tag */
      FLD_TRM, 0, FLD_INI                 /* features, user, input-mode */
   }
};
LCL   EbldT   CDC   DemFrm =              /*- form-build object --------*/
{  &DemFld[0], DEMO_CNT,                  /* field-build list, count    */
   GetKey, NULL,                          /* getkey(), key-buffer       */
   0, ENT_SAV,                            /* user, options              */
   WHITE|_BLUE, BLUE|_LGREY,              /* prompt, field attributes   */
   WHITE|_LGREY, BLUE|_LGREY              /* highlight, disabled attrs  */
};

/*------[ Pop-up compiler menu item-build and menu buid objects ]-------*/

LCL   IbldT   CDC   EntItm[6] =           /*- item-build objects -------*/
{  {  "Borland C++", 'B', 0,              /* item, quick-sel, feature   */
      0, 0, 1, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   },
   {  "Microsoft C", 'M', 0,              /* item, quick-sel, feature   */
      1, 0, 2, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   },
   {  "Quick C", 'Q', 0,                  /* item, quick-sel, feature   */
      2, 0, 3, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   },
   {  "Turbo C/C++", 'T', 0,              /* item, quick-sel, feature   */
      3, 0, 4, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   },
   {  "Zortech C++", 'Z', 0,              /* item, quick-sel, feature   */
      4, 0, 5, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   },
   {  "TopSpeed C/C++", 'S', 0,           /* item, quick-sel, feature   */
      5, 0, 6, 0, 0, 0,                   /* pos, tag, help, key,, user */
      NULL, NULL, NULL,                   /* "before","select","after"  */
      NULL, NULL                          /* child, description         */
   }
};
LCL   MbldT   CDC   EntMnu =              /*- menu-build object --------*/
{  &EntItm[0], 6,                         /* item-build list, count     */
    7, 22, 14, 38, MNU_VER,               /* start, end, type           */
   BOX_SNG, BLUE|_MAGENTA,                /* frame type, attr           */
   BLUE|_MAGENTA, BLUE|_MAGENTA,          /* window, text attrs         */
   LCYAN|_MAGENTA, 0,                     /* quick, no-select attrs     */
   BLUE|_LGREY, 1, PreMenu1,              /* bar attr, init tag, "open" */
    0, 15, 1,                             /* user, width, offset        */
   0xFF, 0xFF, 0xFF                       /* text desc (unused)         */
};

TYP struct _DoMsg                   /* user type for messages           */
{  ChrP     Msg;
   BytT     Brd;
   BytT     Col;
   AtrT     Atr;
   BytT     Pad;
}  DoMsg, *DoMsgP;

DoMsg Msgs[4] =
{  { "[ $50 Plus $3 S&H ]", BRD_TOP, 42, LCYAN|_BLUE },
   { " [F10]=Finished ",    BRD_BOT,  5, LCYAN|_BLUE },
   { " [F9]=Today ",        BRD_BOT, 25, LCYAN|_BLUE },
   { " [Esc]=Abort ",       BRD_BOT, 45, LCYAN|_BLUE },
};

LCL ChrP CDC EntrMsg1 = "Is this information correct? \033A\076Y\b";

/*========================[ The TCXL Entry Demo ]=======================*
 | Called from the [E]ntry item of the UserDemo.C main menu
 *----------------------------------------------------------------------*/

VOID  CTYP  EntryDemo(NOARG)
{
   REG IntT    i;
   DoMsgP      mp;
   KeyT        k;
   VcelFP      s;
   ChrT        c;

   s = FarVsave(LGREY|_BLUE);          /* save screen                   */
   CurSave();                          /* save cursor state             */
   DemFrm.etrm = &k;                   /* key-buffer                    */

   if(!WpopUp(CNT_CNT, 2, 8, 23, 70, 1, LCYAN|_BLUE, LCYAN|_BLUE))
      ErrorExit(1);                    /* windowing error!              */

   AddShadow();                        /* add shadow, title, notes      */
   Wtitle("[ TCXL Order Form ]", TTL_LFT, LCYAN|_BLUE);
   mp = &Msgs[0];
   for(i = 0; i < 4; i++)
   {  Wmessage(mp->Msg, mp->Brd, mp->Col, mp->Atr);
      mp++;
   }
   HlpPush(H_EDITKEYS);                /* set help category             */
   EntBuild(&DemFrm);                  /* build the form, with prompts  */
   EntSav();                           /* ??? save it for later         */
   LOOP
   {  k =0u;                           /* clear the last-key buffer     */
      if(0 >= EntGet(DemFld[0].ftag))  /* process the form. If [Esc]    */
         break;                        /* was pressed, don't bother     */
                                       /* with confirmation message.    */

      if(!WpopUp(CNT_CNT, 9, 20, 13, 64, 0, WHITE|_CYAN, WHITE|_CYAN))
         ErrorExit(1);                 /* windowing error!              */

      EntrMsg1[32] = NlsYes;

      if(k != Key_F10)                 /* if [F10] was pressed, don't   */
      {                                /* display confirmation message. */
         AddShadow();
         Wputc('\n');                  /* Display confirmation message  */
         WputCen(EntrMsg1);
         KeyClear();
         c = KwGetYn(NlsYes);
      }
      else
         c = 'Y';
      Wclose();
      if(c == 'Y')                     /* all done with form            */
         break;
      EntMode(FLD_CHG);                /* change to update mode         */
   }  /* LOOP */

   EntFree();                          /* free the form                 */
   HlpDrop();                          /* clear help                    */
   Wclose();                           /* close window                  */
   CurPop();                           /* restore original cursor state */
   FarVrestore(s);                     /* restore screen                */
   MoveBarDn();                        /* next selection on main menu   */
}

/*---------[ Validate the Date field in the data entry window ]---------*/

LCL   IntT  CTYP  CheckDate(ChrP b)
{
   IntT  y, m, d;

   if(!strblank(b))                    /* non-blank only                */
   {  ParseDate(b, &m, &d, &y);

      if(m < 1 || m > 12)              /* validate numeric values       */
      {  Wperror("Invalid month");
         return(1);
      }
      if(d < 1 || d > 31)
      {  Wperror("Invalid day");
         return(3);
      }
   }
   return(0);
}  /* CheckDate() */

/*------[ Display the literal equivalent of the MMDDYY date field ]-----*
 | Called immediately after the user leaves the Date field.
 *----------------------------------------------------------------------*/

LCL   VOID  CTYP  DisplayDate(NOARG)
{
#if(_TCXL_cc_ != 22)                   /* no room for Zortech           */
   FdfP  f;
   IntT  m, d, y;

   if(NULL == (f = FldLoc(1)))            /* find address of Date field */
      ErrorExit(1);

   Wgotoxy(1, 37);                        /* clear to end of line       */
   WclrEol();
   if(!strblank(FdfBfr(f)))               /* parse string date into     */
   {  ParseDate(FdfBfr(f), &m, &d, &y);   /* numeric values             */
      Wputf("%s %d, %d", months[m - 1], d, y);
   }
#endif
}  /* DisplayDate() */

/*-------------[ Change input mode of all fields to <im> ]--------------*/

LCL   VOID  CTYP  EntMode(BytT im)
{
   REG EdfP    e = EctlCur;            /* current form                  */
   REG FdfP    f;

   im &= FDF_MOD;                      /* valid bits only               */
   for(f = EdfTop; f <= EdfBot; f++)
   {  FdfFlg(f) &= ~FDF_MOD;           /* update all fields             */
      FdfFlg(f) |= im;
   }
}  /* EntMode() */

/*--------------------[ Alternate get key function ]--------------------*
 | Do a normal keyboard get, with the following user-defined cases:
 | 1) If the key is [F10], exit the form and pass back [F10] in the
 |    last-key buffer.
 | 2) If the key is [F9], fill in today's date via keyboard queue.
 | In order to pass back an [F10] as the last key, we call EntTrm() to
 | put Key_F10 in the buffer and preventing EntGet() from putting the
 | Key_C_Ent we return to exit the form in it.
 *----------------------------------------------------------------------*/

LCL   KeyT  CTYP  GetKey(NOARG)
{
   KeyT  x;
   ChrP  b;

   x = KeyGetc();
#if(_TCXL_cc_ != 22)                   /* no room for Zortech           */
   if(x == Key_F9)                     /* [F9] - fill in today's date   */
   {  b = SysDate(5);                  /* get date as MM/DD/YY          */
      KqueStr(&b[1]);                  /* stuff it                      */
      x = b[0];                        /* return 1st char               */
   }
   else                                /* [F10] - exit the form.  Put   */
#endif
   {  if(x == Key_F10)                 /* Key_F10 in the last-key buffer*/
      {  EntTrm(Key_F10);              /* and return K_C_Ent to exit.   */
         x = Key_C_Ent;
      }
   }
   return(x);
}  /* GetKey() */

/*----------[ Select a compiler - string picking using a menu ]---------*/

LCL   VOID  CTYP  PickCompiler(NOARG)
{
   REG IntT    s;
   FdfP        f;
   KeyT        k;

   HlpCur();                           /* save help category            */
   MnuBuild(&EntMnu);                  /* define a pop-up menu          */
   if((s = MnuGet()) == -1)            /* get user input                */
      ErrorExit(1);                    /* windowing error!              */

   f = FldCur();

   if(s)
      FldUpd(FdfTag(f), EntItm[s-1].istr);

   k = Key_Tab;
   if(FdfPrv(f) || FdfUp(f))
      k = Key_S_Tab;
   KquePut(k);
   HlpPop();                           /* restore help category         */
}  /* PickCompiler() */

/*- end of EntrDemo.C --------------------------------------------------*/

