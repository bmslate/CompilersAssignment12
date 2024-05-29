/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: Huijun Bu(041121881) /Kexin Huang(041096567)
* Professors: Paulo Sousa                                         "
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define POWER_R_READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define POWER_R_READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define POWER_R_READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */


#define READER_END_FLAG 0x08/* TO_DO: BIT 3: END = End of buffer flag */
#define READER_REL_FLAG 0x04/* TO_DO: BIT 2: REL = Rellocation memory flag */
#define READER_EMP_FLAG 0x02/* TO_DO: BIT 1: EMP = Buffer empty flag */
#define READER_FUL_FLAG 0X01/* TO_DO: BIT 0: FUL = Buffer full flag */


#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME () .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	PowerR_int mark;			/* the offset to the mark position (in chars) */
	PowerR_int read;			/* the offset to the get a char position (in chars) */
	PowerR_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	PowerR_string	content;			/* pointer to the beginning of character array (character buffer) */
	PowerR_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	PowerR_int		increment;			/* character array increment factor */
	PowerR_int		mode;				/* operational mode indicator */
	PowerR_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	PowerR_int		histogram[NCHAR];	/* Statistics of chars */
	PowerR_int		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(PowerR_int, PowerR_int, PowerR_int);
BufferPointer	readerAddChar		(BufferPointer const, PowerR_char);
PowerR_boln		readerClear		    (BufferPointer const);
PowerR_boln		readerFree		    (BufferPointer const);
PowerR_boln		readerIsFull		(BufferPointer const);
PowerR_boln		readerIsEmpty		(BufferPointer const);
PowerR_boln		readerSetMark		(BufferPointer const, PowerR_int);
PowerR_int		readerPrint		    (BufferPointer const);
PowerR_int		readerLoad			(BufferPointer const, FILE* const);
PowerR_boln		readerRecover		(BufferPointer const);
PowerR_boln		readerRetract		(BufferPointer const);
PowerR_boln		readerRestore		(BufferPointer const);
PowerR_void		readerChecksum		(BufferPointer const);
/* Getters */
PowerR_char		readerGetChar		(BufferPointer const);
PowerR_string	readerGetContent	(BufferPointer const, PowerR_int);
PowerR_int		readerGetPosRead	(BufferPointer const);
PowerR_int		readerGetPosWrte	(BufferPointer const);
PowerR_int		readerGetPosMark	(BufferPointer const);
PowerR_int		readerGetSize		(BufferPointer const);
PowerR_int		readerGetInc		(BufferPointer const);
PowerR_int		readerGetMode		(BufferPointer const);
PowerR_byte		readerGetFlags		(BufferPointer const);
PowerR_void		readerPrintStat		(BufferPointer const);
PowerR_int		readerNumErrors		(BufferPointer const);

#endif
