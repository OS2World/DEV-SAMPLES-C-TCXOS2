/*=====[ The TesSeRact(TM) CXL User Interface Development System ]======*
 | Copyright (c) 1987-1991, Innovative Data Concepts, Inc.
 | All Rights Reserved.
 |
 | This Library is part of IDC's TesSeRact Development Tools product
 | line. For information about other IDC products, call  1-215-443-9705.
 *-V--------------------------------------------------------------------*
 | $Header:   D:/beta/version/str_demo.c_v   552.2   22 Jun 1991 14:03:52  $
 |
 | $Log:   D:/beta/version/str_demo.c_v  $
 | 
 |    Rev 552.2   22 Jun 1991 14:03:52
 | check correct return value from Wopen
 | 
 |    Rev 552.1   17 Mar 1991 20:03:02
 | Version 5.52 (after unlog/build)
 *-D--------------------------------------------------------------------*
 | Str_Demo.C : Demonstration of TCXL string system. The demo consists of
 | a selection-list of demonstration types which is used to select an
 | element of a control structure, then invoke and display the code for
 | and display the results of the selected operations.  StringDemo() is
 | invoked from the main menu of Mid_Demo.C.
 *-N-----------------------[ Notes and Caveats ]------------------------*
 | 1) Use the MakeDemo.Bat file to compile this file.
 *======================================================================*/
#include <string.h>
#include <stdlib.h>
#include "demo\TCXLdemo.h"             /* TCXL demo-specific            */
#include <TCXLsel.h>                   /* TCXL selection/window/video   */
#include <TCXLstr.h>                   /* TCXL strings                  */

/*----------------------------[ Local data ]----------------------------*/

LCL   ChrP  CDC   BefAft =             /* Before/after format           */
   " Before: <%s>\n  After: <%s>\n";

ChrP  CDC   sDstrmatch[] =             /* sample demo-source text       */
{
   "VOID CTYP  Dstrmatch(NOARG)\n",
   "{\n",
   "  ChrP strings[] = { \"Hello\", \"There\", \"Computer\", \"World\", "
      "NULL };\n",
   "  ChrP str1 = \"xhelpx\";\n",
   "  IntT i = 0;\n",
   "\n",
   "  while(strings[i] != NULL)\n",
   "  {\n",
   "    Wputf(\" <%s> vs. <%s> = <%d>\\n\", \n",
   "      str1, strings[i], strmatch(str1, strings[i]));\n",
   "    i++;\n",
   "  }\n",
   "\n",
   "  Wputf(\" <%s> best matches <%s>\\n\", str1, strbmatch(str1, string"
      "s));\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrtrim[] =
{
   "VOID CTYP  Dstrtrim(NOARG)\n",
   "{\n",
   "  ChrP str1 = \"     Hello, world     \";\n",
   "  ChrT str2[25];\n",
   "\n",
   "  strcpy(str2, str1);\n",
   "  strltrim(str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "\n",
   "  strcpy(str2, str1);\n",
   "  strrtrim(str2);      /* identical to strtrim() */\n",
   "  Wputf(BefAft, str1, str2);\n",
   "\n",
   "  strcpy(str2, str1);\n",
   "  strbtrim(str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrchg[] =
{
   "VOID CTYP  Dstrchg(NOARG)\n",
   "{ ChrP str1 = \"HelLo, worLd\";\n",
   "  ChrP str2 = \"Hello, world\";\n",
   "  ChrP str3 = \"xxxhElLoyyyHElLOzzz\";\n",
   "  ChrP str4 = \"xxxhElloyyyhellozzz\";\n",
   "  ChrT str5[30];\n",
   "\n",
   "  strcpy(str5, str1);\n",
   "  strchg(str5, 'l', 'z');\n",
   "  Wputf(BefAft, str1, str5);\n",
   "\n",
   "  strcpy(str5, str2);\n",
   "  strichg(str5, 'l', 'z');\n",
   "  Wputf(BefAft, str2, str5);\n",
   "\n",
   "  strcpy(str5, str3);\n",
   "  strischg(str5, \"HeLlO\", \"goodbye\");\n",
   "  Wputf(BefAft, str3, str5);\n",
   "\n",
   "  strcpy(str5, str4);\n",
   "  strschg(str5,\"hello\",\"goodbye\");\n",
   "  Wputf(BefAft, str4, str5);\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrchksum[] =
{
   "VOID CTYP  Dstrchksum(NOARG)\n",
   "{\n",
   "  ChrP str1 = \"Hello, world\";\n",
   "\n",
   "  Wputf(\"Checksum is %lu, I-Checksum is %lu\\n\",\n",
   "    strchksum(str1), strichksum(str1));\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrdel[] =
{
   "VOID CTYP  Dstrdel(NOARG)\n",
   "{\n",
   "  ChrP str1 = \"XyZHello, xYzworldXyZxYz\";\n",
   "  ChrT str2[35];\n",
   "  \n",
   "  strcpy(str2, str1);\n",
   "  strdel(\"xYz\", str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "  strcpy(str2, str1);\n",
   "  strdela(\"xYz\", str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "  strcpy(str2, str1);\n",
   "  stridel(\"xYz\", str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "  strcpy(str2, str1);\n",
   "  stridela(\"xYz\", str2);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "  strcpy(str1, str2);\n",
   "  strins(\"xYz\", str2, 4);\n",
   "  Wputf(BefAft, str1, str2);\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrinc[] =
{
   "VOID CTYP  Dstrinc(NOARG)\n",
   "{\n",
   "  ChrP str1 = \"Hello1HELLO2HeLlO3hElLo\";\n",
   "  ChrP str2 = \"hello\";\n",
   "\n",
   "  Wputf(\"str2 is %sincluded in str1\\n\",\n",
   "    ( (strinc(str2,str1) == NULL) ? \n",
   "    \"not \" : \"\"));\n",
   "\n",
   "  Wputf(\"str2 is %sincluded in str1\\n\",\n",
   "    ( (striinc(str2,str1) == NULL) ? \n",
   "    \"not \" : \"\"));\n",
   "\n",
   "  Wputf(\"There are %d occurrences of '%c' in str1\\n\",\n",
   "            strocc(str1, 'l'), 'l');\n",
   "  Wputf(\"There are %d occurrences of '%c' in str1\\n\",\n",
   "            striocc(str1, 'l'), 'l');\n",
   "\n",
   "  Wputf(\"str2 occurs in str1 %d times\\n\",\n",
   "    strsocc(str2, str1));\n",
   "  Wputf(\"str2 occurs in str1 %d times\\n\",\n",
   "    strisocc(str2, str1));\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrsrep[] =
{
   "VOID CTYP  Dstrsrep(NOARG)\n",
   "{\n",
   "  ChrP str1 = \"This is a big string\";\n",
   "  ChrT str2[25];\n",
   "\n",
   "  strcpy(str2, str1);\n",
   "  strsrep(str2, \"str\", \"th\");\n",
   "  Wputf(BefAft, str1, str2);\n",
   "\n",
   "  strcpy(str2, str1);\n",
   "  strisrep(str2, \"str\", \"th\");\n",
   "  Wputf(BefAft, str1, str2);\n",
   "\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrmid[] =
{
   "VOID CTYP  Dstrmid(NOARG)\n",
   "{\n",
   "  ChrP p;\n",
   "  ChrP str = \"Hello, world\";\n",
   "\n",
   "  Wputf(\"    %s\\n\", p = strmid(str, 5, 5));\n",
   "  free(p);\n",
   "\n",
   "  Wputf(\"    %s\\n\", p = strleft(str, 5));\n",
   "  free(p);\n",
   "\n",
   "  Wputf(\"    %s\\n\", p = strright(str, 5));\n",
   "  free(p);\n",
   "  \n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrljust[] =
{
   "VOID CTYP  Dstrljust(NOARG)\n",
   "{ ChrP str1 = \"     Hello, world     \";\n",
   "  ChrP str2 = \"Hello, world\";\n",
   "  ChrT str3[25];\n",
   "  strcpy(str3, str1);\n",
   "  strljust(str3);\n",
   "  Wputf(BefAft, str1, str3);\n",
   "  strcpy(str3, str1);\n",
   "  strrjust(str3);\n",
   "  Wputf(BefAft, str1, str3);\n",
   "  strcpy(str3, str2);\n",
   "  strrol(str3, 3);\n",
   "  Wputf(BefAft, str2, str3);\n",
   "  strcpy(str3, str2);\n",
   "  strror(str3, 3);\n",
   "  Wputf(BefAft, str2, str3);\n",
   "  strcpy(str3, str2);\n",
   "  strshl(str3, 3);\n",
   "  Wputf(BefAft, str2, str3);\n",
   "  strcpy(str3, str2);\n",
   "  strshr(str3, 3);\n",
   "  Wputf(BefAft, str2, str3);\n",
   "}\n",
   NULL,
};
ChrP  CDC   sDstrblank[] =
{
   "VOID CTYP  Dstrblank(NOARG)\n",
   "{ ChrP str1 = \"  Hello  \";\n",
   "  ChrP str2 = \" \\n  \\t \\r \";\n",
   "  ChrP str3 = \"Hello, world\";\n",
   "  ChrP str4 = \"hElLo, wOrLd\";\n",
   "  ChrT str5[20];\n",
   "  Wputf(\" str1 is %sblank\\n\", strblank(str1) ? \"\" : \"not \");\n",
   "  Wputf(\" str2 is %sblank\\n\", strblank(str2) ? \"\" : \"not \");\n",
   "  Wputf(\" Before:    <%s>\\n\", str3);\n",
   "  strcode(str3, \"34&*#Mdq\");\n",
   "  Wputf(\" Encrypted: <%s>\\n\", str3);\n",
   "  strcode(str3, \"34&*#Mdq\");\n",
   "  Wputf(\" Decrypted: <%s>\\n\", str3);\n",
   "  strcpy(str5, str3);\n",
   "  Wputf(\" Before:  <%s>\\n\", str5);\n",
   "  strsetsz(str5, 20);\n",
   "  Wputf(\" Len=20:  <%s>\\n\", str5);\n",
   "  strsetsz(str5, 5);\n",
   "  Wputf(\" Len=5:   <%s>\\n\", str5);\n",
   "  strcpy(str5, str4);\n",
   "  struplow(str5);\n",
   "  Wputf(BefAft, str4, str5);\n",
   "}\n",
   NULL,
};

LCL   ChrP  CDC   Dstrings[] =         /* text for strings demo         */
{
   "Hello", "There", "Computer", "World", NULL
};

LCL   ChrP Sdemo1[] =                  /* Selection items/titles        */
{
   "Trimming",    "Changing",       "Checksum",    "Delete/Insert",
   "Inclusion",   "Replacement",    "Substrings",  "Justification",
   "Matching",    "Miscellaneous",  "Exit",        NULL
};

TYP struct _StrDmo
{
   ChrI  Dsp;                          /* sample source text array      */
   VfvCP Fun;                          /* demo function                 */
   IntT  Wrws;                         /* coords for result window      */
   IntT  Wcls;                         /* "      "   "      "           */
}   STRDMO;

/*---------------------[ Local function prototypes ]--------------------*/

LCL   VOID  CTYP  Dstrmatch(NOARG);
LCL   VOID  CTYP  Dstrtrim(NOARG);
LCL   VOID  CTYP  Dstrchg(NOARG);
LCL   VOID  CTYP  Dstrchksum(NOARG);
LCL   VOID  CTYP  Dstrdel(NOARG);
LCL   VOID  CTYP  Dstrinc(NOARG);
LCL   VOID  CTYP  Dstrsrep(NOARG);
LCL   VOID  CTYP  Dstrmid (NOARG);
LCL   VOID  CTYP  Dstrljust(NOARG);
LCL   VOID  CTYP  Dstrblank(NOARG);

STRDMO Sdemo[] =                       /* string demo control object    */
{                                      /* _VFVCP casts are for C++      */
   {  sDstrtrim,   _VFVCP(Dstrtrim),    9, 35  },
   {  sDstrchg,    _VFVCP(Dstrchg),    11, 36  },
   {  sDstrchksum, _VFVCP(Dstrchksum),  5, 19  },
   {  sDstrdel,    _VFVCP(Dstrdel),    13, 37  },
   {  sDstrinc,    _VFVCP(Dstrinc),    11, 32  },
   {  sDstrsrep,   _VFVCP(Dstrsrep),    7, 33  },
   {  sDstrmid,    _VFVCP(Dstrmid),     7, 15  },
   {  sDstrljust,  _VFVCP(Dstrljust),  15, 35  },
   {  sDstrmatch,  _VFVCP(Dstrmatch),   8, 32  },
   {  sDstrblank,  _VFVCP(Dstrblank),  13, 34  },
};

/*=======================[ The TCXL Strings demo ]======================*
 | Called from the [S]trings item of the Mid_Demo.C main menu.
 *----------------------------------------------------------------------*/

VOID  CTYP  StringDemo(NOARG)
{
   VcelFP   s;
   IntT     Sel = 0, i;

   s = FarVsave(LGREY|_BLACK);         /* save screen                   */
   MouPush(MOU_FULL);                  /* full mouse support            */
   CurSave();                          /* save cursor state             */
   LeftRow = ((VidDep - 1) / 2) - 6;   /* menu coordinates              */
   RightRow = LeftRow + 12;
   LeftCol = ((VidWid - 1) / 2) - 9;
   RightCol = LeftCol + 16;

   LOOP                                /*- Endless loop ----------------*/
   {                                   /* display selection list        */
      Sel = SelStr(LeftRow, LeftCol, RightRow, RightCol, 1, LCYAN|_BLUE,
         LCYAN|_BLUE, YELLOW|_LGREY, Sdemo1, Sel, NULL);
      if((Sel >= 10) || (Sel < 0))
         break;                        /* time to quit                  */

      if(!WpopUp(CNT_CNT, 0, 0, 24,    /* pop up a demo window          */
            VidWid - 1, 1, LCYAN|_BLUE, LCYAN|_BLUE))
         ErrorExit(1);                 /* windowing error!              */

      Wtitle(Sdemo1[Sel], TTL_CNT, LCYAN|_BLUE);   /* add title         */
      Wmessage(" [Press a Key to Continue ] ",     /* add message       */
         BRD_BOT, MsByt(((VidWid - 1) / 2) - 15), LCYAN|_BLUE);

      i = 0;
      while(Sdemo[Sel].Dsp[i] != NULL) /* display source-code text      */
         Wputs(Sdemo[Sel].Dsp[i++]);
                                       /* open result window            */
      if(ERR_ARG == Wopen(((VidDep - 25) / 2) + 1, 
            VidWid - 1 - Sdemo[Sel].Wcls - 1,
            ((VidDep - 25) / 2) + 1 + Sdemo[Sel].Wrws, VidWid - 2, 0,
            WHITE|_RED, WHITE|_BLUE))
         ErrorExit(1);                 /* can't open the window!        */

      (*Sdemo[Sel].Fun)();             /* invoke the demo function      */
      PressAKey1(MsByt(Sdemo[Sel].Wrws - 2), -1);
      Wclose();                        /* close up windows              */
      Wclose();
      Sel++;                           /* move selection bar down       */
   }  /* LOOP */

   CurPop();                           /* restore cursor state          */
   MouPop();                           /* restore mouse                 */
   FarVrestore(s);                     /* restore screen                */
   KeyClear();                         /* flush any lurking keycodes    */
   MoveBarDn();                        /* next main-menu selection      */
}  /* StringDemo() */

/*-----------------------[ String Matching demo ]-----------------------*/

LCL   VOID  CTYP  Dstrmatch(NOARG)
{
   ChrP  str1 = "xhelpx";
   IntT  i = 0;

   while(Dstrings[i] != NULL)          /* Find best match               */
   {
      Wputf(" <%s> vs. <%s> = <%d>\n",
           str1, Dstrings[i], strmatch(str1, Dstrings[i]));
      i++;
   }

   Wputf(" <%s> best matches <%s>\n", str1, strbmatch(str1, Dstrings));
}  /* Dstrmatch() */

/*-----------------------[ String Trimming demo ]-----------------------*/

LCL   VOID  CTYP  Dstrtrim(NOARG)
{
   ChrP  str1 = "     Hello, world     ";
   ChrT  str2[25];

   strcpy(str2, str1);                 /* Trim leading blanks           */
   strltrim(str2);
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Trim trailing blanks          */
   strrtrim(str2);                     /* identical to strtrim()        */
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Trim leading and trailing     */
   strbtrim(str2);
   Wputf(BefAft, str1, str2);
}  /* Dstrtrim() */

/*-----------------------[ String Changing demo ]-----------------------*/

LCL   VOID  CTYP  Dstrchg(NOARG)
{
   ChrP  str1 = "HelLo, worLd";
   ChrP  str2 = "Hello, world";
   ChrP  str3 = "xxxhElLoyyyHElLOzzz";
   ChrP  str4 = "xxxhElloyyyhellozzz";
   ChrT  str5[30];

   strcpy(str5, str1);                 /* Change all characters         */
   strchg(str5, 'l', 'z');
   Wputf(BefAft, str1, str5);

   strcpy(str5, str2);                 /* Change all case-independent   */
   strichg(str5, 'l', 'z');            /* characters                    */
   Wputf(BefAft, str2, str5);

   strcpy(str5, str3);                 /* Change case-independent       */
   strischg(str5, "HeLlO", "goodbye"); /* substring                     */
   Wputf(BefAft, str3, str5);

   strcpy(str5, str4);                 /* Change substring              */
   strschg(str5, "hello", "goodbye");
   Wputf(BefAft, str4, str5);
}  /* Dstrchg() */

/*-----------------------[ String Checksum demo ]-----------------------*/

LCL   VOID  CTYP  Dstrchksum(NOARG)
{
   ChrP  str1 = "Hello, world";

   Wputf("Checksum is %lu, I-Checksum is %lu\n",
        strchksum(str1), strichksum(str1));
}  /* Dstrchksum() */

/*---------------------[ String Delete/Insert demo ]--------------------*/

LCL   VOID  CTYP  Dstrdel(NOARG)
{
   ChrP  str1 = "XyZHello, xYzworldXyZxYz";
   ChrT  str2[35];

   strcpy(str2, str1);                 /* Delete first substring        */
   strdel("xYz", str2);
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Delete all substrings         */
   strdela("xYz", str2);
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Delete first case-independent */
   stridel("xYz", str2);               /* substring                     */
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Delete all case-independent   */
   stridela("xYz", str2);              /* substrings                    */
   Wputf(BefAft, str1, str2);

   strcpy(str1, str2);                 /* Insert substring              */
   strins("xYz", str2, 4);
   Wputf(BefAft, str1, str2);
}  /* Dstrdel() */

/*-----------------------[ String Inclusion demo ]----------------------*/

LCL   VOID  CTYP  Dstrinc(NOARG)
{
   ChrP  str1 = "Hello1HELLO2HeLlO3hElLo";
   ChrP  str2 = "hello";

                                       /* Case-dependent substring      */
   Wputf("str2 is %sincluded in str1\n",
      ((strinc(str2, str1) == NULL) ? "not " : ""));
                                       /* Case-independent substring    */
   Wputf("str2 is %sincluded in str1\n",
        ((striinc(str2, str1) == NULL) ? "not " : ""));
                                       /* Case-dependent character      */
   Wputf("There are %d occurrences of '%c' in str1\n",
        strocc(str1, 'l'), 'l');
                                       /* Case-independent character    */
   Wputf("There are %d occurrences of '%c' in str1\n",
        striocc(str1, 'l'), 'l');
                                       /* Case-dependent substring      */
   Wputf("str2 occurs in str1 %d times\n",
        strsocc(str2, str1));
                                       /* Case-independent substring    */
   Wputf("str2 occurs in str1 %d times\n",
        strisocc(str2, str1));
}  /* Dstrinc() */

/*----------------------[ String Replacement demo ]---------------------*/

LCL   VOID  CTYP  Dstrsrep(NOARG)
{
   ChrP  str1 = "This is a big string";
   ChrT  str2[25];

   strcpy(str2, str1);                 /* Case-dependent                */
   strsrep(str2, "str", "th");
   Wputf(BefAft, str1, str2);

   strcpy(str2, str1);                 /* Case-independent              */
   strisrep(str2, "str", "th");
   Wputf(BefAft, str1, str2);
}  /* Dstrsrep() */

/*-----------------------[ String Substring demo ]----------------------*/

LCL   VOID  CTYP  Dstrmid(NOARG)
{
   ChrP  p;
   ChrP  str = "Hello, world";

                                       /* Middle substring              */
   Wputf("    %s\n", p = strmid(str, 5, 5));
   free(p);
                                       /* Left substring                */
   Wputf("    %s\n", p = strleft(str, 5));
   free(p);
                                       /* Right substring               */
   Wputf("    %s\n", p = strright(str, 5));
   free(p);
}  /* Dstrmid() */

/*---------------------[ String Justification demo ]--------------------*/

LCL   VOID  CTYP  Dstrljust(NOARG)
{
   ChrP  str1 = "     Hello, world     ";
   ChrP  str2 = "Hello, world";
   ChrT  str3[25];

   strcpy(str3, str1);                 /* Left justify                  */
   strljust(str3);
   Wputf(BefAft, str1, str3);

   strcpy(str3, str1);                 /* Right justify                 */
   strrjust(str3);
   Wputf(BefAft, str1, str3);

   strcpy(str3, str2);                 /* Rotate left                   */
   strrol(str3, 3);
   Wputf(BefAft, str2, str3);

   strcpy(str3, str2);                 /* Rotate right                  */
   strror(str3, 3);
   Wputf(BefAft, str2, str3);

   strcpy(str3, str2);                 /* Shift left                    */
   strshl(str3, 3);
   Wputf(BefAft, str2, str3);

   strcpy(str3, str2);                 /* Shift right                   */
   strshr(str3, 3);
   Wputf(BefAft, str2, str3);
}  /* Dstrljust() */

/*---------------------[ String Miscellaneous demo ]--------------------*/

LCL   VOID  CTYP  Dstrblank(NOARG)
{
   ChrP  str1 = "  Hello  ";
   ChrP  str2 = " \n  \t \r ";
   ChrP  str3 = "Hello, world";
   ChrP  str4 = "hElLo, wOrLd";
   ChrT  str5[25];
                                       /* Test for blank                */
   Wputf(" str1 is %sblank\n", strblank(str1) ? "" : "not ");
   Wputf(" str2 is %sblank\n", strblank(str2) ? "" : "not ");

   Wputf(" Before:    <%s>\n", str3);  /* Encrypt/Decrypt               */
   strcode(str3, "34&*#Mdq");
   Wputf(" Encrypted: <%s>\n", str3);
   strcode(str3, "34&*#Mdq");
   Wputf(" Decrypted: <%s>\n", str3);

   strcpy(str5, str3);                 /* Adjust size                   */
   Wputf(" Before:  <%s>\n", str5);
   strsetsz(str5, 20);
   Wputf(" Len=20:  <%s>\n", str5);
   strsetsz(str5, 5);
   Wputf(" Len=5:   <%s>\n", str5);

   strcpy(str5, str4);                 /* Convert to Initial-capitals   */
   struplow(str5);
   Wputf(BefAft, str4, str5);
}  /* Dstrblank() */

/*- end of Str_Demo.C --------------------------------------------------*/

