/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: Huijun Bu(041121881) /Kexin Huang(041096567)
* Professors: Paulo Sousa
************************************************************                                     "
*/
/*
		"\t=---------------------------------------=\n",
		"\t|  COMPILERS - ALGONQUIN COLLEGE (S24)  |\n",
		"\t=---------------------------------------=\n",
		"\t    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    \n",
		"\t    @@                             @@    \n",
		"\t    @@       @@@@@@@@@@@@@@@@@@@@  @@    \n",
		"\t    @@       @  @@@@@@@@@@@@@@  @  @@    \n",
		"\t    @@       @  @            @  @  @@    \n",
		"\t    @@       @  @@@@@@@@@@@@@@  @  @@    \n",
		"\t    @@       @  @ @@@@@@@@@@@@@@   @@    \n",
		"\t    @@       @  @   @              @@    \n",
		"\t    @@       @  @@   @             @@    \n",
		"\t    @@       @  @  @  @            @@    \n",
		"\t    @@       @  @    @   @         @@    \n",
		"\t    @@       @  @      @   @       @@    \n",
		"\t    @@       @  @        @   @     @@    \n",
		"\t    @@       @@@@          @@@@@   @@    \n",
		"\t    @@       P O W E R _ R          @@    \n",
		"\t    @@                             @@    \n",
		"\t    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    \n",
		"\t                                         \n",
		"\t[READER SCRIPT .........................]\n",
		"\t                                         \n"
*/
/*
************************************************************
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

 /* TO_DO: Adjust your language (cannot be "Sofia") */

 /* Language name */
#define STR_LANGNAME	"PowerR"

/* Logical constants - adapt for your language */
#define PowerR_TRUE  1
#define PowerR_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/


/* TO_DO: Define your typedefs */
typedef char			PowerR_char;
typedef char*			PowerR_string;
typedef int				PowerR_int;
typedef float			PowerR_numeric;
typedef void			PowerR_void;

typedef unsigned char	PowerR_boln;
typedef unsigned char	PowerR_byte;

typedef long			PowerR_long;
typedef double			PowerR_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER = 'r',
	PGM_SCANNER = 's',
	PGM_PARSER = 'p'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
PowerR_int mainReader(PowerR_int argc, PowerR_string* argv);

/*
TO_DO: Include later mainScaner (A22) and mainParser (A32)
*/
PowerR_void printLogo();

#endif
