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


%%




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




  program    :  PROGRAM IDENTIFIER LPAREN idens RPAREN SEMICOLON lblock statement DOT { makeprogram($2, $4, $8); }  
             ;
	idens      :  IDENTIFIER COMMA idens  { $$ = cons($1, $3); }
	           |  IDENTIFIER              { $$ = $1; }
	           ;
  lblock     :  LABEL ints SEMICOLON cblock  { $$ = $4; }
             |  cblock                       { $$ = $1; }
						 ;
  cblock     :  CONST con tblock { $$ = $3;}
             |  tblock           { $$ = $1;}
             ;
  tblock     :  TYPE typ vblock  { $$ = $3;}
             |  vblock           { $$ = $1;}
             ;
  vblock     :  VAR vars
             |  /* empty */
             ;
  ints       :  NUMBER COMMA ints
             |  NUMBER
             ;
  con        :  IDENTIFIER EQ NUMBER SEMICOLON con  { instconst($1, $3); }
             |  IDENTIFIER EQ NUMBER SEMICOLON      { instconst($1, $3); }
             ;
  typ        :  IDENTIFIER EQ IDENTIFIER SEMICOLON typ
             |  IDENTIFIER EQ IDENTIFIER SEMICOLON
             ;
  vars       :  varsid COLON IDENTIFIER SEMICOLON vars { instvars($1, $3); }
             |  varsid COLON IDENTIFIER SEMICOLON      { instvars($1, $3); }
             ;  
  varsid     :  IDENTIFIER COMMA varsid { $$ = cons($1, $3); }
             |  IDENTIFIER              { $$ = $1; }
             ;
  statement  :  BEGINBEGIN statement endpart   { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  FOR assignment DOWNTO expr DO statement { $$ = makefor(-1,$1,$2,$3,$4,$5,$6); }
             |  FOR assignment TO expr DO statement     { $$ = makefor( 1,$1,$2,$3,$4,$5,$6); }
             |  WHILE expr DO statement
             |  REPEAT statelp UNTIL compare       { $$ = makerepeat($1,$2,$3,$4); }
             |  WITH varlp DO statement
             |  GOTO NUMBER
             |  procedid
             |  assignment
             |  /* empty */
             ;
  procedid   :  IDENTIFIER LPAREN procedlp RPAREN { $$ = makefuncall(talloc(), $1, $3); }
             |  IDENTIFIER
             ;
  procedlp   :  expr                        { $$ = $1; }
             |  IDENTIFIER                  { $$ = $1; }
             |  STRING                      { $$ = $1; }
             |  procedlp COMMA procedlp     { $$ = cons($1, $3); }
             ;
  statelp    :  statelp SEMICOLON statement { $$ = cons($1, $3); }
             |  statement                   { $$ = $1; }
             ;
  compare    :  IDENTIFIER cmpr NUMBER      { $$ = binop($2, $1, $3); }
             |  IDENTIFIER cmpr IDENTIFIER  { $$ = binop($2, $1, $3); }
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
  assignment :  IDENTIFIER ASSIGN expr         { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr PLUS term                 { $$ = binop($2, $1, $3); }
             |  expr MINUS term                { $$ = binop($2, $1, $3); }
             |  term                           { $$ = $1; }
             ;
  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  factor                         { $$ = $1; }
             |  MINUS factor                   { $$ = unaryop($1, $2); }
             ;
  factor     :  LPAREN expr RPAREN             { $$ = $2; }
             |  IDENTIFIER LPAREN expr RPAREN  { $$ = makefuncall(talloc(), $1, $3);  }
             |  IDENTIFIER                     { $$ = $1; }
             |  NUMBER                         { $$ = $1; }
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

#define DEBUG         31             /* set bits here for debugging, 0 = off  */
#define DB_CONS        1             /* bit to trace cons */
#define DB_BINOP       2             /* bit to trace binop */
#define DB_MAKEPROGRAM 3             /* bit to trace makeprogram */
#define DB_MAKEIF      4             /* bit to trace makeif */
#define DB_MAKELABEL   5             /* bit to trace makelabel */
#define DB_MAKEFOR     6             /* bit to trace makefor */
#define DB_MAKEFUNCALL 7             /* bit to trace makefuncall */
#define DB_MAKEPROGN   8             /* bit to trace makeprogn */
#define DB_MAKEFLOAT   9             /* bit to trace makefloat */
#define DB_MAKEFIX    10             /* bit to trace makefix */
#define DB_COPYTOK    11             /* bit to trace copytok */
#define DB_MAKEGOTO   12             /* bit to trace makegoto */
#define DB_MAKEREPEAT 13             /* bit to trace makerepeat */
#define DB_INSTCONST  14             /* bit to trace instconst */
#define DB_INSTVARS   15             /* bit to trace instvars */
#define DB_PARSERES   16             /* bit to trace parseresult */
#define DB_UNARYOP    17             /* bit to trace unaryop */

#define WORDSIZE   4             /* alignment size in address units (bytes)  */
#define ALIGNSIZE 16             /* record/array alignment size    */

 int labelnumber = 0;  /* sequential counter for internal label numbers */


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
    /* link operands to operator       */
    SYMBOL lsym = searchst(lhs->stringval);
    TOKEN ltok = copytok(lhs);
    if(lsym != NULL)
    { if(lsym->kind == CONSTSYM)
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
    { if(rsym->kind == CONSTSYM)
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
      if(lsym == NULL && rsym == NULL)
      {  if((ltok->datatype == REAL || rtok->datatype == REAL) && ltok->datatype != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      /*both tokens are IDENTIFIER symbols*/
      if(lsym != NULL && rsym != NULL)
      { if((lsym->basicdt == REAL || rsym->basicdt == REAL) && lsym->basicdt != rsym->basicdt)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      /*one token is a symbol, the other a number*/
      if(lsym != NULL && rsym == NULL)
      { if((lsym->basicdt == REAL || rtok->datatype == REAL) && lsym->basicdt != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      if(lsym == NULL && rsym != NULL)
      { if((ltok->datatype == REAL || rsym->basicdt == REAL) && ltok->datatype != rsym->basicdt)
        { if(ltok->datatype == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
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
    if(rtok->datatype > ltok->datatype)
      op->datatype = rtok->datatype;
    else op->datatype = ltok->datatype;   


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

/* LABEL */
/* Creates and identify a label for use in assembly */
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

/* GOTO */
/* will tell the assembly code which label to jump to */
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
  { tok->tokentype = OPERATOR;
    tok->whichval = FUNCALLOP;
    SYMBOL sym = searchins(fn->stringval);
    tok->datatype = sym->datatype->basicdt;
    tok->operands = fn;
    cons(fn, args);
    if (DEBUG & DB_MAKEFUNCALL)
    { printf("makefuncall\n");
      dbugprinttok(tok);
      dbugprinttok(fn);
      dbugprinttok(args);
    }
    return tok;
  }

/* INSERT CONSTANT IDENTIFIER */
void instconst(TOKEN idtok, TOKEN consttok)
  {  SYMBOL sym;

     sym = insertsym(idtok->stringval);
     sym->kind = CONSTSYM;
     sym->basicdt = consttok->datatype;
     switch(sym->basicdt)
     { case INTEGER: sym->constval.intnum = consttok->intval; break;
       case REAL: sym->constval.realnum = consttok->realval; break;
       case BOOLETYPE: sym->constval.intnum = consttok->intval; break;
     }

     if (DEBUG & DB_INSTCONST)
     { printf("instconst\n");
       dbugprinttok(idtok);
       dbugprinttok(consttok);
     }

  }

/* CREATE VARIABLE IDENTIFIER*/
void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typ;
     typ = makesym(typetok->stringval);
     typ->kind = BASICTYPE;
     int align;

     switch(typetok->stringval[0])
     {
       case 'i': typ->basicdt = INTEGER; break;
       case 'r': typ->basicdt = REAL; break;
       case 's': typ->basicdt = STRINGTYPE; break;
       case 'b': typ->basicdt = BOOLETYPE; break;
     }
     typ->size = basicsizes[typ->basicdt];
     align = (typ->size > WORDSIZE) ? ALIGNSIZE : typ->size;

     while (idlist != NULL)
     {  sym = insertsym(idlist->stringval);
        sym->kind = VARSYM;
        sym->offset = wordaddress(blockoffs[blocknumber],align);
        sym->size = typ->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        sym->datatype = typ;
        sym->basicdt = typ->basicdt;
        idlist = idlist->link;
     }

     if (DEBUG & DB_INSTVARS)
     { printf("instvars\n");
       dbugprinttok(idlist);
       dbugprinttok(typetok);
     }
  }

/* assign the new variable's location in memory */
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
    printst();
    printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    ppexpr(parseresult);           /* Pretty-print the result tree */
  }
