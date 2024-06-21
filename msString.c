#include "msString.h"

msString msSetString(char *str)
{
        long int len = strlen(str);
        msString newMsString = malloc(sizeof(long int) + len*sizeof(char));
        /* trapping for a memory allocation failure */
	if ( newMsString == NULL )
	{
                msError("Memory allocation failed for msSetString \n");
        }
	/* performing memory copy operations to place information into memory */
        memcpy(newMsString, &len, sizeof(long int));
        memcpy((char *)newMsString+sizeof(long int), str, len);
        return newMsString;
}

char* msGetString(msString msStr)
{
        long int len = msLength(msStr);
        char *str = malloc(len*sizeof(char)+1);
	/* trapping for a memory allocation failure */
        if ( str == NULL )
	{
                msError("Memory allocation failed for msGetString \n");
        }
        long int i;
	/* iteration through memory to get all the characters */
        for (i=0; i<len; i++)
	{
                str[i] = *(char *)(msStr+sizeof(long int)+i);
        }
	/* putting the final character to be the null terminator */
        str[len] = '\0';
        return str;
}

void msCopy(msString *destPtr, msString src)
{
	long int srcLen = msLength(src);
	/* trapping for a NULL pointer and trapping for allocation failure */
	if (*destPtr == NULL)
	{
		*destPtr = malloc(sizeof(long int) + srcLen);
		if (*destPtr == NULL)
		{
			msError("Memory allocation failed for msCopy \n");
		}
	}
	/* memory copy operations to copy the source to destination */
	memcpy(*destPtr, &srcLen, sizeof(long int));
	memcpy((char *)*destPtr + sizeof(long int), (char *)src + sizeof(long int), srcLen);
}

void msConcatenate(msString *destPtr, msString src)
{
	/* using the built in strcat method from sting.h for efficiency */
        char *str1 = msGetString(*destPtr);
	char *str2 = msGetString(src);
	strcat(str1, str2);
	msString both = msSetString(str1);
	msCopy(destPtr, both);
	/* freeing any memory allocated */
	free(str1);
	free(str2);
	free(both);
}

long int msLength(msString msStr)
{
	/* casting the pointer to long int and returning it's value to extract length */
        return *(long int *)msStr;
}

int msCompare(msString msStr1, msString msStr2)
{
	/* length comparison as a prerequisite for equality */
        long int len1 = msLength(msStr1);
        long int len2 = msLength(msStr2);
        if (!(len1==len2))
	{
                return 1;
        }
        long int i;
	/* iterating through and comparing character by character */
        for (i=0; i<len1; i++)
	{
                if (!( *(char *)(msStr1+sizeof(long int)+i) == *(char *)(msStr2+sizeof(long int)+i) ))
		{
                        return 1;
                }
        }
        return 0;
}

int msCompareString(msString msStr, char* str)
{
	/* assigning the string to an msString then using the prewritten msCompare for efficiency */
        msString msStr2 = msSetString(str);
        short int out = msCompare(msStr, msStr2);
        free(msStr2);
        return out;
}

void msError(char* errStr)
{
	/* writing the message to stderr then flushing and exiting */
        fprintf(stderr, "%s", errStr);
	fflush(stdout);
        exit(1);
}
