# Pascal-Compiler
***
A compiler that converts Pascal source code into x86 assembly code.

**NOTE:** This compiler only works on UNIX machines so far, but I am looking into how to get it running on Windows.

## How to use

This compiler only converts a Pascal file into and x86 assembly file.  To turn the assembly code into an executable, you will need the cc compiler installed.

Download the following files from the respository: 

###### compiler & driver.c

You will also need a pascal file ready to use.  Note that this compiler will only work if everything is syntactically correct.  
It is not good for checking for errors.  I recommend taking one from ExampleInput.zip, keep all the files in the same directory.

In the Unix terminal run the following command in the directory you are keeping the files:

	compiler < [PASCAL_SOURCECODE].pas > code.s

This will create the assembly file.  Execute the following command afterwards:

	cc driver.c code.s -lm

To assemble the final code into an executable while adding needed function calls.


## How it works

There are 3 parts to the compiler: The **Lexer**, the **Parser**, and the **Assembly Code Generator**.  

The Lexer works by reading in the pascal source code character by character looking out for and words, characters, symbols, numbers,
any regular expression declared in the lexan.l file while ignoring anything commented out by  "(\*","\*)","{","}".  
It any declared expression and assign that item to a token, which identifies the token to be either an operator, delimiter,
reserved word for the pascal language, identifier, string, or number.  It may then assign the token a subtype if it is an 
operator/delimiter/reserved/number, just to be more specific about what type of token it is.  The lexer will then return the 
tokens as they are read into an output format for the parser to read.

The Parser takes in each token one at a time to see if they are in an order declared to be legal in parser.y and handles the tokens
based on the pattern they follow to connect them together in a binary tree that shows how the final program will run through a
Lisp-like format while identifying all, variables, constants, labels used through out the program.

The Assembly Generator reads through the binary tree created by the parser and writes out the appropriate x86 assembly code to the
output file as it reads through.

## Features

This compiler understands the following Pascal terms:


#### Reserved Words:


###### Declarations

* **program** - Identifies the start of the program, must be followed with the program name, arguments, then the declarations.
* **label**   - Begins the block of declarations of labels that state where the program can jump to. Labels, if used, must be declared first.
* **const**   - Begins the block of declaration and initialization of constants.  Constants, if declared, must come after the label declarations.
* **type**    - Begins the block of declaration of datatypes.  These user named datatypes can hold information of what datatypes a record will store, what
datatype a pointer will point to, what the type of a array is, enums, etc...  Must be declared after labels and constants.
* **var**     - Begins the block of declaration of variables. All variables must either be an integer, real number, or a previously declared *type*.  
Must be declared last
* **record**  - A collection of variables, used in datatype and variable declarations.
* **begin**   - Begins a new block of statements to execute.
* **end**     - Closes the block of statements from the last begin statement.
* **nil**     - Zero

###### Loops

* **repeat**  - Begins what is essentially a Do-While loop.
* **until**   - Marks the end of a repeat statement when the following conditional is met.
* **for**     - Declares a for-loop
* **to**      - Used in a for-loop's conditional statement: the initialized value will be incremented to the following value
* **downto**  - Used in a for-loop's conditional statement: the initialized value will be decremented to the following value
* **while**   - Begins a while-loop.
* **do**      - Placed after a for/while loop's conditional statement: identifies the statement (or block of statements) the loop will execute.
* **goto**    - Jumps the program to a provided label number

###### If

* **if**      - Begins an if-statement.
* **then**    - Statement (or block of statements) to execute when the if-statement returns true.

###### Arrays

* **array**   - Declares a new array in the variable declarations.  Array size must also be declared here; integers, subranges, and enums are
accepted.  Multidimensional declarations are also allowed.
* **of**      - Declares the type of values an array will store.

###### Fucntion Calls

* **write()**    - Prints an integer, real number, or a string
* **writeln()**  - Prints an integer, real number, or a string followed by a new line character

**Note:** while the function calls are written to assembly by this compiler, they must be assmebled with *drivers.c* to actually be used.

#### Recognized Operators:

* **\+**    - Addition
* **\-**    - Subtraction
* **\***    - Multiplication
* **/**     - Division
* **<**   - Less than
* **<=**  - Less than or equal
* **=**     - Equal to
* **<>**  - Not equal to
* **>**     - Greater than
* **>=**    - Greater than or equal to
* **:=**    - Assign value
* **^**     - Declare/dereference Pointer
* **\.**    - Get record field


#### Delimiters:

* **;**     - End statement
* **,**     - Pass another value 
* **:**     - Declare variable type or label number
* **(**     - Pass function argument or prioritize operations
* **)**     - Close left parenthesis
* **[**     - For array indexes
* **]**     - Close left bracket
* **\.\.**    - Initialize array subrange
* **\{** or **\(*** - Start comments
* **\}** or **\*\)** - End comments


## Files

* **lexan.l** - **ORIGINAL SOURCE CODE** will be compiled by lex to declare a number of regular expressions, then takes in input to
see what regular expressions the characters being read match.  Then labels the tokens accordingly and writes them out.
* **lexer** - fully compiled lexan.l
* **parser.y** - **ORIGINAL SOURCE CODE** will be compiled by yacc to declare the legal patterns the tokens can be arranged.  Then 
reads from the previously generated token list to see if they match a designated pattern, while attaching the tokens together to 
form a binary tree that will organize how the program will run.  Also declares and remembers variable identifiers, types, sizes 
as well as constant values, labels, etc.
* **parser** - fully compiled lexan.l + parser.y
* **codegen.c** - **ORIGINAL SOURCE CODE**, reads through the binary tree created by the parser and writes out the
apporpriate x86 assembly code while remembering which variables are stored in which registers.
* **compiler** - fully compiled lexan.l + parser.y + codgen.c
* **driver.c** - creates the special functions called by the code generator but not generated by it, to be compiled with cc with the 
assembly code created by the compiler to create the executable program.
* ForCompilingTheCompiler.zip - a compressed folder containing all files necessary to compile the compiler itself.  Does not include,
GNU Make, Lex, Yacc, or CC, which are required to in the makefile.
* ExamplePascal.zip - a small number of Pascal files that can run through all parts of the compiler.
* UnusedFiles.zip - all untouched skeleton code and notes in a single flat directory.  If a file is missing from 
ForCompilingTheCompiler.zip it will be in here.


## Notes


If you want to produce each step of the compiler in action, you can run the following commands.

##### Lexer

To view the token list:

	lexer < [PASCAL_SOURCECODE].pas

##### Parser

To see the variable types, identifiers, constants declared along with the binary tree produced: commented-out statements in the main 
function of parse.y must be restored and recompiled with the files in ForCompilingTheCompiler.zip using

	make parser

and the following command executed.

	parser < [PASCAL_SOURCECODE].pas

##### Assembly Generator

To see the assembly code produced:

	compiler < [PASCAL_SOURCECODE].pas
