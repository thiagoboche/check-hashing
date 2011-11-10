#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *myBuffer, *token;
  const char delimiters[] = "\n";

	FILE *f = openFile();

	/*Quick way of finding the file size--move the pointer to the end
	of the file, get the position add one, and then voilá! The file size!
	You have to add another byte to hold the terminating NULL.*/
	fseek(f,0,SEEK_END);
	unsigned long fileSize = ftell(f);
	fileSize += 2;

	
	//reposition the file pointer to the beginning for reading
	fseek(f,0,SEEK_SET);

	//allocate the pointer
	myBuffer = (char *)malloc(fileSize * sizeof(char));
	if(myBuffer == NULL)
	{
		printf("Out of memory.");
		exit(-2);
	}

	//notice that since this is a pointer, no ampersand (&) is used.
	//fread(myBuffer,sizeof(myBuffer),1,f);
	fread(myBuffer,fileSize,1,f);
	fclose(f);
  
  //spliting the string
  token = strtok(myBuffer, delimiters);
  while((token = strtok(NULL, delimiters)) != NULL)
  {
    
  }

	return 0;
	
}

FILE* openFile()
{
  FILE* file = fopen("arq1.dic","r");
  
	if(file == NULL)
	{
		printf("File not found.");
		exit(-1);
	}
  
  return file;
}
