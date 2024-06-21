#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msString.c"

void task1(void);
void printBytes(void *ptr, int numBytes);
void task2(int argc, char *argv[]);
long int getFileLength(FILE *fptr);
void task3(void);

int main(int argc, char *argv[]) 
{
	task1();
	task2(argc, argv);
	task3();
	return 0;
}

void task1(void)
{
	printf("\nTask 1\n");
	char arr[] = {10,20,30,145};
	printBytes(arr, 4);
}

void printBytes(void *ptr, int numBytes)
{
	printf("Starting at memory address %p: \n", ptr);
	int i;
	for (i=0; i<numBytes; i++)
	{
		printf("%03d: %4d \n", i+1, *(unsigned char *)ptr);
		ptr++;
	}
}

void task2(int argc, char *argv[])
{
	printf("\nTask 2\n");
	/* trapping for if insufficient arguments are given */
	if (argc<3)
	{
                fprintf(stderr, "Insufficient arguments to main \n");
                exit(1);
        }
	FILE *fptr;
	/* trapping for if opening the file fails */
        if ( (fptr = (fopen(argv[1], "r"))) == NULL )
	{
                fprintf(stderr, "Error when opening Input file: %s \n", argv[1]);
                exit(1);
        }
	long int size = getFileLength(fptr);
	char revStr[size+1];
	/* setting final character to the null terminator */
	revStr[size] = '\0';
	int i = size-1;
	while (i>-1)
	{
		/* getting a character and writing to revStr in reverse order */
		revStr[i] = fgetc(fptr);
		i--;
	}
	fclose(fptr);
	FILE *ofptr;
	/* trapping for if opening the file fails */
        if ((ofptr = fopen(argv[2], "w")) == NULL)
	{
		fprintf(stderr, "Error when opening Output file: %s \n", argv[2]);
		exit(1);
	}
	fputs(revStr, ofptr);
	/* catching any potential write errors */
	if (ferror(ofptr))
	{
		fprintf(stderr, "Error when writing to file \n");
		exit(1);
	}
	printf("Contents of %s reversed and written to: %s \n", argv[1], argv[2]);
	fclose(ofptr);
}

long int getFileLength(FILE *fptr)
{
	fseek(fptr, 0L, SEEK_END);
        long int size = ftell(fptr);
        rewind(fptr);
	return size;
}

void task3(void) 
{
	printf("\nTask 3\n");
	msString ms = msSetString("Hello");
	msString ms2 = msSetString(" World!");
	msString mscopy = NULL;

	/* assigning the result of msGetString to allow freeing */
	char *msPtr = msGetString(ms);
	printf("String |%s| is %ld characters long (%p).\n", msPtr, msLength(ms), ms);
	
	msCopy(&mscopy, ms);
	/* assigning the result of msGetString to allow freeing */
	char *mscopyPtr = msGetString(mscopy);
	printf("Copied string |%s| is %ld characters long (%p).\n", mscopyPtr, msLength(mscopy), mscopy);

	printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
	printf("Compare ms with ms2   : %d\n", msCompare(ms, ms2));
	printf("Compare ms with Hello : %d\n", msCompareString(ms, "Hello"));
	printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
	printf("Compare ms with Hella : %d\n", msCompareString(ms, "Hella"));

	msConcatenate(&mscopy, ms2);
	/* assigning the result of msGetString to allow freeing */
	char *mscopyPtr2 = msGetString(mscopy);
	printf("Concatenated string |%s| is %ld characters long (%p).\n", mscopyPtr2, msLength(mscopy), mscopy);

	/* the next six lines resolve the memory leak mentioned in the specification */
	free(ms);
	free(ms2);
	free(mscopy);
	free(msPtr);
	free(mscopyPtr);
	free(mscopyPtr2);

	printf("\n");
}
