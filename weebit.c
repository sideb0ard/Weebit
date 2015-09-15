#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


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
  // takes a "binary number", and pads with leading zeroes 
  char * tmpstring = malloc(33);
  int length = strlen(s);
  if (length <= 32) {
    int padlength = 32 - length;
    for (int i=0; i < padlength; i++) 
    {
      strcat(tmpstring, "0");
    }
    strcat(tmpstring,s);
    strncpy(s, tmpstring, 33);
  }
  free(tmpstring);

}

void chomp(int inum, char boutput[]) 
{
    while (inum) {
      if (inum & 1) {
        strcat(boutput, "1");
      } else {
        strcat(boutput, "0");
      }
      inum >>= 1;
    }

    reverse(boutput);
    pad(boutput);
}

void barf(char *msg) 
{
  printf("BARF! %s", msg);
  exit(1);
}

int notNum(char arg[])
{
  regex_t regex;
  /* Compile regular expression */
  int reti;
  char msgbuf[100];
  reti = regcomp(&regex, "[^0-9]", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }
  /* Execute regular expression */
  reti = regexec(&regex, arg, 0, NULL, 0);
  if (!reti) {
      return 1;  // bad - found numbers
  }
  else if (reti == REG_NOMATCH) {
      return 0;
  }
  else {
      regerror(reti, &regex, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Regex match failed: %s\n", msgbuf);
      exit(1);
  }
}


int main(int argc, char **argv) 
{
  for ( int i = 1; i < argc; i++ ) {

    if (strlen(argv[i]) > 10) 
        barf("INTS mate, fucking INTS ONLY! (i.e. <= 2,147,483,647)\n");

    if (notNum(argv[i])) {
      printf("YOu're a wee jobbie, that wisnae a number: %s\n", argv[i]);
      continue;
    }

    int inum;
    sscanf(argv[i], "%d", &inum); 

    // setup "binary" output string
    char * boutput = malloc(33);
    // boutput[0] = '\0';  // do i need this? works without it as far as i can tell
       
    // do the magic, convert numb to 32bit binary REPREZENT and save in boutput
    chomp(inum, boutput);
    printf("%d 		: %s\n", inum, boutput);

    free(boutput);
  }
}
