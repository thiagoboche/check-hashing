#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* fileName);

int hash (const char* s, unsigned int seed);


int main(void)
{
	char *myBuffer, *token;
  const char delimiters[] = "\n";

	FILE *file = openFile("arq1.dic");

	/*Quick way of finding the file size--move the pointer to the end
	of the file, get the position add one, and then voilá! The file size!
	You have to add another byte to hold the terminating NULL.*/
	fseek(file, 0, SEEK_END);
	unsigned long fileSize = ftell(file);
	fileSize += 2;

	//reposition the file pointer to the beginning for reading
	fseek(file, 0, SEEK_SET);

	//allocate the pointer
	myBuffer = (char *) malloc(fileSize * sizeof(char));
	if(myBuffer == NULL)
	{
		printf("Out of memory.");
		exit(-2);
	}

	//notice that since this is a pointer, no ampersand (&) is used.
	//fread(myBuffer,sizeof(myBuffer),1,f);
	fread(myBuffer, fileSize, 1, file);
	fclose(file);
  
  //spliting the string
  token = strtok(myBuffer, delimiters);
  
  do
  {
    printf("%s -- %d\n", token, hash(token,0));
  } while((token = strtok(NULL, delimiters)) != NULL);

	return 0;
	
}

FILE* openFile(char* fileName)
{
  FILE* file = fopen(fileName, "r");
  
	if(file == NULL)
	{
		printf("File not found.");
		exit(-1);
	}
  
  return file;
}


int hash (
    const char* s,
    unsigned int seed)

{
    unsigned hash = seed;
    while (*s)
    {
        hash = hash * 101  +  *s++;
//        printf("hash - %d\n", hash);
    }
    return hash % (8000);
}
