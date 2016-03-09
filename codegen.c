
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "symtab.h"
#include "genasm.h"
#include "codegen.h"

void genc(TOKEN code);

int usdrg[24];
int rbse = RBASE;
int fbse = FBASE;

/* Set DEBUGGEN to 1 for debug printouts of code generation */
#define DEBUGGEN 0

int nextlabel;    /* Next available label number */
int stkframesize;   /* total stack frame size */

/* Top-level entry for code generator.
   pcode    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

The generated code is printed out; use a text editor to extract it for
your .s file.
         */

void gencode(TOKEN pcode, int varsize, int maxlabel)
  {  TOKEN name, code;
     name = pcode->operands;
     code = name->link->link;
     nextlabel = maxlabel + 1;
     stkframesize = asmentry(name->stringval,varsize);
     genc(code);
     asmexit(name->stringval);
  }

/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getreg(int kind)
  {
     int i = 0;
     int regfnd = 0;

     while(i <= RMAX & kind == WORD & regfnd == 0)
     {
       if(usdrg[i] == 0)
       { regfnd = 1;
         usdrg[i] = 1;
         break;
       }
       i++;
     }

     if(regfnd == 0)
     { i = 8;
       while(i <= FMAX & regfnd == 0)
       { if(usdrg[i] == 0)
         { regfnd = 1;
           usdrg[i] = 1;
           break;
         }
         i++;
       }
     }

     if(regfnd == 0) printf("\n\nNO MORE REGISTERS\n\n");
     
     return i;
  }

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code)
  {  int num1, num2, reg1, reg2, offs;
     TOKEN tok, lhs, rhs;
     SYMBOL sym, lsym, rsym;
     if (DEBUGGEN)
     { printf("genarith\n");
         dbugprinttok(code);
     };

     // This switch determines how to handle the token based on its type
     switch ( code->tokentype )
     { case NUMBERTOK:
         switch (code->datatype)
         { case INTEGER:
	           num1 = code->intval;
             reg1 = getreg(WORD);
             if (code->symtype != NULL)
             { if(code->symtype->kind == POINTERSYM)
                 asmimmed(MOVQ, num1, reg1);
             }
         	   else if ( num1 >= MINIMMEDIATE && num1 <= MAXIMMEDIATE )
               asmimmed(MOVL, num1, reg1);
             break;
           case REAL:
             reg1 = getreg(FLOAT);
             makeflit(code->realval, nextlabel++);
             asmldflit(MOVSD, nextlabel-1, reg1);
          	 break;
         }
         break;


       case IDENTIFIERTOK:
         reg1 = getreg(WORD);
         sym = code->symentry;
         offs = sym->offset - stkframesize;
         asmld(MOVQ, offs, reg1, code->stringval);
         break;


       case OPERATOR:
         switch(code->whichval)
         { case PLUSOP:
             lhs = code->operands;
             rhs = lhs->link;
             lsym = lhs->symentry;
             rsym = rhs->symentry;

             if(lsym != NULL & lhs->tokentype != NUMBERTOK)
             {
               switch(lsym->basicdt)
               { case INTEGER: reg1 = getreg(WORD); break;
                 case REAL: reg1 = getreg(FLOAT); break;
               }
               asmldr(MOVL, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
             }
             else
             { if(lhs->tokentype == OPERATOR) reg1 = genarith(lhs);
               else switch(lhs->datatype)
               { case INTEGER:
                   reg1 = getreg(WORD);
                   asmimmed(MOVL, lhs->intval, reg1);
                   break;
                 case REAL:
                   reg1 = getreg(FLOAT);
                   makeflit(lhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg1);
                   break;
               }
             }
             if(rsym != NULL & rhs->tokentype != NUMBERTOK)
             {
               switch(rsym->basicdt)
               { case INTEGER: reg2 = getreg(WORD); break;
                 case REAL: reg2 = getreg(FLOAT); break;
               }
               asmldr(MOVL, rsym->offset - stkframesize, RBP, reg2, rsym->namestring);
             }
             else
             { if(rhs->tokentype == OPERATOR) reg2 = genarith(rhs);
               else switch(rhs->datatype)
               { case INTEGER:
                   reg2 = getreg(WORD);
                   asmimmed(MOVL, rhs->intval, reg2);
                   break;
                 case REAL:
                   reg2 = getreg(FLOAT);
                   makeflit(rhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg2);
                   break;
               }
             }
             if(reg1 < 8 & reg2 < 8)
               asmrr(ADDL, reg2, reg1);
             else
               asmrr(ADDSD, reg2, reg1);
             unused(reg2);
           break;
           
           case MINUSOP:
             lhs = code->operands;
             lsym = lhs->symentry;
             rhs = lhs->link;

             if(rhs == NULL) //if this is just a negation
             { if(lsym != NULL & lhs->tokentype != NUMBERTOK)
               { 
                 switch(lsym->basicdt)
                 { case INTEGER:
                     reg1 = getreg(WORD);
                     asmldr(MOVL, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                     break;
                   case REAL:
                     reg1 = getreg(FLOAT);
                     reg2 = getreg(FLOAT);
                     asmldr(MOVSD, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                     asmfneg(reg1, reg2);
                     unused(reg2);
                     break;
                 }
               }
               else
               { if(lhs->tokentype == OPERATOR) reg1 = genarith(lhs);
                 else switch(lhs->datatype)
                 { case INTEGER:
                     reg1 = getreg(WORD);
                     asmimmed(MOVL, lhs->intval, reg1);
                     break;
                   case REAL:
                     reg1 = getreg(FLOAT);
                     reg2 = getreg(FLOAT);
                     asmldflit(MOVSD, nextlabel++, reg1);
                     asmfneg(reg1, reg2);
                     unused(reg2);
                     break;
                 }
               }
               return reg1;
             }

             rsym = rhs->symentry;

             if(lsym != NULL & lhs->tokentype != NUMBERTOK)
             {
               switch(lsym->basicdt)
               { case INTEGER:
                   reg1 = getreg(WORD);
                   asmldr(MOVL, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                   break;
                 case REAL:
                   reg1 = getreg(FLOAT);
                   asmldr(MOVSD, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                   break;
               }
             }
             else
             { if(lhs->tokentype == OPERATOR) reg1 = genarith(lhs);
               else switch(lhs->datatype)
               { case INTEGER:
                   reg1 = getreg(WORD);
                   asmimmed(MOVL, lhs->intval, reg1);
                   break;
                 case REAL:
                   reg1 = getreg(FLOAT);
                   makeflit(lhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg1);
                   break;
               }
             }
             if(rsym != NULL & rhs->tokentype != NUMBERTOK)
             {
               switch(rsym->basicdt)
               { case INTEGER:
                   reg2 = getreg(WORD);
                   asmldr(MOVL, rsym->offset - stkframesize, RBP, reg2, rsym->namestring);
                   break;
                 case REAL:
                   reg2 = getreg(FLOAT);
                   asmldr(MOVSD, rsym->offset - stkframesize, RBP, reg2, rsym->namestring);
                   break;
               }

             }
             else
             { if(rhs->tokentype == OPERATOR) reg2 = genarith(rhs);
               else switch(rhs->datatype)
               { case INTEGER:
                   reg2 = getreg(WORD);
                   asmimmed(MOVL, rhs->intval, reg2);
                   break;
                 case REAL:
                   reg2 = getreg(FLOAT);
                   makeflit(rhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg2);
                   break;
               }
             }
             if(reg1 < 8 & reg2 < 8)
               asmrr(SUBL, reg2, reg1);
             else
               asmrr(SUBSD, reg2, reg1);
             unused(reg2);
           break;

           case TIMESOP:
             lhs = code->operands;
             rhs = lhs->link;
             lsym = lhs->symentry;
             rsym = rhs->symentry;

             if(lsym != NULL & lhs->tokentype != NUMBERTOK)
             {
               switch(lsym->basicdt)
               { case INTEGER:
                   reg1 = getreg(WORD);
                   asmldr(MOVL, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                   break;
                 case REAL:
                   reg1 = getreg(FLOAT);
                   asmldr(MOVSD, lsym->offset - stkframesize, RBP, reg1, lsym->namestring);
                   break;
               }
             }
             else
             { if(lhs->tokentype == OPERATOR)
               { reg1 = genarith(lhs);
                 if(lhs->whichval == FUNCALLOP & rhs->whichval == FUNCALLOP)
                 { asmsttemp(reg1);
                   unused(reg1);
                 }
               }
               else switch(lhs->datatype)
               { case INTEGER:
                   reg1 = getreg(WORD);
                   asmimmed(MOVL, lhs->intval, reg1);
                   break;
                 case REAL:
                   reg1 = getreg(FLOAT);
                   makeflit(lhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg1);
                   break;
               }
             }

             if(rsym != NULL & rhs->tokentype != NUMBERTOK)
             {
               switch(rsym->basicdt)
               { case INTEGER:
                   reg2 = getreg(WORD);
                   asmldr(MOVL, rsym->offset - stkframesize, RBP, reg2, rsym->namestring);
                   break;
                 case REAL:
                   reg2 = getreg(FLOAT);
                   asmldr(MOVSD, rsym->offset - stkframesize, RBP, reg2, rsym->namestring);
                   break;
               }
             }
             else
             { if(rhs->tokentype == OPERATOR)
               { reg2 = genarith(rhs);
                 if(lhs->whichval == FUNCALLOP & rhs->whichval == FUNCALLOP)
                 { switch(lhs->datatype)
                   { case INTEGER: reg1 = getreg(WORD); break;
                     case REAL: reg1 = getreg(FLOAT); break;
                   }
                   asmldtemp(reg1);
                 }
               }
               else switch(rhs->datatype)
               { case INTEGER:
                   reg2 = getreg(WORD);
                   asmimmed(MOVL, rhs->intval, reg2);
                   break;
                 case REAL:
                   reg2 = getreg(FLOAT);
                   makeflit(rhs->realval, nextlabel++);
                   asmldflit(MOVSD, nextlabel-1, reg2);
                   break;
               }
             }
             if(reg1 < 8 & reg2 < 8)
               asmrr(IMULL, reg2, reg1);
             else
               asmrr(MULSD, reg2, reg1);
             unused(reg2);
           break;

           case FLOATOP:
             lhs = code->operands;
             lsym = lhs->symentry;
             reg1 = getreg(FLOAT);
             reg2 = getreg(WORD);
             asmldr(MOVL, lsym->offset - stkframesize, RBP, reg2, lsym->namestring);
             asmfloat(reg2, reg1);
             unused(reg2);
             break;

           case FUNCALLOP:
             tok = code->operands;
             if(tok->link != NULL)
             {
               switch(tok->link->tokentype)
               { case STRINGTOK:
                      asmlitarg(nextlabel++, EDI);
                      makeblit(tok->link->stringval, nextlabel-1);
                      asmcall(tok->stringval);
                      break;
                 case OPERATOR:
                      reg1 = genarith(tok->link);
                      break;
                 case NUMBERTOK:
                      switch(tok->link->datatype)
                      { case INTEGER:
                          reg1 = getreg(WORD);
                          asmimmed(MOVL,tok->link->intval,reg1);
                          asmrr(MOVL, reg1, EDI);
                          break;
                        case REAL:
                          reg1 = getreg(FLOAT);
                          asmimmed(MOVSD,tok->link->realval,reg1);
                          asmrr(MOVSD, reg1, EDI);
                          break;
                      }
                      
             }
           }
           asmcall(tok->stringval);
           break; 

         case FIXOP:
           reg1 = getreg(WORD);
           reg2 = genarith(code->operands);
           asmfix(reg2,reg1);           
           break;

         case POINTEROP:
           lhs = code->operands;
           if(lhs->tokentype == OPERATOR & lhs->whichval == AREFOP)
           { reg1 = genarith(lhs);
           }
           else
           { reg1 = getreg(WORD);
             lsym = code->operands->symentry;
             asmld(MOVQ, lsym->offset - stkframesize, reg1, code->operands->stringval);
           }
           break;

         case AREFOP:
           lhs = code->operands;
           rhs = lhs->link;
           
           if(lhs->tokentype == OPERATOR & lhs->whichval == POINTEROP)
           { reg2 = genarith(lhs->operands);

             if(lhs->symtype != NULL)
             { if(lhs->symtype->basicdt == REAL) 
               { reg1 = getreg(FLOAT);

                 asmldr(MOVSD, rhs->intval, reg2, reg1, "^. ");
                 unused(reg2);
                 break;
               }
             }
             reg1 = getreg(WORD);
             asmldr(MOVQ, rhs->intval, reg2, reg1, "^. ");
            

           }

           unused(reg2);
           break;
         }
         break;
    };
    return reg1;
  }


/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
  {  TOKEN tok, lhs, rhs;
     int reg, reg2, offs, jmpval, loop1, loop2;
     SYMBOL sym, lsym, rsym;
     if (DEBUGGEN)
       { printf("genc\n");
         dbugprinttok(code);
       };
     if ( code->tokentype != OPERATOR )
       { printf("Bad code token");
         dbugprinttok(code);
       };

     // This switch statement will determine how to handle the token based on its operator value
     switch ( code->whichval )
       { case PROGNOP:
           tok = code->operands;
           while ( tok != NULL )
           {  genc(tok);
              tok = tok->link;
           };
	         break;
           
         case ASSIGNOP:                   /* Trivial version: handles I := e */
           lhs = code->operands;
           rhs = lhs->link;
           reg = genarith(rhs);              /* generate rhs into a register */
           if(rhs != NULL) rsym = rhs->symentry;

           if(lhs->tokentype == OPERATOR & lhs->whichval == AREFOP)
           { if(lhs->operands->tokentype != OPERATOR & lhs->operands->whichval != POINTEROP)
             { if(lhs->operands->link->tokentype == NUMBERTOK)
               { lsym = lhs->operands->symentry;
                 reg2 = getreg(WORD);
                 asmimmed(MOVL, lhs->operands->link->intval, reg2);
                 asmop(CLTQ);
                 if(reg < 8 & reg2 < 8)
                 {
                   asmstrr(MOVL, reg, lsym->offset - stkframesize, reg2, lhs->operands->stringval);
                 }
                 else
                 {
                   asmstrr(MOVSD, reg, lsym->offset - stkframesize, reg2, lhs->operands->stringval);
                 }
                 break;
               }
               else
               { reg2 = genarith(lhs->operands->link); 
                 asmop(CLTQ);
                 lsym = lhs->operands->symentry;
                 if(reg < 8 & reg2 < 8)
                 {
                   asmstrr(MOVL, reg, lsym->offset - stkframesize, reg2, lhs->operands->stringval);
                 }
                 else
                 {
                   asmstrr(MOVSD, reg, lsym->offset - stkframesize, reg2, lhs->operands->stringval);
                 }
                 break;
               }
             }
             reg2 = genarith(lhs->operands);
             offs = lhs->operands->link->intval;


             if(rsym != NULL)
             { if(rsym->datatype->kind == POINTERSYM)
                  asmstr(MOVQ, reg, offs, reg2, "^. ");
               else
               { if (reg < 8 & reg2 < 8) asmstr(MOVL, reg, offs, reg2, "^. ");
                 else asmstr(MOVSD, reg, offs, reg2, "^. ");
               }
             }
             else
             { if (reg < 8 & reg2 < 8) asmstr(MOVL, reg, offs, reg2, "^. ");
               else asmstr(MOVSD, reg, offs, reg2, "^. ");
             }
             unused(reg);
             break;
           }
           else
           { lsym = lhs->symentry;              /* assumes lhs is a simple var  */
             offs = lsym->offset - stkframesize; /* net offset of the var   */
           }

           if(lsym->datatype->kind == POINTERSYM)
           { asmst(MOVQ, reg, offs, lhs->stringval);
           }
           else
           { switch (code->datatype)            /* store value into lhs  */
             { case INTEGER:
                 asmst(MOVL, reg, offs, lhs->stringval);
                 break;
               case REAL:
                 asmst(MOVSD, reg, offs, lhs->stringval);
                 break;
             }
           }
           unused(reg);
           break;
         
         case PLUSOP:
           lhs = code->operands;
           rhs = lhs->link;
           lsym = lhs->symentry;
           rsym = rhs->symentry;

           if(lsym != NULL & lhs->tokentype != NUMBERTOK)
             asmldr(MOVL, lsym->offset - stkframesize, RBP, EAX, lsym->namestring);
           else
             asmimmed(MOVL, lhs->intval, EAX);
           if(rsym != NULL & rhs->tokentype != NUMBERTOK)
             asmldr(MOVL, rsym->offset - stkframesize, RBP, ECX, rsym->namestring);
           else
             asmimmed(MOVL, rhs->intval, ECX);
           asmrr(ADDL, ECX, EAX);
           break;
         case LABELOP:
           lhs = code->operands;
           asmlabel(lhs->intval);
           break;
         
         case IFOP:
           tok = code->operands;
           lhs = tok->operands;
           rhs = lhs->link;
           lsym = lhs->symentry;
           rsym = rhs->symentry;
           loop1 = nextlabel++;
           loop2 = nextlabel++;

           if(rhs->symtype != NULL)
           { if (rhs->symtype->kind == POINTERSYM)
             { 
               if(lsym != NULL & lhs->tokentype != NUMBERTOK)
                 asmldr(MOVQ, lsym->offset - stkframesize, RBP, EAX, lsym->namestring);
               else
                 asmimmed(MOVQ, lhs->intval, EAX);
               if(rsym != NULL & rhs->tokentype != NUMBERTOK)
                 asmldr(MOVQ, rsym->offset - stkframesize, RBP, ECX, rsym->namestring);
               else
                 asmimmed(MOVQ, rhs->intval, ECX);

               asmrr(CMPQ, ECX, EAX);
             }  
             else
             { 
               if(lsym != NULL & lhs->tokentype != NUMBERTOK)
                 asmldr(MOVL, lsym->offset - stkframesize, RBP, EAX, lsym->namestring);
               else
                 asmimmed(MOVL, lhs->intval, EAX);
               if(rsym != NULL & rhs->tokentype != NUMBERTOK)
                 asmldr(MOVL, rsym->offset - stkframesize, RBP, ECX, rsym->namestring);
               else
                 asmimmed(MOVL, rhs->intval, ECX);

               asmrr(CMPL, ECX, EAX);
             }  
           }
           else
           { 
             if(lsym != NULL & lhs->tokentype != NUMBERTOK)
               asmldr(MOVL, lsym->offset - stkframesize, RBP, EAX, lsym->namestring);
             else
               asmimmed(MOVL, lhs->intval, EAX);
             if(rsym != NULL & rhs->tokentype != NUMBERTOK)
               asmldr(MOVL, rsym->offset - stkframesize, RBP, ECX, rsym->namestring);
             else
               asmimmed(MOVL, rhs->intval, ECX);

             asmrr(CMPL, ECX, EAX);
           }

           switch(tok->whichval)
           { case EQOP: jmpval = JE;  break;
             case NEOP: jmpval = JNE; break;
             case LTOP: jmpval = JL;  break;
             case LEOP: jmpval = JLE; break;
             case GEOP: jmpval = JGE; break;
             case GTOP: jmpval = JG;  break;
           }
           asmjump(jmpval, loop1);



           tok = tok->link;
           //else part
           if(tok->link != NULL) genc(tok->link);

           asmjump(JMP, loop2);
           //if part
           asmlabel(loop1);
           genc(tok);



           asmlabel(loop2);

           break;
         case GOTOOP:
           lhs = code->operands;
           asmjump(JMP, lhs->intval);
           break;
         case FUNCALLOP:
           tok = code->operands;
           rhs = tok->link;
           if(rhs != NULL)
           {

             switch(rhs->tokentype)
             { case STRINGTOK:
                 asmlitarg(nextlabel++, EDI);
                 makeblit(rhs->stringval, nextlabel-1);
                 asmcall(tok->stringval);
                 break;
               case IDENTIFIERTOK:
                 rsym = rhs->symentry;
                 reg = getreg(WORD);
                 asmld(MOVL, rsym->offset - stkframesize, reg, rhs->stringval);
                 asmrr(MOVL, reg, EDI);
                 asmcall(tok->stringval);
                 break;
               case OPERATOR:
                 rsym = rhs->symentry;
                 reg = getreg(FLOAT);
                 asmld(MOVL, -1000, EAX, rhs->operands->operands->stringval);
                 asmldr(MOVSD, rhs->operands->link->intval, EAX, XMM0, "^. ");
                 asmcall(tok->stringval);
                 break;
             }
           }

           break;

	    };
  clearreg();
  }

void used(int reg)
{ usdrg[reg] = 1;
}

void unused(int reg)
{ usdrg[reg] = 0;
}

void clearreg()
{
  int i = RBASE;
  while (i <= FMAX) usdrg[i++] = 0;
}

void clearfreg()
{
  int i = FBASE;
  while (i <= FMAX) usdrg[i++] = 0;
}
