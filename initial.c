#include <stdio.h>
#include <stdlib.h>

struct parameter_value {
  int value;
  int number;
};

extern int no_parameters;
extern struct parameter_value parameter[100];

void get_initial_data(int argc, char *argv[])
{
  char *prog = argv[0];
  int i = 0;
  int get_two_values(char *, struct parameter_value *);
  
  if (argc < 2) {
    fprintf(stderr,
            "usage: %s value1xnumber1 value2xnumber2 ...\n", prog);
    exit(1);
  }

  while (--argc > 0) {
    if (!get_two_values(*++argv, &parameter[i++])) {
      fprintf(stderr, "can't obtain parameter values\n");
      exit(2);
    }
  }

  no_parameters = i;
}

int get_two_values(char *str, struct parameter_value *par)
{
  char *start;

  start = str;
  while(*start != '\0') {
    if (*start == 'x')
      *start = ' '; 
    start++;
  }


  sscanf(str, "%d %d", &(par->value), &(par->number));
  if (!((1 < par->value) && (par->value <= 100) &&
       (0 < par->number) && (par->number <= 100)))
    return 0; // failed
  else
    return 1;
}
