#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HASH_VECTOR_SIZE 2003

FILE* openFile(char* fileName, char* type);
int homeHash(const char* s, unsigned int seed);
int incrementHash(const char* s, unsigned int seed);
int storeHash(const char* s, unsigned int seed);
char* readFile(FILE* file);
void readDictionary(int *hashVector);
void printHashVector(int *hashVector);
int sumCharacters(const char *string);

int main(void)
{
  char *myBuffer;
  int *hashVector = (int*) malloc(HASH_VECTOR_SIZE * sizeof(int));
  
  readDictionary(hashVector);
  
  printHashVector(hashVector);
  
  FILE *text = openFile("example/nome.txt", "r");
  FILE *error = openFile("example/nome.err", "w");

  myBuffer = readFile(text);
  
  //spliting the string
  char *line = strtok(myBuffer, "\n");
  int lineCount = 1;
  
  /*do
  {
    //printf("Tamanho - %d\n", (int) strlen(line));
    //FILE *lineStream = fmemopen(line, strlen(line), "r");
    
    printf("linha - %s\n", line);
    //char *word = NULL;
    */
    do
    {
      //fscanf(lineStream, "%s", word);
      //printf("palavra - %s\n", word);
      
      int hash = homeHash(line, 0);
      
      printf("%d - %d\n", hash, hashVector[hash]);
      if(hashVector[hash] == 0)
      {
        fprintf(error, "%d - %s\n", lineCount, line);
      }
      else if(hashVector[hash] != storeHash(line, 0))
      {
        int found = 0;
        while(hashVector[hash] != 0)
        {
          printf("%d - %d\n", hash, hashVector[hash]);
          hash += incrementHash(line, 0);
          printf("Increment -- %d\n", hash);
          
          if(hashVector[hash] == storeHash(line, 0))
          {
            found = 1;
            break;
          }
          
          hash += incrementHash(line, 0);
        }
        if(!found)
        {
          fprintf(error, "%d - %s\n", lineCount, line);
        }
      }
      
      lineCount++;
    } while((line = strtok(NULL, "\n")) != NULL);
    
    //lineCount++;
    
  //} while((line = strtok(NULL, "\n")) != NULL);

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
  return sumCharacters(s) % HASH_VECTOR_SIZE;
}

int incrementHash(const char* s, unsigned int seed)
{
  
  return abs(sumCharacters(s) / HASH_VECTOR_SIZE) % HASH_VECTOR_SIZE;
}

int storeHash (const char* s,unsigned int seed)
{
  return (sumCharacters(s) % HASH_VECTOR_SIZE - 4) + 1;
}

int sumCharacters(const char *string)
{
  int i = 0, sum = 0;
  while(string[i] != '\0')
  {
    sum += string[i];
    i++;
  }
  
  return abs(sum);
}

void printHashVector(int *hashVector)
{
  int i;
  for(i = 0; i < HASH_VECTOR_SIZE; i++)
  {
    printf("%d - %d\n", i, hashVector[i]);
  }
}

void readDictionary(int *hashVector)
{
  char *myBuffer, *token;
  FILE *dictionary;
  
  dictionary = openFile("example/arq1.dic", "r");

  myBuffer = readFile(dictionary);
  
  //spliting the string
  token = strtok(myBuffer, "\n");
  
  do
  {
    int hash = homeHash(token, 0);
    
    if(hashVector[hash] == 0)
    {
      hashVector[hash] = storeHash(token, 0);
    }
    else if(hashVector[hash] == storeHash(token, 0))
    {
      printf("Reapeated - %s\n", token);
      continue;
    }
    else
    {
      printf("colision detected \n");
      while(hashVector[hash] != 0)
      {
        hash += incrementHash(token, 0);
        if(hashVector[hash] == 0)
        {
          hashVector[hash] = storeHash(token, 0);
          break;
        }
      } 
    }
    
    printf("%d -> %d - %s\n", hash, storeHash(token, 0), token);
  } while((token = strtok(NULL, "\n")) != NULL);
}
