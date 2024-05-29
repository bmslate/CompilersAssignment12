/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: Huijun Bu /Kexin Huang
* Professors: Paulo Sousa
************************************************************                                         "
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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer readerCreate(PowerR_int size, PowerR_int increment, PowerR_int mode) {
	BufferPointer readerPointer;
	/* TO_DO: Defensive programming */
	if ((size < 0) || (increment < 0))
		return NULL;
	/* TO_DO: Adjust the values according to parameters */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return NULL;
	readerPointer->content = (PowerR_string)malloc(size);
	/* TO_DO: Defensive programming */
	if (!readerPointer->content) {
		free(readerPointer);
		return NULL;
	}
	/* TO_DO: Initialize the histogram */
	PowerR_int i;
	for (i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}

	if (size != 0)
		readerPointer->size = size;
	else
		readerPointer->size = POWER_R_READER_DEFAULT_SIZE;
	if (increment!= 0)
		readerPointer->increment = increment;
	else
		readerPointer->increment = POWER_R_READER_DEFAULT_INCREMENT;
	if (mode == MODE_ADDIT || mode == MODE_FIXED || mode == MODE_MULTI)
		readerPointer->mode = mode;
	else
		readerPointer->increment = MODE_FIXED;
	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/*Initialize numReaderErrors*/
	readerPointer->numReaderErrors = 0;
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags |= READER_EMP_FLAG;
	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, PowerR_char ch) {
	PowerR_string tempReader = NULL;
	PowerR_int newSize = 0;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL)
		return NULL;
	if ((ch < 0) || ch > NCHAR) {
		readerPointer->numReaderErrors++;
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= ~READER_REL_FLAG;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (PowerR_int)sizeof(PowerR_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags &= ~READER_FUL_FLAG;
		
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags |= READER_FUL_FLAG;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT: 
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = (PowerR_string)realloc(readerPointer->content, newSize);
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		
		/* TO_DO: Defensive programming */
		if (!tempReader) {
			return NULL;
		}
		/* TO_DO: Check Relocation */
		readerPointer->flags |= READER_REL_FLAG;/*Not sure about this*/
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[(unsigned)ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: 
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return PowerR_FALSE;
	}
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->flags |= READER_EMP_FLAG;
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	return PowerR_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions  
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return PowerR_FALSE;
	}

	if (readerPointer->content != NULL) {
		free(readerPointer->content);
		readerPointer -> content = NULL;/*SET POINTER TO NULL*/
	}
	free(readerPointer);
		//readerPointer = NULL;/*SET POINTER TO NULL*/

	/* TO_DO: Free pointers */
	return PowerR_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return PowerR_FALSE;
	}
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags & READER_FUL_FLAG) {
		return PowerR_TRUE;
	}
	return PowerR_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return PowerR_FALSE;
	}
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags & READER_EMP_FLAG) {
		return PowerR_TRUE;
	}
	return PowerR_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerSetMark(BufferPointer const readerPointer, PowerR_int mark) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return PowerR_FALSE;
	}
	/*check mark*/
	if (mark < 0 || mark > readerPointer->position.wrte) {
		return PowerR_FALSE;
	}
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return PowerR_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerPrint(BufferPointer const readerPointer) {
	PowerR_int cont = 0;
	PowerR_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}

	while (cont < readerPointer->position.wrte && !(readerPointer->flags & READER_END_FLAG)) {
		c = readerGetChar(readerPointer);
		if ( c > 126) {
			printf("Invalid character %d...\n",(unsigned char)c);
			return READER_ERROR;
		}
		cont++;
		printf("%c", c);
				
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	PowerR_int size = 0;
	PowerR_char c;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	if (fileDescriptor == NULL) {
		printf("File descriptor is not initialized\n");
		return READER_ERROR;
	}
	c = (PowerR_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {

		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	if (size > readerPointer->size) {//not sure
		printf("file size is over reader size");
		return READER_ERROR;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0;
	return PowerR_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	if (readerPointer->position.read == 0) {
		printf("Position at the beginning of the reader");
		return PowerR_FALSE;
	}
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;
	return PowerR_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	if (readerPointer->position.read == 0) {
		printf("Position at the beginning of the reader");
		return PowerR_FALSE;
	}
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return PowerR_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return READER_TERMINATOR;
	}
	/* TO_DO: Check condition to read/wrte */
	
	if (readerPointer->position.read < readerPointer->position.wrte) {	
		/* TO_DO: Reset EOB flag */
		readerPointer->flags &= ~READER_END_FLAG;
		return readerPointer->content[readerPointer->position.read++];/*read the character and increment the read offset by 1*/
	}
	else {
		/* TO_DO: Set EOB flag */
		readerPointer->flags |= READER_END_FLAG;
		return READER_TERMINATOR;

	}
		
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_string readerGetContent(BufferPointer const readerPointer, PowerR_int pos) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return NULL;
	}
	if ((pos < 0) || (pos >= readerPointer->position.wrte)) {
		printf("Parameter out of reader boundary");
		return NULL;
	}
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
	
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_byte readerGetFlags(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return;
	}
	/* TO_DO: Print the histogram */
	PowerR_int i;
	printf("Statistics of chars:\n ");
	for (i = 0; i < NCHAR; i++) {
		printf("Character %c: %d \n",i,readerPointer->histogram[i]);
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
PowerR_int readerNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return READER_ERROR;
	}
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}

/*
***********************************************************
* Function name: readerChecksum
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

PowerR_void readerChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		printf("reader is not initialized\n");
		return;
	}
	/* TO_DO: Adjust the checksum to flags */
	PowerR_byte checkSum = 0;
	PowerR_int i;
	for (i = 0; i < readerPointer->position.wrte;i++) {
		checkSum += (PowerR_byte)readerPointer->content[i];
	}
	checkSum &= 0xF0;
	readerPointer->flags |= checkSum;
}
