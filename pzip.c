#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *pzip(void *arg);

int main(int argc, char *argv[]) {
  pthread_t threads[argc];
  int i, rc;

  // not enough input arguments
  if (argc < 2) {
    return 0;
  }

  // spawn threads
  for (i = 0; i < argc-1; i++) {
    if ((rc = pthread_create(&threads[i], NULL, pzip, argv[i+1])) != 0) {
      perror("Error on creating thread.\n");
      exit(1);
    }
  }

  // wait for threads to finish
  for (i = 0; i < argc-1; i++) {
    if ((rc = pthread_join(threads[i], NULL)) != 0) {
      perror("Error on joining thread.\n");
      exit(1);
    }
  }

  return 0;
}

void *pzip(void *arg) {
  FILE *fp;
  int c, p, counter;
  // p is the character to be counted
  p = 0;
  // counter is amount of characters
  counter = 1;

  fp = fopen(arg, "r");

  // failed to open file
  if (fp == NULL) {
    printf("pzip: cannot open file\n");
    exit(1);
  }

  while ((c = getc(fp)) != EOF) {
    // if p == 0, c is the first character of file, so just set p = c
    if (p != 0) {
      if (p == c) { // increase counter is character to be counted (p) is the same as character read (c)
        counter += 1;
      } else { // write counter as 4 byte integer in binary format to stdout, followed by the character to be counted
        fwrite(&counter, 4, 1, stdout);
        printf("%c", p);
        counter = 1;
      }
    }

    // set p = c, so the next character to be read (c on next iteration) can be compared to previous one (p)
    p = c;
  }

  fclose(fp);

  return NULL;
}
