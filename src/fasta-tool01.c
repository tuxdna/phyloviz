/*
  This program is not used anywhere at the moment.
  Do not bother, it will be removed soon.
 */

#include<stdio.h>
#include<stdlib.h>

int main( int argc, char *argv[]) {
  int numseq;	
  int c;

  if(argc<2) {
    printf("Invalid number of arguments");
    exit(1);
  }

  numseq=atoi(argv[1]);

  //printf("numseq=%d\n",numseq);

  while((c = getchar())!=EOF) {
    if(c=='>') {
      numseq--;
    }
    if(numseq<0)
      break;
    putchar(c);
  }
  exit(1);
}

