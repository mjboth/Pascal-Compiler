# Pascal-Compiler
A compiler that can convert Pascal source code into assembly code.

HOW TO USE:

I can only get this compiler to work on UNIX machines so far, but I am looking to getting it running on Windows.

You will need the cc compiler installed.

Download the following files from the respository: 

compiler & driver.c

You will also need a pascal file ready to use.  Note that this compiler will only work if everything is syntactically correct.  
It is not good for checking for errors.  I recommend taking one from ExampleInput.zip, keep all the files in the same directory.

In the Unix terminal run the following command in the directory you are keeping the files:

compiler < [PASCAL_SOURCECODE].pas > code.s

This will just convert the pascal source code into x86 assembly code.  Execute the following command afterwards:

cc driver.c code.s -lm

To add needed function calls to the assembly code while converting both files into one executable.


HOW IT WORKS:

There are 3 parts to the compiler: The LEXER, the PARSER, and the ASSEMBLY CODE GENERATOR.  

The Lexer works by reading in the pascal source code character by character looking out for and words, characters, symbols, numbers,
any regular expression declared in the lexan.l file while ignoring anything commented out by  "(*","*)","{*","*}".  
It any declared expression and assign that item to a token, which identifies the token to be either an operator, delimiter,
reserved word for the pascal language, identifier, string, or number.  It may then assign the token a subtype if it is an 
operator/delimiter/reserved/number, just to be more specific about what type of token it is.  The lexer will then return the 
tokens as they are read into an output format for the parser to read.

The Parser takes in each token one at a time to see if they are in an order declared to be legal in parser.y and handles the tokens
based on the pattern they follow to connect them together in a binary tree that shows how the final program will run through a
Lisp-like format while identifying all, variables, constants, labels used through out the program.

The Assembly Generator reads through the binary tree created by the parser and writes out the appropriate x86 assembly code to the
output file as it reads through.

FILES:

lexan.l - ORIGINAL SOURCE CODE, assembled by lex to declare a number of regular expressions, then to take in input from the scanner 
in RequireFiles.zip > lex.yy.c to see what regular expressions the readin characters match. Then labels them accordingly through
functions written in C, and writes them to an output file through RequiredFiles > printtoken.c

lexer - fully compiled lexan.l

parser.y - ORIGINAL SOURCE CODE, assembled by yacc to declare the legal patterns the tokens can be arranged.  Then reads from the
previously generated token list to see if they match a designated pattern, while attaching the tokens together in C functions called
by the patterns the tokens are ordered in, to form a binary tree that will display how the program will run/be written in assembly.  
Also declares and remembers variable identifiers, types, sizes as well as constant values, labels, etc.

parser - fully compiled lexan.l + parser.y

codegen.c - ORIGINAL SOURCE CODE, reads through the binary tree created by the parser and writes out the
apporpriate x86 assembly code while remembering which variables are stored in which registers.

compiler - fully compiled lexan.l + parser.y + codgen.c

RequiredFiles.zip - a compressed folder containing all files necessary to compile the compiler itself.  Does not include,
GNU Make, Lex, YACC, or CC, which are all needed in the makefile.

ExampleInput.zip - a small number of Pascal files that can run through all parts of the compiler.

UnusedFiles.zip - all untouched code and notes in a single flat directory.  If a file is missing it will be in here.


NOTE:

If you want to see each step of the compiler in action, just run:

lexer < [PASCAL_SOURCECODE].pas

to view the token list

parser < [PASCAL_SOURCECODE].pas

to see the variable types, identifiers, constants declared along with the binary tree produced (in a Lisp-ish format)

compiler < [PASCAL_SOURCECODE].pas

to see the assembly code produced.
