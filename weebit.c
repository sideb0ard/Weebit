#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[])
{
  int length = strlen(s);
  int c, i, j;
  for (i=0, j = length -1; i < j ; i++, j--) 
  {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void pad(char s[]) 
{
  char * tmpstring = malloc(33);
  int length = strlen(s);
  if (length < 32) {
    int padlength = 32 - length;
    for (int i=0; i < padlength; i++) 
    {
      tmpstring[i] = '0';
    }
    strcat(tmpstring,s);
    strncpy(s, tmpstring, 33);
  }

}

void chomp(int inum, char boutput[]) 
{
    // this is working from least significant bit,
    // so the string will be in reverse
    while (inum) {
      if (inum & 1) {
        strcat(boutput, "1");
      } else {
        strcat(boutput, "0");
      }
      inum >>= 1;
    }

    reverse(boutput);
    // printf("%s\n", boutput);
    pad(boutput);
}

int main(int argc, char **argv) 
{
  for ( int i = 1; i < argc; i++ ) {

    // interpret argv's as number
    int inum;
    sscanf(argv[i], "%d", &inum); 

    // setup "binary" output string
    char * boutput = malloc(33);
    boutput[0] = '\0';
       
    chomp(inum, boutput);
    printf("%2s : %s\n", argv[i], boutput);
  }
}
