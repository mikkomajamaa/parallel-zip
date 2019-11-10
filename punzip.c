#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *punzip(void *arg);

int main(int argc, char *argv[]) {
  pthread_t threads[argc];
  int i, rc;

  // spawn threads
  for (i = 0; i < argc-1; i++) {
    if ((rc = pthread_create(&threads[i], NULL, punzip, argv[i+1])) != 0) {
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

void *punzip(void *arg) {
  FILE *fp;
  int j, k, p, counter;
  int *c = malloc(sizeof(int));

  fp = fopen(arg, "r");

  // failed to open file
  if (fp == NULL) {
    printf("punzip: cannot open file\n");
    exit(1);
  }

  // get count of first character
  fread(c, 4, 1, fp);

  while ((k = getc(fp)) != EOF) {
    // print as many characters as c indicates
    for (j = 0; j < *c; j++) {
      putchar(k);
    }
    // read amount of next character
    fread(c, 4, 1, fp);
  }

  fclose(fp);

  return NULL;
}
