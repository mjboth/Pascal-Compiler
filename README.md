Pascal-Compiler
=====
A compiler that converts Pascal source code into x86 assembly code.

**NOTE:** This compiler assumes the source code being compiled is syntactically correct, it will not give compile-time errors.  Works on 64-bit Linux machines, *Bash on Ubuntu on Windows* will be required to run on Windows 10.


## Files

* **lexan.l** - **Source Code** Used to create the Lexer.  Reads through the user's source code while labeling all of the code's significant items as tokens while ignoring user comments.
* **parse.y** - **Source Code** Used to create the Parser.  Declares all legal patterns the tokens can be arranged.  Then reads from the generated token list to see if they match a declared pattern while connecting the tokens together to form a binary tree that will organize how the program will run.  Also creates and lists any user declared variables.
* **codegen.c** - **Source Code** Writes the assembly code.  Reads through the binary tree created by the parser and generates x86 assembly code while keeping track of the variables and registers.
* **compiler** - fully compiled lexan.l + parser.y + codgen.c
* ForCompilingTheCompiler.zip - a compressed folder containing all files necessary to compile the compiler itself. GNU Make, Lex, Yacc, and CC are required to use the makefile.
* ExamplePascal.zip - contains several Pascal files known to work on this compiler.


## How to use

Download "compiler" from the respository, you will also need a pascal file ready to use.  Remember that this compiler does not check for syntax errors, so I recommend taking a pascal file from "ExamplePascal.zip".

In the Unix shell, run the following command in the directory you are keeping the files:

	compiler < [FILENAME].pas > code.s

To create the assembly file **code.s**.


## How it works

There are 3 parts to the compiler: The **Lexer**, the **Parser**, and the **Assembly Code Generator**.  

#### Lexer

The Lexer works by reading in a pascal file byte-by-byte; looking out for and words, characters, symbols, numbers, or regular expressions declared in the "lexan.l" file while ignoring any user comments.  It takes any significant expression and declares that item as a token, which is identified to be either an operator, delimiter, identifier, string, number, or reserved word.  It may then assign the token a subtype if it is an operator/delimiter/reserved/number, just to be more specific about what type of token it is.  The lexer will then write out the tokens for the parser to read.

#### Parser

The Parser reads through the tokens in chronological order to see if they form a legal syntax that was declared in "parser.y". As it reads through, it connects the instruction tokens together to create a binary tree that represents the order the code will be executed.

#### Assebly Generator

The Assembly Generator reads through the binary tree of instruction tokens starting from the root in a depth-first traversal and writes out the assembly code as it goes.


## Features

This compiler understands the following Pascal terms:

#### Reserved Words:

###### Declarations
<pre>
	<b>program</b> - Identifies the start of the program, must be followed with the program name, arguments, then the declarations.
	<b>label</b>   - Begins the block of declarations of labels that state where the program can jump to. Labels, if used, must be declared first.
	<b>const</b>   - Begins the block of declaration and initialization of constants.  Constants, if declared, must come after the label declarations.
	<b>type</b>    - Begins the block of declaration of datatypes.  These user named datatypes can hold information of what datatypes a record will store, what datatype a pointer will point to, what the type of a array is, enums, etc...  Must be declared after labels and constants.
	<b>var</b>     - Begins the block of declaration of variables. All variables must either be an integer, real number, or a previously declared *type*.  Must be declared last
	<b>record</b>  - A collection of variables, used in datatype and variable declarations.
	<b>begin</b>   - Begins a new block of statements to execute.
	<b>end</b>     - Closes the block of statements from the last begin statement.
	<b>nil</b>     - Zero
</pre>

###### Loops
<pre>
	<b>repeat</b>  - Begins what is essentially a Do-While loop.
	<b>until</b>   - Marks the end of a repeat statement when the following conditional is met.
	<b>for</b>     - Declares a for-loop
	<b>to</b>      - Used in a for-loop's conditional statement: the initialized value will be incremented to the following value
	<b>downto</b>  - Used in a for-loop's conditional statement: the initialized value will be decremented to the following value
	<b>while</b>   - Begins a while-loop.
	<b>do</b>      - Placed after a for/while loop's conditional statement: identifies the statement (or block of statements) the loop will execute.
	<b>goto</b>    - Jumps the program to a provided label number
</pre>

###### If
<pre>
	<b>if</b>      - Begins an if-statement.
	<b>then</b>    - Statement (or block of statements) to execute when the if-statement returns true.
</pre>

###### Arrays
<pre>
	<b>array</b>   - Declares a new array in the variable declarations.  Array size must also be declared here; integers, subranges, and enums are accepted.  Multidimensional declarations are also allowed.
	<b>of</b>      - Declares the type of values an array will store.
</pre>

###### Fucntion Calls
<pre>
	<b>write()</b>    - Prints an integer, real number, or a string
	<b>writeln()</b>  - Prints an integer, real number, or a string followed by a new line character
</pre>

#### Recognized Operators:
<pre>
	<b>+</b>    Addition
	<b>-</b>    Subtraction
	<b>*</b>    Multiplication
	<b>/</b>    Division
	<b><</b>    Less than
	<b><=</b>   Less than or equal
	<b>=</b>    Equal to
	<b><></b>   Not equal to
	<b>></b>    Greater than
	<b>>=</b>   Greater than or equal to
	<b>:=</b>   Assign value
	<b>^</b>    Declare/dereference Pointer
	<b>.</b>    Get record field/declare the end of the program
</pre>

#### Delimiters:
<pre>
	<b>;</b>    End statement
	<b>,</b>    Pass another value 
	<b>:</b>    Declare variable type or label number
	<b>(</b>    Pass function argument or prioritize operations
	<b>)</b>    Close left parenthesis
	<b>[</b>    For array indexes
	<b>]</b>    Close left bracket
	<b>..</b>   Initialize array subrange
	<b>{</b> or (*</b> Begin comments
	<b>}</b> or *)</b> End comments
</pre>


## Building the Compiler

If you want to see each step of the compiler in action, grab some pascal code out of "ExamplePascal.zip", then download and unpack "ForCompilingTheCompiler.zip".

**NOTE:** Make, Lex, Yacc, and CC are required for compiling Lexer, Parser, and Compiler.  Each step of the compiler contains all the steps that came before it.  Lexer is made from "lexan.l"; Parser is made from of "lexan.l", and "parse.y"; and Compiler is made up of "lexan.l", "parse.y", and "codegen.c".  There is no need to compile each step one at a time or in order.

##### Lexer

To view the token list, grab and unpack "ForCompilingTheCompiler.zip" from this repository and run the commands:

	make lexer
	lexer < [FILENAME].pas

##### Parser

To see the variable types, identifiers, constants declared in the user's program along with the binary tree produced, grab and extract "ForCompilingTheCompiler.zip".  Restore the commented out lines in the main function of "parse.y".  Then execute:

	make parser
	parser < [FILENAME].pas

##### Assembly Generator

To build the last stage of the compiler and see the assembly code produced by your pascal code, run:

	make compiler
	compiler < [FILENAME].pas
	
##### Creating an executable

This compiler will only go as far as to create the assembly code, but we can assemble the code produced into a machine language executable through the following commands:

	compiler < [FILENAME].pas > code.s
	cc driver.c code.s -lm

"driver.c", which is stored in "ForCompilingTheCompiler.zip", is used to generate the write() function calls that may be needed by the user's program.


## Example

This example shows what happens to "graph1.pas" as it goes through each step of the compiler.

#### Pascal Code

	{ program 4.9 from Jensen & Wirth       -- file pastst.pas }

	program graph1(output);
	const d = 0.0625; {1/16, 16 lines for interval [x,x+1]}
	      s = 32; {32 character widths for interval [y,y+1]}
	      h = 34; {character position of x-axis}
	      c = 6.28318; {2*pi}  lim = 32;
	var x,y : real;  i,n : integer;
	begin
	   for i := 0 to lim do
	      begin x := d*i; y := exp(-x)*sin(c*x);
	      n := round(s*y) + h;
	      repeat write(' ');  n := n-1
	      until n=0;
	      writeln('*')
	   end
	end.

#### Lexer

	yylex() =  306   tokentype:  2  which:   19      program
	yylex() =  258   tokentype:  3  value:            graph1
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  258   tokentype:  3  value:            output
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  291   tokentype:  2  which:    4        const
	yylex() =  258   tokentype:  3  value:                 d
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     1 6.250000e-02
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 s
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     0           32
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 h
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     0           34
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 c
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     1 6.283180e+00
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:               lim
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     0           32
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  314   tokentype:  2  which:   27          var
	yylex() =  258   tokentype:  3  value:                 x
	yylex() =  280   tokentype:  1  which:    1            ,
	yylex() =  258   tokentype:  3  value:                 y
	yylex() =  282   tokentype:  1  which:    3            :
	yylex() =  258   tokentype:  3  value:              real
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 i
	yylex() =  280   tokentype:  1  which:    1            ,
	yylex() =  258   tokentype:  3  value:                 n
	yylex() =  282   tokentype:  1  which:    3            :
	yylex() =  258   tokentype:  3  value:           integer
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  289   tokentype:  2  which:    2        begin
	yylex() =  297   tokentype:  2  which:   10          for
	yylex() =  258   tokentype:  3  value:                 i
	yylex() =  265   tokentype:  0  which:    5           :=
	yylex() =  260   tokentype:  5  type:     0            0
	yylex() =  311   tokentype:  2  which:   24           to
	yylex() =  258   tokentype:  3  value:               lim
	yylex() =  292   tokentype:  2  which:    5           do
	yylex() =  289   tokentype:  2  which:    2        begin
	yylex() =  258   tokentype:  3  value:                 x
	yylex() =  265   tokentype:  0  which:    5           :=
	yylex() =  258   tokentype:  3  value:                 d
	yylex() =  263   tokentype:  0  which:    3            *
	yylex() =  258   tokentype:  3  value:                 i
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 y
	yylex() =  265   tokentype:  0  which:    5           :=
	yylex() =  258   tokentype:  3  value:               exp
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  262   tokentype:  0  which:    2            -
	yylex() =  258   tokentype:  3  value:                 x
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  263   tokentype:  0  which:    3            *
	yylex() =  258   tokentype:  3  value:               sin
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  258   tokentype:  3  value:                 c
	yylex() =  263   tokentype:  0  which:    3            *
	yylex() =  258   tokentype:  3  value:                 x
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 n
	yylex() =  265   tokentype:  0  which:    5           :=
	yylex() =  258   tokentype:  3  value:             round
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  258   tokentype:  3  value:                 s
	yylex() =  263   tokentype:  0  which:    3            *
	yylex() =  258   tokentype:  3  value:                 y
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  261   tokentype:  0  which:    1            +
	yylex() =  258   tokentype:  3  value:                 h
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  308   tokentype:  2  which:   21       repeat
	yylex() =  258   tokentype:  3  value:             write
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  259   tokentype:  4  value:                  
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:                 n
	yylex() =  265   tokentype:  0  which:    5           :=
	yylex() =  258   tokentype:  3  value:                 n
	yylex() =  262   tokentype:  0  which:    2            -
	yylex() =  260   tokentype:  5  type:     0            1
	yylex() =  313   tokentype:  2  which:   26        until
	yylex() =  258   tokentype:  3  value:                 n
	yylex() =  266   tokentype:  0  which:    6            =
	yylex() =  260   tokentype:  5  type:     0            0
	yylex() =  281   tokentype:  1  which:    2            ;
	yylex() =  258   tokentype:  3  value:           writeln
	yylex() =  283   tokentype:  1  which:    4            (
	yylex() =  259   tokentype:  4  value:                 *
	yylex() =  284   tokentype:  1  which:    5            )
	yylex() =  295   tokentype:  2  which:    8          end
	yylex() =  295   tokentype:  2  which:    8          end
	yylex() =  273   tokentype:  0  which:   13            .

#### Parser

	Symbol table level 0
	 25665552        real  BASIC  basicdt   1          siz     8
	 25665648     integer  BASIC  basicdt   0          siz     4
	 25665744        char  BASIC  basicdt   2          siz     1
	 25665840     boolean  BASIC  basicdt   3          siz     4
	Symbol table level 1
	 25690000         lim  CONST  typ INTEGER  val  32
	 25690096           c  CONST  typ    REAL  val  6.283180e+00
	 25690192           h  CONST  typ INTEGER  val  34
	 25690288           s  CONST  typ INTEGER  val  32
	 25690384           d  CONST  typ    REAL  val  6.250000e-02
	 25691408           i  VAR    0 typ integer  lvl  1  siz     4  off     0
	 25691504           n  VAR    0 typ integer  lvl  1  siz     4  off     4
	 25691696           x  VAR    1 typ    real  lvl  1  siz     8  off    16
	 25691792           y  VAR    1 typ    real  lvl  1  siz     8  off    32
	yyparse result =        0
	 token 25697648  OP       program  dtype  0  link 0  operands 25688272
	(program graph1 (progn output)
	                (progn (progn (:= i 0)
	                              (label 1)
	                              (if (<= i 32)
	                                  (progn (progn (:= x (* 6.250000e-02
	                                                         (float i)))
	                                                (:= y (* (funcall exp
	                                                                  (- x))
	                                                         (funcall sin
	                                                                  (* 6.283180e+00
	                                                                     x))))
	                                                (:= n (fix (+ (funcall round
	                                                                       (* 3.200000e+01
	                                                                          y))
	                                                              3.400000e+01)))
	                                                (progn (label 0)
	                                                       (funcall write
	                                                                ' ')
	                                                       (:= n (- n
	                                                                1))
	                                                       (if (= n
	                                                              0)
	                                                           (progn)
	                                                           (goto 0)))
	                                                (funcall writeln '*'))
	                                         (:= i (+ i 1))
	                                         (goto 1))))))

#### Assembly Code

	# ---------------- Beginning of Generated Code --------------------
	        .file   "foo"
	        .text
	.globl graph1
	        .type   graph1, @function
	graph1:
	.LFB0:
		.cfi_startproc
		pushq	%rbp              # save base pointer on stack
		.cfi_def_cfa_offset 16
		movq	%rsp, %rbp        # move stack pointer to base pointer
		.cfi_offset 6, -16
		.cfi_def_cfa_register 6
	        subq	$48, %rsp 	  # make space for this stack frame
		movq	%rbx, %r9        # save %rbx (callee-saved) in %r9
	# ------------------------- begin Your code -----------------------------
		movl	$0,%eax         	#  0 -> %eax
		movl	%eax,-32(%rbp)     	#  %eax -> i
	.L1:
		movl	-32(%rbp),%eax     	#  i -> %eax
		movl	$32,%ecx         	#  32 -> %ecx
		cmpl	%ecx,%eax           	#  compare %eax - %ecx
		jle	.L3 			#  jump if     <=
		jmp	.L4 			#  jump 
	.L3:
		movsd	.LC5(%rip),%xmm0   	#  0.062500 -> %xmm0
		movl	-32(%rbp),%eax     	#  i -> %eax
		cvtsi2sd	%eax,%xmm1    	#  float %eax -> %xmm1
		mulsd	%xmm1,%xmm0         	#  %xmm0 * %xmm1 -> %xmm0
		movsd	%xmm0,-48(%rbp)     	#  %xmm0 -> x
		movsd	-48(%rbp),%xmm0     	#  x -> %xmm0
		movsd	.LC666(%rip),%xmm1   	#  0.000000 -> %xmm1
		xorpd	%xmm1,%xmm0           	#  negate %xmm0
		call	exp              	#  exp()
		movsd	%xmm0,-8(%rbp)     	#  %xmm0 -> temp
		movsd	.LC6(%rip),%xmm0   	#  6.283180 -> %xmm0
		movsd	-48(%rbp),%xmm1     	#  x -> %xmm1
		mulsd	%xmm1,%xmm0         	#  %xmm0 * %xmm1 -> %xmm0
		call	sin              	#  sin()
		movsd	-8(%rbp),%xmm1     	#  temp -> %xmm1
		mulsd	%xmm0,%xmm1         	#  %xmm1 * %xmm0 -> %xmm1
		movsd	%xmm1,-40(%rbp)     	#  %xmm1 -> y
		movsd	.LC7(%rip),%xmm0   	#  32.000000 -> %xmm0
		movsd	-40(%rbp),%xmm1     	#  y -> %xmm1
		mulsd	%xmm1,%xmm0         	#  %xmm0 * %xmm1 -> %xmm0
		call	round              	#  round()
		movsd	.LC8(%rip),%xmm1   	#  34.000000 -> %xmm1
		addsd	%xmm1,%xmm0         	#  %xmm0 + %xmm1 -> %xmm0
		cvttsd2si	%xmm0,%eax    	#  fix %xmm0 -> %eax
		movl	%eax,-28(%rbp)     	#  %eax -> n
	.L0:
		movl	$.LC9,%edi       	#  addr of literal .LC9
		call	write              	#  write()
		movl	-28(%rbp),%eax     	#  n -> %eax
		movl	$1,%ecx         	#  1 -> %ecx
		subl	%ecx,%eax         	#  %eax - %ecx -> %eax
		movl	%eax,-28(%rbp)     	#  %eax -> n
		movl	-28(%rbp),%eax     	#  n -> %eax
		movl	$0,%ecx         	#  0 -> %ecx
		cmpl	%ecx,%eax           	#  compare %eax - %ecx
		je	.L10 			#  jump if     ==
		jmp	.L0 			#  jump 
		jmp	.L11 			#  jump 
	.L10:
	.L11:
		movl	$.LC12,%edi       	#  addr of literal .LC12
		call	writeln              	#  writeln()
		movl	-32(%rbp),%eax     	#  i -> %eax
		movl	$1,%ecx         	#  1 -> %ecx
		addl	%ecx,%eax         	#  %eax + %ecx -> %eax
		movl	%eax,-32(%rbp)     	#  %eax -> i
		jmp	.L1 			#  jump 
	.L4:
	# ----------------------- begin Epilogue code ---------------------------
		movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
	        leave
	        ret
	        .cfi_endproc
	.LFE0:
	        .size   graph1, .-graph1
	# ----------------- end Epilogue; Literal data follows ------------------
	        .section        .rodata
		.align 16
	.LC666:                    # constant for floating negation
		.long	0
		.long	-2147483648
		.long	0
		.long	0
		.align  4
	.LC9:
		.string	" "
		.align  4
	.LC12:
		.string	"*"
		.align  8
	.LC5:
		.long	0   	#  0.062500
		.long	1068498944
		.align  8
	.LC6:
		.long	0   	#  6.283180
		.long	1075388922
		.align  8
	.LC7:
		.long	0   	#  32.000000
		.long	1077936128
		.align  8
	.LC8:
		.long	0   	#  34.000000
		.long	1078001664

	        .ident  "CS 375 Compiler - Summer 2013"

#### Executable

	calling graph1
	                                  *
	                                              *
	                                                      *
	                                                           *
	                                                           *
	                                                        *
	                                                  *
	                                          *
	                                  *
	                           *
	                      *
	                   *
	                   *
	                     *
	                         *
	                             *
	                                  *
	                                      *
	                                         *
	                                           *
	                                           *
	                                          *
	                                        *
	                                     *
	                                  *
	                               *
	                              *
	                             *
	                            *
	                             *
	                               *
	                                *
	                                  *
	exit from graph1
