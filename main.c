#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_VECTOR_SIZE 8009

FILE* openFile(char* fileName, char* type);
int homeHash(const char* s, unsigned int seed);
int incrementHash(const char* s, unsigned int seed);
int storeHash(const char* s, unsigned int seed);
char* readFile(FILE* file);

int main(void)
{
  char *myBuffer, *token;

  FILE *dictionary = openFile("example/arq1.dic", "r");

  myBuffer = readFile(dictionary);
  
  //spliting the string
  token = strtok(myBuffer, "\n");
  
  int *hashVector = (int*) malloc(HASH_VECTOR_SIZE * sizeof(int));
  
  do
  {
    printf("Home %s -- %d\n", token, homeHash(token, 0));
    int hash = homeHash(token, 0);
    
    if(hashVector[hash] == 0)
    {
      printf("Store %s -- %d\n", token, storeHash(token, 0));
      hashVector[hash] = storeHash(token, 0);
    }
    else
    {
      while(hashVector[hash] != 0)
      {
        hash += incrementHash(token, 0);
        printf("Increment -- %d\n", hash);
        if(hashVector[hash] == 0)
        {
          printf("Store %s -- %d\n", token, storeHash(token, 0));
          hashVector[hash] = storeHash(token, 0);
          break;
        }
      } 
    }
    
  } while((token = strtok(NULL, "\n")) != NULL);
  
  int i;
  for(i = 0; i < HASH_VECTOR_SIZE; i++)
  {
    printf("%d - %d\n", i, hashVector[i]);
  }
  
  FILE *text = openFile("example/nome.txt", "r");

  myBuffer = readFile(text);
  
  //spliting the string
  char *line = strtok(myBuffer, "\n");
  int lineCount = 1;
  
  do
  {
    printf("linha - %s\n", line);
    char *word = strtok(NULL, " ");
    
    int hash = homeHash(word, 0);
  
    do
    {
      printf("palavra - %s\n", word);
      if(hashVector[hash] == storeHash(word, 0))
      {
        
      }
    } while((word = strtok(NULL, " ")) != NULL);
    
    lineCount++;
    
  } while((line = strtok(NULL, "\n")) != NULL);
  
  FILE *error = openFile("example/nome.err", "w");

  return 0;
  
}

FILE* openFile(char* fileName, char* type)
{
  FILE* file = fopen(fileName, type);
  
  if(file == NULL)
  {
    printf("File not found.");
    exit(-1);
  }
  
  return file;
}

char* readFile(FILE* file)
{
  char *myBuffer;
  
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
  return myBuffer;
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
