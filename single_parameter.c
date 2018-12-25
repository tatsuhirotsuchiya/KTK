#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

Design *single_parameter(int value)
{
  int i = 0;
  Design *bd;

  bd = (Design *)malloc(sizeof(Design));
  bd->no_pars = 1; bd->size = value;
  bd->range = (int *)calloc(1, sizeof(int));
  *bd->range = value;
  bd->value =(int *)calloc(value, sizeof(int));
  for(i = 0; i< value; i++)
    *(bd->value + i) = i;
  return bd;
}
