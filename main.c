#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_VECTOR_SIZE 8009

FILE* openFile(char* fileName);

int homeHash(const char* s, unsigned int seed);
int incrementHash(const char* s, unsigned int seed);
int storeHash(const char* s, unsigned int seed);

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
  
  int *hashVector = (int*) malloc(HASH_VECTOR_SIZE * sizeof(int));
  
  do
  {
    printf("Home %s -- %d\n", token, homeHash(token, 0));
    int hash = homeHash(token, 0);
    
    if(hashVector[hash] == NULL)
    {
      printf("Store %s -- %d\n", token, storeHash(token, 0));
      hashVector[hash] = storeHash(token, 0);
    }
    else
    {
      while(hashVector[hash] != NULL)
      {
        hash += incrementHash(token, 0);
        printf("Increment -- %d\n", hash);
        if(hashVector[hash] == NULL)
        {
          printf("Store %s -- %d\n", token, storeHash(token, 0));
          hashVector[hash] = storeHash(token, 0);
          break;
        }
      } 
    }
    
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


int homeHash(const char* s, unsigned int seed)
{
  unsigned hash = seed;
  
  while (*s)
  {
    hash = hash * 101  +  *s++;
  }
  
  return hash % (HASH_VECTOR_SIZE);
}

int incrementHash(const char* s, unsigned int seed)
{
  unsigned hash = seed;
  
  while (*s)
  {
    hash = hash * 103  +  *s++;
  }
  
  return hash % (HASH_VECTOR_SIZE);
}

int storeHash (const char* s,unsigned int seed)
{
  unsigned hash = seed;
  
  while (*s)
  {
    hash = hash * 105  +  *s++;
  }
  
  return hash % (HASH_VECTOR_SIZE);
}
