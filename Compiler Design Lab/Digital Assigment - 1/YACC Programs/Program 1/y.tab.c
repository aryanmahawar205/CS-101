
#line	12	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
#ifndef	YYSTYPE
#define	YYSTYPE	int
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
#define	NUM	57346
#define	UMINUS	57347
#define YYEOFCODE 1
#define YYERRCODE 2

#line	35	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"


int main() {
    printf("Enter arithmetic expression:\n");
    return yyparse();
}static	const	short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 0,
};
#define	YYNPROD	8
#define	YYPRIVATE 57344
#define	YYLAST	25
static	const	short	yyact[] =
{
   5,   6,   7,   8,   1,   0,  15,   9,  10,   0,
  11,  12,  13,  14,   4,   0,   2,   0,   7,   8,
   3,   5,   6,   7,   8
};
static	const	short	yypact[] =
{
  10,  16,  10,  10,-1000,  10,  10,  10,  10,-1000,
  -5,  11,  11,-1000,-1000,-1000
};
static	const	short	yypgo[] =
{
   0,   4
};
static	const	short	yyr1[] =
{
   0,   1,   1,   1,   1,   1,   1,   1
};
static	const	short	yyr2[] =
{
   0,   3,   3,   3,   3,   2,   3,   1
};
static	const	short	yychk[] =
{
-1000,  -1,   6,  10,   4,   5,   6,   7,   8,  -1,
  -1,  -1,  -1,  -1,  -1,  11
};
static	const	short	yydef[] =
{
   0,  -2,   0,   0,   7,   0,   0,   0,   0,   5,
   0,   1,   2,   3,   4,   6
};
static	const	short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  10,  11,   7,   5,   0,   6,   0,   8
};
static	const	short	yytok2[] =
{
   2,   3,   4,   9
};
static	const	long	yytok3[] =
{
   0
};
#define YYFLAG 		-1000
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define	yyclearin	yychar = -1
#define	yyerrok		yyerrflag = 0

#ifdef	yydebug
#include	"y.debug"
#else
#define	yydebug		0
static	const	char*	yytoknames[1];		/* for debugging */
static	const	char*	yystates[1];		/* for debugging */
#endif

/*	parser for yacc output	*/
#ifdef YYARG
#define	yynerrs		yyarg->yynerrs
#define	yyerrflag	yyarg->yyerrflag
#define yyval		yyarg->yyval
#define yylval		yyarg->yylval
#else
int	yynerrs = 0;		/* number of errors */
int	yyerrflag = 0;		/* error recovery flag */
#endif

extern	int	fprint(int, char*, ...);
extern	int	sprint(char*, char*, ...);

static const char*
yytokname(int yyc)
{
	static char x[10];

	if(yyc > 0 && yyc <= sizeof(yytoknames)/sizeof(yytoknames[0]))
	if(yytoknames[yyc-1])
		return yytoknames[yyc-1];
	sprint(x, "<%d>", yyc);
	return x;
}

static const char*
yystatname(int yys)
{
	static char x[10];

	if(yys >= 0 && yys < sizeof(yystates)/sizeof(yystates[0]))
	if(yystates[yys])
		return yystates[yys];
	sprint(x, "<%d>\n", yys);
	return x;
}

static long
#ifdef YYARG
yylex1(struct Yyarg *yyarg)
#else
yylex1(void)
#endif
{
	long yychar;
	const long *t3p;
	int c;

#ifdef YYARG	
	yychar = yylex(yyarg);
#else
	yychar = yylex();
#endif
	if(yychar <= 0) {
		c = yytok1[0];
		goto out;
	}
	if(yychar < sizeof(yytok1)/sizeof(yytok1[0])) {
		c = yytok1[yychar];
		goto out;
	}
	if(yychar >= YYPRIVATE)
		if(yychar < YYPRIVATE+sizeof(yytok2)/sizeof(yytok2[0])) {
			c = yytok2[yychar-YYPRIVATE];
			goto out;
		}
	for(t3p=yytok3;; t3p+=2) {
		c = t3p[0];
		if(c == yychar) {
			c = t3p[1];
			goto out;
		}
		if(c == 0)
			break;
	}
	c = 0;

out:
	if(c == 0)
		c = yytok2[1];	/* unknown char */
	if(yydebug >= 3)
		fprint(2, "lex %.4lux %s\n", yychar, yytokname(c));
	return c;
}

int
#ifdef YYARG
yyparse(struct Yyarg *yyarg)
#else
yyparse(void)
#endif
{
	struct
	{
		YYSTYPE	yyv;
		int	yys;
	} yys[YYMAXDEPTH], *yyp, *yypt;
	const short *yyxi;
	int yyj, yym, yystate, yyn, yyg;
	long yychar;
#ifndef YYARG
	YYSTYPE save1, save2;
	int save3, save4;

	save1 = yylval;
	save2 = yyval;
	save3 = yynerrs;
	save4 = yyerrflag;
#endif

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyp = &yys[-1];
	goto yystack;

ret0:
	yyn = 0;
	goto ret;

ret1:
	yyn = 1;
	goto ret;

ret:
#ifndef YYARG
	yylval = save1;
	yyval = save2;
	yynerrs = save3;
	yyerrflag = save4;
#endif
	return yyn;

yystack:
	/* put a state and value onto the stack */
	if(yydebug >= 4)
		fprint(2, "char %s in %s", yytokname(yychar), yystatname(yystate));

	yyp++;
	if(yyp >= &yys[YYMAXDEPTH]) {
		yyerror("yacc stack overflow");
		goto ret1;
	}
	yyp->yys = yystate;
	yyp->yyv = yyval;

yynewstate:
	yyn = yypact[yystate];
	if(yyn <= YYFLAG)
		goto yydefault; /* simple state */
	if(yychar < 0)
#ifdef YYARG
		yychar = yylex1(yyarg);
#else
		yychar = yylex1();
#endif
	yyn += yychar;
	if(yyn < 0 || yyn >= YYLAST)
		goto yydefault;
	yyn = yyact[yyn];
	if(yychk[yyn] == yychar) { /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if(yyerrflag > 0)
			yyerrflag--;
		goto yystack;
	}

yydefault:
	/* default state action */
	yyn = yydef[yystate];
	if(yyn == -2) {
		if(yychar < 0)
#ifdef YYARG
		yychar = yylex1(yyarg);
#else
		yychar = yylex1();
#endif

		/* look through exception table */
		for(yyxi=yyexca;; yyxi+=2)
			if(yyxi[0] == -1 && yyxi[1] == yystate)
				break;
		for(yyxi += 2;; yyxi += 2) {
			yyn = yyxi[0];
			if(yyn < 0 || yyn == yychar)
				break;
		}
		yyn = yyxi[1];
		if(yyn < 0)
			goto ret0;
	}
	if(yyn == 0) {
		/* error ... attempt to resume parsing */
		switch(yyerrflag) {
		case 0:   /* brand new error */
			yyerror("syntax error");
			if(yydebug >= 1) {
				fprint(2, "%s", yystatname(yystate));
				fprint(2, "saw %s\n", yytokname(yychar));
			}
			goto yyerrlab;
		yyerrlab:
			yynerrs++;

		case 1:
		case 2: /* incompletely recovered error ... try again */
			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */
			while(yyp >= yys) {
				yyn = yypact[yyp->yys] + YYERRCODE;
				if(yyn >= 0 && yyn < YYLAST) {
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					if(yychk[yystate] == YYERRCODE)
						goto yystack;
				}

				/* the current yyp has no shift onn "error", pop stack */
				if(yydebug >= 2)
					fprint(2, "error recovery pops state %d, uncovers %d\n",
						yyp->yys, (yyp-1)->yys );
				yyp--;
			}
			/* there is no state on the stack with an error shift ... abort */
			goto ret1;

		case 3:  /* no shift yet; clobber input char */
			if(yydebug >= 2)
				fprint(2, "error recovery discards %s\n", yytokname(yychar));
			if(yychar == YYEOFCODE)
				goto ret1;
			yychar = -1;
			goto yynewstate;   /* try again in the same state */
		}
	}

	/* reduction by production yyn */
	if(yydebug >= 2)
		fprint(2, "reduce %d in:\n\t%s", yyn, yystatname(yystate));

	yypt = yyp;
	yyp -= yyr2[yyn];
	yyval = (yyp+1)->yyv;
	yym = yyn;

	/* consult goto table to find next state */
	yyn = yyr1[yyn];
	yyg = yypgo[yyn];
	yyj = yyg + yyp->yys + 1;

	if(yyj >= YYLAST || yychk[yystate=yyact[yyj]] != -yyn)
		yystate = yyact[yyg];
	switch(yym) {
		
case 1:
#line	27	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-2].yyv + yypt[-0].yyv; } break;
case 2:
#line	28	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-2].yyv - yypt[-0].yyv; } break;
case 3:
#line	29	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-2].yyv * yypt[-0].yyv; } break;
case 4:
#line	30	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-2].yyv / yypt[-0].yyv; } break;
case 5:
#line	31	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = -yypt[-0].yyv; } break;
case 6:
#line	32	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-1].yyv; } break;
case 7:
#line	33	"/home/user/Strivers-A2Z-DSA/Compiler Design Lab/Digital Assigment - 1/YACC Programs/Program 1/prog1.y"
{ yyval = yypt[-0].yyv; } break;
	}
	goto yystack;  /* stack new state and value */
}
