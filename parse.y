%{ 


#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"

/* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;

%}


/* YACC: DECLARATIONS */



/* Order of tokens corresponds to tokendefs.c; do not change */

%token IDENTIFIER STRING NUMBER   /* token types */

%token PLUS MINUS TIMES DIVIDE    /* Operators */
%token ASSIGN EQ NE LT LE GE GT POINT DOT AND OR NOT DIV MOD IN

%token COMMA                      /* Delimiters */
%token SEMICOLON COLON LPAREN RPAREN LBRACKET RBRACKET DOTDOT

%token ARRAY BEGINBEGIN           /* Lex uses BEGIN */
%token CASE CONST DO DOWNTO ELSE END FILEFILE FOR FUNCTION GOTO IF LABEL NIL
%token OF PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL
%token VAR WHILE WITH




/* YACC: RULES  */


/*
 The following YACC code will state the legal order in which tokens can be read
 Uppercase words represent literal tokens, lowercase shows calls to more rules

 The colon shows the end of the rule label and the start of a legal pattern of tokens & rules
 The vertical bar declares other possible patterns the rule is allowed to have
 The semicolon marks the end of the rule and it's possibilities

 The braces state which functions to call in the C code should the given pattern be true
 The dollar sign shows which tokens in the selected pattern should be passed to the C function
 $$ declares which token is returned to the rule that called it
*/




%%

  program    :  PROGRAM IDENTIFIER LPAREN idens RPAREN SEMICOLON lblock statement DOT { makeprogram($2, $4, $8); }  
             ;
  idens      :  IDENTIFIER COMMA idens  { $$ = cons($1, $3); }
             |  IDENTIFIER              { $$ = $1; }
             ;
  lblock     :  LABEL lbl SEMICOLON cblock  { $$ = $4; }
             |  cblock                      { $$ = $1; }
             ;
  cblock     :  CONST con tblock  { $$ = $3;}
             |  tblock            { $$ = $1;}
             ;
  tblock     :  TYPE tloop vblock  { $$ = $3;}
             |  vblock             { $$ = $1;}
             ;
  tloop      :  typ tloop
             |  typ
             ;
  vblock     :  VAR vloop
             |  /* empty */
             ;
  vloop      :  vars vloop
             |  vars
             ;
  lbl        :  NUMBER COMMA lbl { instlabel($1); }
             |  NUMBER           { instlabel($1); }
             ;
  con        :  IDENTIFIER EQ NUMBER SEMICOLON con  { instconst($1, $3); }
             |  IDENTIFIER EQ NUMBER SEMICOLON      { instconst($1, $3); }
             ;
  typ        :  IDENTIFIER EQ type SEMICOLON        { insttype($1, $3); }
             ;
  type       :  RECORD fieldlist END                     { $$ = instrec($1,$2); }  
             |  POINT IDENTIFIER                         { $$ = instpoint($1,$2); }
             |  ARRAY LBRACKET simplelp RBRACKET OF type { $$ = instarray($3, $6); }
             |  simpletype                               { $$ = $1; }
             ;
  simpletype :  IDENTIFIER                               { $$ = $1; }
             |  LPAREN idens RPAREN                      { $$ = instenum($2); }
             |  NUMBER DOTDOT NUMBER                     { $$ = instdotdot($1,$2,$3); }
             ;
  simplelp   :  simpletype COMMA simplelp                { $$ = cons($1, $3); }
             |  simpletype                               { $$ = $1; }
             ;
  fieldlist  :  idens COLON type SEMICOLON fieldlist  { $$ = cons(instfields($1,$3), $5); }
             |  idens COLON type                      { $$ = instfields($1,$3); }
             ;
  vars       :  idens COLON type SEMICOLON  { instvars($1, $3); }
             ;
  statement  :  BEGINBEGIN statement endpart            { $$ = makeprogn($1,cons($2, $3)); }
             |  NUMBER COLON statement                  { $$ = dolabel($1,$2,$3); }
             |  IF compare THEN statement endif         { $$ = makeif($1, $2, $4, $5); }
             |  FOR assignment DOWNTO expr DO statement { $$ = makefor(-1,$1,$2,$3,$4,$5,$6); }
             |  FOR assignment TO expr DO statement     { $$ = makefor( 1,$1,$2,$3,$4,$5,$6); }
             |  WHILE compare DO statement              { $$ = makewhile($1,$2,$3,$4); }
             |  REPEAT statelp UNTIL compare            { $$ = makerepeat($1,$2,$3,$4); }
             |  WITH varlp DO statement
             |  GOTO NUMBER                             { $$ = dogoto($1,$2); }
             |  procedid
             |  assignment
             |  /* empty */
             ;
  procedid   :  IDENTIFIER LPAREN procedlp RPAREN { $$ = makefuncall(talloc(), $1, $3); }
             |  IDENTIFIER
             ; 
  procedlp   :  expr                        { $$ = $1; }
             |  STRING                      { $$ = $1; }
             |  procedlp COMMA procedlp     { $$ = cons($1, $3); }
             ;
  statelp    :  statelp SEMICOLON statement { $$ = cons($1, $3); }
             |  statement                   { $$ = $1; }
             ;
  compare    :  IDENTIFIER cmpr NUMBER      { $$ = binop($2, $1, $3); }
             |  IDENTIFIER cmpr IDENTIFIER  { $$ = binop($2, $1, $3); }
             |  IDENTIFIER cmpr NIL         { $$ = binop($2, $1, $3); }
             ;
  cmpr       :  EQ                          { $$ = $1; }
             |  NE                          { $$ = $1; }
             |  LT                          { $$ = $1; }
             |  LE                          { $$ = $1; }
             |  GE                          { $$ = $1; }
             |  GT                          { $$ = $1; }
             ;
  varlp      :  varlp COMMA IDENTIFIER
             |  IDENTIFIER
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }
             ;
  assignment :  variable ASSIGN expr           { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr PLUS term                 { $$ = binop($2, $1, $3); }
             |  expr MINUS term                { $$ = binop($2, $1, $3); }
             |  term                           { $$ = $1; }
             |  NIL                            { $$ = $1; }
             ;
  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  factor                         { $$ = $1; }
             |  MINUS factor                   { $$ = unaryop($1, $2); }
             ;
  factor     :  variable                       { $$ = $1; }
             |  variable LPAREN expr RPAREN    { $$ = $3; }
             |  NUMBER                         { $$ = $1; }
             ;
  variable   : IDENTIFIER LPAREN procedlp RPAREN { $$ = makefuncall(talloc(), $1, $3); }
             | IDENTIFIER                        { $$ = $1; }
             | variable POINT                    { $$ = dopoint($1,$2); }
             | variable LBRACKET exprlp RBRACKET { $$ = arrayref($1,$2,$3,$4); }
             | variable DOT IDENTIFIER           { $$ = reducedot($1,$2,$3); }
             ;
  exprlp     : expr COMMA exprlp               { $$ = cons($1,$3); }
             | expr                            { $$ = $1; }
             ;
             

%%

/* YACC: C CODE */

/* C functions used to parse the tokens for assembly generation */

/*
 The parser works like a binary tree, where each token is a node and each node
 can have a lefthand node (called an operands in the token's case) and a righthand
 node (called a link).  In the parser generator, as well as the assembly
 generator, the node must always follow and write out what's on the lefthand side
 before coming back up and going through the righthand side.

 When the code is parsed, the LHS branch is displayed on the same line as its parent token
 while RHS is placed on a new line, indented to be right below its parent 

*/

#define DEBUG          0             /* set bits here for debugging, 0 = off  */
#define DB_CONS        0             /* bit to trace cons */
#define DB_BINOP       0             /* bit to trace binop */
#define DB_MAKEPROGRAM 0             /* bit to trace makeprogram */
#define DB_MAKEIF      0             /* bit to trace makeif */
#define DB_MAKELABEL   0             /* bit to trace makelabel */
#define DB_MAKEFOR     0             /* bit to trace makefor */
#define DB_MAKEFUNCALL 0             /* bit to trace makefuncall */
#define DB_MAKEPROGN   0             /* bit to trace makeprogn */
#define DB_MAKEFLOAT   0             /* bit to trace makefloat */
#define DB_MAKEFIX     0             /* bit to trace makefix */
#define DB_COPYTOK     0             /* bit to trace copytok */
#define DB_MAKEGOTO    0             /* bit to trace makegoto */
#define DB_MAKEREPEAT 0             /* bit to trace makerepeat */
#define DB_INSTCONST  0             /* bit to trace instconst */
#define DB_INSTVARS   0             /* bit to trace instvars */
#define DB_PARSERES   0             /* bit to trace parseresult */
#define DB_UNARYOP    0             /* bit to trace unaryop */
#define DB_DOLABEL    0             /* bit to trace dolabel */
#define DB_DOGOTO     0             /* bit to trace dogoto */
#define DB_MAKEWHILE  0             /* bit to trace makewhile */
#define DB_MAKESUBRNG 0             /* bit to trace makesubrange */
#define DB_INSTENUM   0             /* bit to trace instenum */
#define DB_INSTTYPE   0             /* bit to trace insttype */
#define DB_INSTPOINT  0             /* bit to trace instpoint */
#define DB_INSTREC    0             /* bit to trace instrec */
#define DB_INSTFIELD  0             /* bit to trace instfield */
#define DB_MAKEAREF   1             /* bit to trace makearef */
#define DB_RDDOT      0             /* bit to trace reducedot */
#define DB_ARRAYREF   0             /* bit to trace arrayref */
#define DB_INSTARRY   0             /* bit to trace instarray */
#define DB_DOPOINT    0

#define WORDSIZE   4             /* alignment size in address units (bytes)  */
#define DOUBLEWORD 8
#define ALIGNSIZE 16             /* record/array alignment size    */

 int labelnumber = 0;  /* sequential counter for internal label numbers */
 int labellist[20];


/* PROGRAM */
/* Declares the start of the program and its name   */
TOKEN makeprogram (TOKEN name, TOKEN args, TOKEN statements)
  {  TOKEN prog = talloc();
     prog->tokentype = OPERATOR;
     prog->whichval = PROGRAMOP;
     prog->operands = name;

     parseresult = prog;

     cons(name, cons(makeprogn(talloc(), args), statements));
     
     if (DEBUG & DB_MAKEPROGRAM)
       { printf("makeprogram\n");
         dbugprinttok(name); 
         dbugprinttok(args);
         dbugprinttok(statements);
       };
     return prog;
  }

/* CONS */
/* Bundles a token to the RHS branch of another token   */
TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item); 
         dbugprinttok(list);
       };
    return item;
  }

/* BINARY OPERATION */
/* An operation to be written out before moving on */
/* One operand will be stored as the LHS of the operator while
   the other operand is stored as the RHS of the first operand
*/
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    if(rhs->tokentype == RESERVED & rhs->whichval == 15) // if this is a nil
    {  rhs = talloc();
       rhs->tokentype = NUMBERTOK;
       rhs->datatype = INTEGER;
       rhs->intval = 0;

       SYMBOL symtyp = symalloc();
       rhs->symtype = symtyp;
       symtyp->kind = POINTERSYM;
       SYMBOL syment = symalloc();
       rhs->symentry = syment;
       syment->kind = TYPESYM;
       syment->datatype = symtyp;
    }

    /* link operands to operator       */
    SYMBOL lsym = searchst(lhs->stringval);
    TOKEN ltok = copytok(lhs);
    if(lsym != NULL)
    { ltok->symentry = lsym;
      ltok->datatype = lsym->basicdt;
      if(lsym->kind == CONSTSYM)
      { ltok->tokentype = NUMBERTOK;
        ltok->datatype = lsym->basicdt;
        switch(ltok->datatype)
        {  case INTEGER: ltok->intval = lsym->constval.intnum; break;
           case REAL: ltok->realval = lsym->constval.realnum; break;
        }
      }
    }  
    
    /* link second operand to first    */
    SYMBOL rsym = searchst(rhs->stringval);
    TOKEN rtok = copytok(rhs);
    if(rsym != NULL)
    { rtok->symentry = rsym;
      rtok->datatype = rsym->basicdt;
      if(rsym->kind == CONSTSYM)
      { rtok->tokentype = NUMBERTOK;
        rtok->datatype = rsym->basicdt;
        switch(rtok->datatype)
        {  case INTEGER: rtok->intval = rsym->constval.intnum; break;
           case REAL: rtok->realval = rsym->constval.realnum; break;
        }
      }
    }

    if(op->whichval != ASSIGNOP)
    {
      /*the following converts one operand to match the datatype of the other if one is a float*/

      /*both tokens are NUMBERTOK*/
      if(lsym == NULL & rsym == NULL)
      {  if((ltok->datatype == REAL || rtok->datatype == REAL) && ltok->datatype != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else if(rtok->datatype == INTEGER) rtok = makefloat(rtok);
        }
      }
      /*both tokens are IDENTIFIER symbols*/
      if(lsym != NULL & rsym != NULL)
      { if((lsym->basicdt == REAL || rsym->basicdt == REAL) && lsym->basicdt != rsym->basicdt)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else if(rsym->basicdt == INTEGER) rtok = makefloat(rtok);
        }
      }
      /*one token is a symbol, the other a number*/
      if(lsym != NULL & rsym == NULL)
      { if((lsym->basicdt == REAL || rtok->datatype == REAL) && lsym->basicdt != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else if(rtok->datatype == INTEGER) rtok = makefloat(rtok);
        }
      }
      if(lsym == NULL & rsym != NULL)
      { if((ltok->datatype == REAL || rsym->basicdt == REAL) && ltok->datatype != rsym->basicdt)
        { if(ltok->datatype == INTEGER) ltok = makefloat(ltok);
          else if(rsym->basicdt == INTEGER) rtok = makefloat(rtok);
        }
      }
      ltok->link = rtok;
    }

    //if op is an ASSIGNOP
    //lhs is a symbol
    else if(lsym != NULL)
    {
      //assign FIXOP
      //rhs is a symbol
      if(rsym != NULL)
      { if(rsym->basicdt == REAL && lsym->basicdt == INTEGER) ltok->link = makefix(rtok);
        else ltok->link = rtok;
      }
      //rhs is a NUMBERTOK
      else if(rtok->datatype == REAL && lsym->basicdt == INTEGER)
      { ltok->link = makefix(rtok);
      }
      else ltok->link = rtok;
    }
    //both lhs and rhs are of the same type
    else ltok->link = rtok;

    op->operands = ltok;

    //sets the datatype of the operator the largest datatype of its operands
    if(rtok->datatype == REAL & ltok->datatype == INTEGER & ltok->tokentype == NUMBERTOK) 
    { op->datatype = rtok->datatype;
      float tmp = (float)ltok->intval;
      ltok->datatype = rtok->datatype;
      ltok->realval = tmp;
    }
    else if(ltok->datatype == REAL & rtok->datatype == INTEGER & rtok->tokentype == NUMBERTOK)
    { op->datatype = ltok->datatype;
      float tmp = (float)rtok->intval;
      rtok->datatype = ltok->datatype;
      rtok->realval = tmp;
    }
    else if(ltok->datatype == REAL & rtok->datatype == REAL)
      op->datatype = ltok->datatype;

    if (DEBUG & DB_BINOP)
    { printf("binop\n");
      dbugprinttok(op);
      dbugprinttok(lhs);
      dbugprinttok(rhs);
    };

    return op;
  }

/* UNARY OPERATION */
/* assigns a single item to the LHS of the operator */
TOKEN unaryop(TOKEN op, TOKEN lhs)
  { op->operands = lhs;
    lhs->link = NULL;
    lhs->symentry = searchst(lhs->stringval);
    if (DEBUG & DB_UNARYOP)
    { printf("unaryop\n");
      dbugprinttok(op);
      dbugprinttok(lhs);
    }
    return op;
  }

/* OVERRIDE AS A FLOATING POINT NUMBER FOR ASSIGNMENT OPERATION */
/* creates a float declaration and assigns the given token
   to its LHS, this is to override variables as a floats
*/
TOKEN makefloat(TOKEN tok)
  { TOKEN flt = talloc();
    if(tok->tokentype == IDENTIFIERTOK)
    { flt->tokentype = OPERATOR;
      flt->whichval = FLOATOP;
      flt->datatype = REAL;
      unaryop(flt, tok);
    }

    else if(tok->tokentype == NUMBERTOK)
    { flt->tokentype = NUMBERTOK;
      flt->datatype = REAL;
      flt->realval = (float)tok->intval;
    }

    if(DEBUG & DB_MAKEFLOAT) 
    {  printf("makefloat\n");
       dbugprinttok(tok);
    }
  return flt;
  }

/* MARK A FIX OPERATION FOR MISMATCHING VARIABLE TYPES */
TOKEN makefix(TOKEN tok)
  { TOKEN fix = talloc();
    fix->tokentype = OPERATOR;
    fix->whichval = FIXOP;
    fix->operands = tok;
    if(DEBUG & DB_MAKEFIX) 
    {  printf("makefix\n");
       dbugprinttok(tok);
    }
    return fix;
  }

/* COPY TOKEN */
TOKEN copytok(TOKEN origtok)
  { TOKEN cpy = origtok;
    cpy->tokentype = origtok->tokentype;
    cpy->datatype = origtok->datatype;
    cpy->operands = origtok->operands;
    cpy->link = origtok->link;
    if(DEBUG & DB_COPYTOK)
    {  printf("copytok\n");
       dbugprinttok(origtok);
    }
    return cpy;
  }

/* IF STATEMENT */
TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;
     tok->whichval = IFOP;

     //ELSE PART NOT READY, NEED TO ADD LABELS
     if (elsepart != NULL) elsepart->link = NULL;

     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

/* PROGN */
/* Creates a LHS branch that must be written out before moving on */
TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

/* DECLARE LABEL */ 
/* keeps track of the labels the coder declared at the start of the program 
  (user can create up to 20 labels)
*/
void  instlabel (TOKEN num)
  {  labellist[labelnumber++] = num->intval;
  }

/* USE DECLARED LABEL */
/* The coder uses a declared label in the pascal file */
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement)
  {  int i = 0;
     while(labellist[i] != labeltok->intval) i++;

     tok = talloc();
     tok->tokentype = OPERATOR;
     tok->whichval = LABELOP;
     labeltok->intval = i;
     
     unaryop(tok, labeltok);
     cons(tok, statement);

     if (DEBUG & DB_DOLABEL)
       { printf("dolabel\n");
          dbugprinttok(labeltok);
          dbugprinttok(tok);
          dbugprinttok(statement);
        };
    return makeprogn(talloc(), tok);
  }

/* MAKE LABEL */
/* Called by a makeloop function, creates and identifies a label for any loops created in the program */
TOKEN makelabel()
  { TOKEN lbl = talloc();
    TOKEN n = talloc();
    lbl->tokentype = OPERATOR;
    lbl->whichval = LABELOP;
    n->tokentype = NUMBERTOK;
    n->datatype = INTEGER;
    n->intval = labelnumber++;
    lbl->operands = n;
    if (DEBUG & DB_MAKELABEL)
       { printf("makelabel\n");
         dbugprinttok(lbl);
         dbugprinttok(n);
       };
    return lbl;
  }

/* GOTO DECLARED LABEL */
TOKEN dogoto(TOKEN tok, TOKEN labeltok)
  {  int i = 0;
     while(labellist[i] != labeltok->intval) i++;
     tok->tokentype = OPERATOR;
     tok->whichval = GOTOOP;
     labeltok->intval = i;
     tok->operands = labeltok;
     if (DEBUG & DB_DOGOTO)
       { printf("dogoto\n");
         dbugprinttok(tok);
         dbugprinttok(labeltok);
       };
     return tok;
  }

/* MAKE GOTO */
/* Called by a makeloop function, goes to the label created by a loop */
TOKEN makegoto(int label)
  {  TOKEN go2 = talloc();
     TOKEN num = talloc();
     go2->tokentype = OPERATOR;
     go2->whichval = GOTOOP;
     num->tokentype = NUMBERTOK;
     num->datatype = INTEGER;
     num->intval = label;
     go2->operands = num;
     if (DEBUG & DB_MAKEGOTO)
       { printf("makegoto\n");
         dbugprinttok(go2);
         dbugprinttok(num);
       };
     return go2;
  }

/* WHILE LOOP */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement)
  { tok = makeprogn(talloc(), cons(makelabel(),makeif(tokb,expr,statement, NULL)));

    statement = statement->operands;
    while(statement->link != NULL) statement = statement->link;
    cons(statement, makegoto(labelnumber - 1));

    if (DEBUG & DB_MAKEWHILE)
      { printf("makewhile\n");
        dbugprinttok(tok);
        dbugprinttok(expr);
        dbugprinttok(tokb);
        dbugprinttok(statement);
       };
    return tok;
  }

/* REPEAT (aka DO-WHILE LOOP)*/
/* creates a label at the start of the next block of code with a
   an if statement and goto statement at the end
*/
TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr)
  {  TOKEN go2 = makegoto(labelnumber);
     TOKEN iftok =makeif(tokb, expr, cons(makeprogn(talloc(), NULL), talloc()), go2);

     makeprogn(tok, cons(makelabel(), statements));

     TOKEN linked = statements;
     while(linked->link != NULL) linked = linked->link;
     cons(linked, iftok);

     if (DEBUG & DB_MAKEREPEAT)
       { printf("makerepeat\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
         dbugprinttok(tokb);
         dbugprinttok(expr);
       };
     
     return tok;
  }

/* FOR LOOP */
/* Creates a label and if statement at the start of the next block of
   code with an increment and goto statement at the end
*/
TOKEN makefor(int sign, TOKEN tok, TOKEN asg, TOKEN tokb, TOKEN endexpr,
              TOKEN tokc, TOKEN statement)
  { 
    //op will be the <= (or >=) value when the for-loop checks its argument after every loop
		TOKEN op = talloc();
    op->tokentype = OPERATOR;

    //increment will be the ":=" for the loop update
    TOKEN increment = talloc();
    increment->tokentype = OPERATOR;
    increment->whichval = ASSIGNOP;

    //one will just be a token of value one, for the increment
    TOKEN one = talloc();
    one->tokentype = NUMBERTOK;
    one->datatype = INTEGER;
    one->intval = 1;
    
    //increop will be nested in increment, will either be PLUSOP or MINUSOP
    TOKEN increop = talloc();
    increop->tokentype = OPERATOR;

		if(sign == -1)
    {  op->whichval = GEOP;
       increop->whichval = MINUSOP;
    }
    else
    {  op->whichval = LEOP;
       increop->whichval = PLUSOP;
    }

    TOKEN tmp = talloc();

    //to copy the initialized value from the condition statement
    //For use in the if statement
    TOKEN cpy1 = talloc();
    cpy1->tokentype = asg->operands->tokentype;
    cpy1->whichval = asg->operands->whichval;

    //For use in the assign value part of the incrementation
    TOKEN cpy2 = talloc();
    cpy2->tokentype = asg->operands->tokentype;
    cpy2->whichval = asg->operands->whichval;

    //For use in the "add one" part of the incrementation
    TOKEN cpy3 = talloc();
    cpy3->tokentype = asg->operands->tokentype;
    cpy3->whichval = asg->operands->whichval;

    //the goto [label] branch
    TOKEN go2 = makegoto(labelnumber);

    binop(op,cpy1,endexpr);
    binop(increment, cpy2, increop);
    binop(increop, cpy3, one);
    cons(increment, go2);

    makeprogn(tok, asg);
    makeprogn(tmp,cons(statement, increment));
    cons(asg, cons(makelabel(), makeif(tokb, op, tmp, NULL)));
    if (DEBUG & DB_MAKEFOR)
    { printf("makefor\n");
      dbugprinttok(tok);
      dbugprinttok(asg);
      dbugprinttok(tokb);
      dbugprinttok(endexpr);
      dbugprinttok(tokc);
      dbugprinttok(statement);
    };
    return tok;
  }

/* FUNCTION CALL */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args)
  { if(strcmp(fn->stringval,"new") == 0)
    { 
        tok->tokentype = OPERATOR;
        tok->whichval = ASSIGNOP;
        tok->operands = args;

        TOKEN tok2 = talloc();
        tok2->tokentype = OPERATOR;
        tok2->whichval = FUNCALLOP;

        TOKEN size = talloc();
        size->tokentype = NUMBERTOK;
        size->datatype = INTEGER;
        SYMBOL sym = searchst(args->stringval);
        args->symentry = sym;

        if(sym->datatype->kind == POINTERSYM) sym = sym->datatype->datatype;
        size->intval = sym->size;
 
        args->link = binop(tok2, fn, size);
 
    }
      
    else {

      tok->tokentype = OPERATOR;
      tok->whichval = FUNCALLOP;
    
      //Write Line Function Calls
      if(strcmp(fn->stringval, "writeln") == 0)
      {  SYMBOL sym = searchins(args->stringval);
         if(sym->datatype != NULL)
         {  
            //Write Line Integer Function Call
            if(sym->datatype->kind == BASICTYPE & sym->datatype->kind == INTEGER);
            {
              TOKEN wrti = talloc();
              wrti->tokentype = IDENTIFIERTOK;
              wrti->stringval[0] = 'w';
              wrti->stringval[1] = 'r';
              wrti->stringval[2] = 'i';
              wrti->stringval[3] = 't';
              wrti->stringval[4] = 'e';
              wrti->stringval[5] = 'l';
              wrti->stringval[6] = 'n';
              wrti->stringval[7] = 'i';
              tok->datatype = INTEGER;
              tok->operands = wrti;
              cons(wrti, args);
            }
         }

         //Write Line Floating Point
         else if(args->datatype == REAL)
         {
              TOKEN wrtf = talloc();
              wrtf->tokentype = IDENTIFIERTOK;
              wrtf->stringval[0] = 'w';
              wrtf->stringval[1] = 'r';
              wrtf->stringval[2] = 'i';
              wrtf->stringval[3] = 't';
              wrtf->stringval[4] = 'e';
              wrtf->stringval[5] = 'l';
              wrtf->stringval[6] = 'n';
              wrtf->stringval[7] = 'f';
              tok->datatype = REAL;
              tok->operands = wrtf;
              cons(wrtf, args);
         }

         //Write Line String
         else
         { SYMBOL sym = searchins(fn->stringval);
           tok->datatype = sym->datatype->basicdt;
           tok->operands = fn;
           cons(fn, args);
         }
      }

      //Write Function Calls
      else if(strcmp(fn->stringval, "write") == 0)
      {  SYMBOL sym = searchins(args->stringval);

         //Write Integer
         if(sym->datatype != NULL)
         {  if(sym->datatype->kind == BASICTYPE & sym->datatype->kind == INTEGER);
            {
              TOKEN wrti = talloc();
              wrti->tokentype = IDENTIFIERTOK;
              wrti->stringval[0] = 'w';
              wrti->stringval[1] = 'r';
              wrti->stringval[2] = 'i';
              wrti->stringval[3] = 't';
              wrti->stringval[4] = 'e';
              wrti->stringval[5] = 'i';
              tok->datatype = INTEGER;
              tok->operands = wrti;
              cons(wrti, args);
            }
         }

         //Write Floating Point
         else if(args->datatype == REAL)
         {
              TOKEN wrtf = talloc();
              wrtf->tokentype = IDENTIFIERTOK;
              wrtf->stringval[0] = 'w';
              wrtf->stringval[1] = 'r';
              wrtf->stringval[2] = 'i';
              wrtf->stringval[3] = 't';
              wrtf->stringval[4] = 'e';
              wrtf->stringval[5] = 'f';
              tok->datatype = REAL;
              tok->operands = wrtf;
              cons(wrtf, args);
         }

         //Write String
         else
         { SYMBOL sym = searchins(fn->stringval);
           tok->datatype = sym->datatype->basicdt;
           tok->operands = fn;
           cons(fn, args);
         }
      }

      //Special Function Call
      else
      { SYMBOL sym = searchins(fn->stringval);
        tok->datatype = sym->datatype->basicdt;
        tok->operands = fn;
        cons(fn, args);
      }
    }
    args->symentry = searchst(args->stringval);
    if (DEBUG & DB_MAKEFUNCALL)
    { printf("makefuncall\n");
      dbugprinttok(tok);
      dbugprinttok(fn);
      dbugprinttok(args);
    }
    return tok;
  }

/* Make Subrange */
/* Used when declaring the range of an array */
TOKEN makesubrange(TOKEN tok, int low, int high)
  {  SYMBOL sym;
     sym = symalloc();
     sym->kind = SUBRANGE;
     sym->basicdt = INTEGER;
     sym->lowbound = low;
     sym->highbound = high;
     sym->size = basicsizes[INTEGER];
     tok = talloc();
     tok->symtype = sym;

     if (DEBUG & DB_MAKESUBRNG)
     { printf("makesubrange\n");
       dbugprinttok(tok);
       printf(" low: %i\n high: %i\n", low, high);
     }
    return tok;
  }

/* DECLARE ENUM */
TOKEN instenum(TOKEN idlist)
  {  TOKEN tok, type;
     SYMBOL sym;
     
     type = talloc();
     type->tokentype = NUMBERTOK;
     type->datatype = INTEGER;
     type->intval = 0;

     instconst(idlist, type);
     (type->intval)++;
     while(idlist->link != NULL)
     {  idlist = idlist->link;
        instconst(idlist, type);
        (type->intval)++;
     }

     tok = talloc();
     sym = symalloc();
     tok->symtype = makesubrange(talloc(), 0,(type->intval) - 1)->symtype;

     if (DEBUG & DB_INSTENUM)
     { printf("instenum\n");
       dbugprinttok(idlist);
     }
     return tok;
  }

/* DECLARE TYPE (NAME AND CONTENT(S) */
void insttype(TOKEN typename, TOKEN typetok)
  {  SYMBOL sym, type;

     sym = searchins(typename->stringval);
     sym->kind = TYPESYM;
     type = typetok->symtype;
     sym->datatype = type;
     sym->size = type->size;
     if (DEBUG & DB_INSTTYPE)
     { printf("insttype\n");
       dbugprinttok(typename);
       dbugprinttok(typetok);
     }
  }

/* DECLARE POINTER */
TOKEN instpoint(TOKEN tok, TOKEN typename)
  {  TOKEN symtok;
     SYMBOL point, sym;

     sym = searchins(typename->stringval);
     point = symalloc();
     point->kind = POINTERSYM;
     point->size = 8;
     point->datatype = sym;

     symtok = talloc();
     symtok->symtype = point;

     if (DEBUG & DB_INSTPOINT)
     { printf("instpoint\n");
       dbugprinttok(tok);
       dbugprinttok(typename);
     }
     return symtok;
  }

/* DECLARE RECORD (aka STRUCT) */
TOKEN instrec(TOKEN rectok, TOKEN argstok)
  {
     TOKEN symtok;
     SYMBOL sym, field;
     int off;

     symtok = talloc();
     sym = symalloc();
     symtok->symtype = sym;
     sym->kind = RECORDSYM;
     field = argstok->symtype;
     sym->datatype = field;
     off = 0;
     off = field->size;
     while(field->link != NULL)
     {
       field = field->link;
       if(field->datatype->size == 4) field->offset = wordaddress(off, 4);
       else  field->offset = wordaddress(off, 8);
       off = field->offset + field->size;
     }

     while(argstok->link != NULL)
     {
       argstok = argstok->link;
       field->link = argstok->symtype;
       field = field->link;
       if(field->datatype->size == 4) field->offset = wordaddress(off, 4);
       else  field->offset = wordaddress(off, 8);
       off = field->offset + field->size;
       while(field->link != NULL)
       {
         field = field->link;
         if(field->datatype->size == 4) field->offset = wordaddress(off, 4);
         else  field->offset = wordaddress(off, 8);
         off = field->offset + field->size;
       }
     }
     sym->size = off;
     if (DEBUG & DB_INSTREC)
     { printf("instrec\n");
       dbugprinttok(rectok);
       dbugprinttok(argstok);
     }
     return symtok;
  }

/* DECLARE FIELDS (TYPES TO BE CONTAINTED IN A RECORD) */
TOKEN instfields(TOKEN idlist, TOKEN typetok)
  {  TOKEN symtok;
     SYMBOL sym, last, type;
     
     symtok = talloc();
     sym = makesym(idlist->stringval);

     symtok->symtype = sym;
     type = searchst(typetok->stringval);

     sym->datatype = type;
     sym->size = sym->datatype->size;
     sym->offset = 0;
     last = sym;
     while(idlist->link != NULL)
     { idlist = idlist->link;
       sym = makesym(idlist->stringval);
       sym->datatype = type;
       sym->size = sym->datatype->size;
       sym->offset = last->offset + sym->size;
       last->link = sym;
       last = sym;
     }


     if (DEBUG & DB_INSTFIELD)
     { printf("instfields\n");
       dbugprinttok(idlist);
       dbugprinttok(typetok);
     }
     return symtok;
  }

/* DECLARE CONSTANT VALUE */
void instconst(TOKEN idtok, TOKEN consttok)
  {  SYMBOL sym;

     sym = insertsym(idtok->stringval);
     sym->kind = CONSTSYM;
     sym->basicdt = consttok->datatype;
     switch(sym->basicdt)
     { case INTEGER: sym->constval.intnum = consttok->intval;
                     sym->datatype = searchst("integer"); break;
       case REAL: sym->constval.realnum = consttok->realval;
                     sym->datatype = searchst("real");break;
       case BOOLETYPE: sym->constval.intnum = consttok->intval; break;
     }

     if (DEBUG & DB_INSTCONST)
     { printf("instconst\n");
       dbugprinttok(idtok);
       dbugprinttok(consttok);
     }

  }

/* DECLARE VARIABLE TYPE*/
void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typ;
     typ = symalloc();

     int align;

     if(typetok->symtype != NULL) typ = typetok->symtype; 
     else typ = searchst(typetok->stringval);

     align = (typ->size > WORDSIZE) ? ((typ->size > DOUBLEWORD) ? ALIGNSIZE : DOUBLEWORD) : typ->size;

     while (idlist != NULL)
     {  sym = insertsym(idlist->stringval);
        sym->kind = VARSYM;
        sym->basicdt = typ->basicdt;
        sym->offset = wordaddress(blockoffs[blocknumber],align);
        sym->size = typ->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        idlist->symentry = sym;

        if(typ->kind == TYPESYM) sym->datatype = typ->datatype;
        else sym->datatype = typ;
        idlist = idlist->link;
     }

     if (DEBUG & DB_INSTVARS)
     { printf("instvars\n");
       dbugprinttok(idlist);
       dbugprinttok(typetok);
     }
  }

/* DECLARE ARRAY RANGE */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok)
  {
    dottok = makesubrange(dottok, lowtok->intval, hightok->intval);
     if (DEBUG)
     { printf("instdotdot\n");
       dbugprinttok(lowtok);
       dbugprinttok(dottok);
       dbugprinttok(hightok);
     }
    return dottok;
  }

/* MAKE ANALOG REFERENCE */
/* Grabs a value of a record using an offset */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok)
  {  TOKEN ref;
     ref = talloc();
     ref->tokentype = OPERATOR;
     ref->whichval = AREFOP;

     tok = binop(ref, var, off);

     int i = off->intval;
     SYMBOL temp = var->symtype->datatype->datatype;

     if(temp->kind == RECORDSYM) temp = temp->datatype;
     
     while(temp->offset < i & temp->link != NULL) temp = temp->link;
     
     temp = temp->datatype;
     var->symtype = temp;

     if (DEBUG & DB_MAKEAREF)
     { printf("makearef\n");
       dbugprinttok(var);
       dbugprinttok(off);
       dbugprinttok(tok);
     }
     return tok;
  }

/* REDUCE DOT */
/* Locate a specific field within a record */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field)
  {  TOKEN off;
     SYMBOL sym;

     dot = talloc();
     off = talloc();
     off->tokentype = NUMBERTOK;
     off->datatype = INTEGER;
     off->intval = var->symtype->offset;

     sym = var->symtype->datatype->datatype;

     if(sym->kind == RECORDSYM) sym = sym->datatype;

     //iterate throught the record until the desired variable is found
     while(strcmp(sym->namestring, field->stringval) != 0) sym = sym->link;


     off->intval = off->intval + sym->offset;
     if(var->tokentype == OPERATOR & var->whichval == POINTEROP)
     { dot = makearef(var, off, dot);
       if(dot->operands->tokentype == OPERATOR & dot->tokentype == OPERATOR)
         if(dot->operands->whichval == AREFOP & dot->whichval == AREFOP & dot->operands->operands != NULL)
           if(dot->operands->operands->tokentype == OPERATOR & dot->operands->operands->whichval == POINTEROP)
           dot->operands->operands->link = dot->operands->link;
     }
     else
     { dot = makearef(var, off, dot); 
       if(dot->operands->tokentype == OPERATOR & dot->tokentype == OPERATOR)
         if(dot->operands->whichval == AREFOP & dot->whichval == AREFOP & dot->operands->operands != NULL)
           if(dot->operands->operands->tokentype == OPERATOR & dot->operands->operands->whichval == POINTEROP)
           dot->operands->operands->link = dot->operands->link;
       dot->operands = dot->operands->operands;
     } 

     dot->symtype = sym;

    if(sym->datatype->basicdt == REAL) dot->datatype = sym->datatype->basicdt;

    if (DEBUG & DB_RDDOT)
     { printf("reducedot\n");
       dbugprinttok(var);
       dbugprinttok(dot);
       dbugprinttok(field);
     }
     return dot;
  }

/* ARRAY REFERENCE */
/* Grabs the value of a variable in an array */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb)
 { if (DEBUG & DB_ARRAYREF)
    { printf("arrayref\n");
      dbugprinttok(arr);
      dbugprinttok(tok);
      dbugprinttok(subs);
      dbugprinttok(tokb);
    }
    SYMBOL sym;

    if(arr->symtype != NULL) sym = arr->symtype;
    else sym = searchst(arr->stringval);
    
    while(sym->kind != ARRAYSYM) sym = sym->datatype;


    tokb->tokentype = OPERATOR;
    tokb->whichval = AREFOP;

    SYMBOL sm = searchst(subs->stringval);

    if(sm != NULL & subs->link == NULL & subs->tokentype != NUMBERTOK)
    {  if(sm->kind == CONSTSYM)
      {
        tok->tokentype = NUMBERTOK;
        tok->datatype = INTEGER;
        tok->intval = ((sm->constval.intnum - (sym->lowbound)) * sym->datatype->size);

        binop(tokb,arr,tok);

        tokb->symtype = sym;

        return tokb; 
      }
    }
    if(subs->tokentype == NUMBERTOK & subs->link == NULL)
    {  sym = sym->datatype;
       tok->tokentype = NUMBERTOK;
       tok->datatype = INTEGER;
       tok->intval = ((subs->intval - (sym->lowbound)) * sym->datatype->size) - sym->datatype->size;

       binop(tokb,arr,tok);

    }
    else
    { tok = talloc();
      tok->tokentype = OPERATOR;
      tok->whichval = PLUSOP;

      TOKEN multi = talloc();
      TOKEN low1 = talloc();
      TOKEN low2 = talloc();

      multi->tokentype = OPERATOR;
      multi->whichval = TIMESOP;
      low1->tokentype = NUMBERTOK;
      low1->datatype = INTEGER;
      low1->intval = sym->lowbound * sym->datatype->size * -1;
      low2->tokentype = NUMBERTOK;
      low2->datatype = INTEGER;
      low2->intval = (sym->lowbound * sym->datatype->size);


      SYMBOL type = searchst(subs->stringval);
      if(subs->tokentype == NUMBERTOK & subs->datatype == INTEGER)
      {
        low1->intval = low1->intval + (sym->datatype->size * (subs->intval - sym->lowbound));
        binop(tok,low1,multi);
      }
      else if (type != NULL) if(type->kind == CONSTSYM)
      {
        low1->intval = low1->intval + (sym->datatype->size * type->constval.intnum);
        binop(tok,low1,multi);
      }
      else binop(tok,low1,binop(multi,low2,subs));

      TOKEN tmp = subs;
      while(subs->link != NULL) 
      { sym = sym->datatype;
        tmp = tmp->link;
        subs->link = NULL;
        subs = tmp;
        SYMBOL type = searchst(subs->stringval);
        if(subs->tokentype == NUMBERTOK & subs->datatype == INTEGER)
        {
          low1->intval = low1->intval + (sym->datatype->size * (subs->intval - sym->lowbound));
        }
        else if (type != NULL) if(type->kind == CONSTSYM)
        {
          low1->intval = low1->intval + (sym->datatype->size * type->constval.intnum);
        }
        else
        {
          TOKEN multi2 = talloc();
          multi2->tokentype = OPERATOR;
          multi2->whichval = TIMESOP;
          TOKEN low3 = talloc();
          low3->tokentype = NUMBERTOK;
          low3->datatype = INTEGER;
          low3->intval = (sym->lowbound * sym->datatype->size);
          low1->intval = low1->intval - low3->intval;
          if (multi->operands == NULL) multi2 = multi;
          else cons(multi,multi2);
          binop(multi2,low3,subs);
          multi = multi2;
        }
      }

      binop(tokb,arr,tok);
    }
    

    tokb->symtype = sym;
    return tokb;
 }

/* DO POINTER */
/* Identifies a pointer to be dereferenced*/
TOKEN dopoint(TOKEN var, TOKEN tok)
  { if(var->symtype != NULL) tok->symtype = var->symtype;
    else tok->symtype = searchst(var->stringval);
    
    while(tok->symtype->kind != POINTERSYM) tok->symtype = tok->symtype->datatype;
    tok->symtype = tok->symtype->datatype;

    unaryop(tok,var);

    if (DEBUG & DB_DOPOINT)
     { printf("dopoint\n");
       dbugprinttok(var);
       dbugprinttok(tok);
     }
    return tok;
  }

/* DELCARE ARRAY */
TOKEN instarray(TOKEN bounds, TOKEN typetok)
  { TOKEN symtok;
    SYMBOL sym, next, bnds;

    sym = symalloc();
    sym->kind = ARRAYSYM;
    bnds = symalloc();
    if(bounds->symtype == NULL) bnds = searchst(bounds->stringval);
    else bnds = bounds->symtype;
    if(bnds->datatype != NULL) bnds = bnds->datatype;
 
    next = symalloc();
    if(bounds->link != NULL) next = instarray(bounds->link, typetok)->symtype;
    else next = searchst(typetok->stringval);

    sym->datatype = next;
    sym->size = ((bnds->highbound) - (bnds->lowbound) + 1) * (next->size);
    sym->highbound = bnds->highbound;
    sym->lowbound = bnds->lowbound;

    symtok = talloc();
    symtok->symtype = sym;
    if (DEBUG & DB_INSTARRY)
    { printf("instarray\n");
      dbugprinttok(bounds);
      dbugprinttok(typetok);
    }
    return symtok;
  }


int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
yyerror(s)
  char * s;
  { 
  fputs(s,stderr); putc('\n',stderr);
  }

main()
  { int res;
    initsyms();
    res = yyparse();


    /* These commented lines should be restored to show parser results*/

    //printstlevel(1);
    //printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    //ppexpr(parseresult);           /* Pretty-print the result tree */
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
  }
