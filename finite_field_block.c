#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

#define MAX_q 23 // greatest prime power supported
#define MAX_degree 4 

int Z_addition(int, int, int);
int Z_multiplication(int, int, int);

Design *finite_field_based_design(int value)
{
  int i = 0;
  int flag_primepower = 0;
  int sprime;
  int alpha, beta;
  int new_value;
  Design *bd;
  
  if ((value < 1) ||(value > MAX_q)) {
    fprintf(stderr, "exceed limit\n");
    exit(1);
  }
  
  sprime = smallest_prime_power(value);
  
  if (value == sprime)
    flag_primepower = 1;
  else
    flag_primepower = 0;

  bd = (Design *)malloc(sizeof(Design));
  
  bd->no_pars = sprime + 1;
  bd->size = sprime*sprime;
  if ((bd->range = (int *)calloc(bd->no_pars, sizeof(int))) == NULL)
    return NULL; // memory shortage
  for(i = 0; i < bd->no_pars; i++)
    bd->range[i] = value;

  bd->value = (int *)calloc(bd->no_pars * bd->size, sizeof(int));

  for (alpha = 0; alpha < sprime; alpha++) {
    for (beta = 0; beta < sprime; beta++) {
      for (i = 0; i < sprime; i++) {
        new_value = Z_addition(Z_multiplication(alpha, i, sprime), beta, sprime);
        if (new_value >= value)
          new_value = -1;
        set_value(bd, alpha * sprime + beta, i, new_value);
      }
      new_value = alpha;
      if (new_value >= value)
        new_value = -1;
      set_value(bd, alpha * sprime + beta, sprime, new_value);
    }
  }
  return bd;
}


int Z_multiplication(int x, int y, int q)
{
  int i, tmp, result;
  int prime, prime_power, factor = 0;

  void Index2Coefficient();

  if (q > MAX_q){
    fprintf(stderr,"%d is too large.\n",q);
    exit(-1);
  }

  prime = 1;
  for(i=2; i<q; i++)
    if((q % i) == 0) {
      prime = 0;
      break;
    }
  if(prime == 1) {
    result = (x * y) % q;
    return(result);
  }

  prime_power = 1;
  for(i=2; i<q; i++)
    if((q % i) == 0) {
      factor = i;
      break;
    }
  tmp = q / factor;
  while(tmp != 1)
    if((tmp % factor) == 0)
      tmp = tmp/factor;
    else {
      prime_power = 0;
      break;
    }

  if(prime_power == 0) {
    fprintf(stderr,"%d is not a prime power.\n", q);
    exit(-1);
  }

  if ((x==0)||(y==0))
      return(0);

  result = (((x-1) + (y-1)) % (q-1))+1;
  return(result);
}

int Z_addition(int x, int y, int q)
{
  int i, tmp, result;
  int prime, prime_power, factor = 0;
  int xc[MAX_degree];
  int yc[MAX_degree];
  int zc[MAX_degree];

  void Index2Coefficient();
  int  Coefficient2Index();

  if (q > MAX_q){
    fprintf(stderr,"%d is too large.\n",q);
    exit(-1);
  }

  prime = 1;
  for(i=2; i<q; i++)
    if((q % i) == 0) {
      prime = 0;
      break;
    }
  if(prime == 1) {
    result = (x + y) % q;
    return(result);
  }

  prime_power = 1;
  for(i=2; i<q; i++)
    if((q % i) == 0) {
      factor = i;
      break;
    }
  tmp = q / factor;
  while(tmp != 1)
    if((tmp % factor) == 0)
      tmp = tmp/factor;
    else {
      prime_power = 0;
      break;
    }

  if(prime_power == 0) {
    fprintf(stderr,"%d is not a prime power.\n", q);
    exit(-1);
  }

  Index2Coefficient(q, x-1, &xc[0], &xc[1], &xc[2], &xc[3]);
  Index2Coefficient(q, y-1, &yc[0], &yc[1], &yc[2], &yc[3]);
  for(i=0; i<MAX_degree; i++)
    zc[i] = (xc[i]+yc[i]) % factor;

  result = Coefficient2Index(q, zc[0], zc[1], zc[2], zc[3]);
  result = result +1;
  return(result);
}

void Index2Coefficient(int q, int x, int *c1, int *c2, int *c3, int *c4)
{
  int order, i,j,k;
  int ce[4][MAX_q][MAX_degree]; /* 4 = no_FILEDS */
  int no_FILEDS;

  enum FILED {
    GF4, GF8, GF9, GF16
  };
  no_FILEDS = 4;

  order = -1;
  if (q == 4)
    order = GF4;
  if (q == 8)
    order = GF8;
  if (q == 9)
    order = GF9;
  if (q == 16)
    order = GF16;
  if (order < 0){
    fprintf(stderr,"In Index2Coefficient: Error\n");
    exit(-1);
  }

  if (x < 0) {
    *c1 = *c2 = *c3 = *c4 = 0;
    return;
  }

  for(i=0; i<no_FILEDS; i++)
    for(j=0; j<MAX_q; j++)
      for(k=0; k<MAX_degree; k++)
	ce[i][j][k] = 0;

  ce[GF4][0][0] = 0;  ce[GF4][0][1] = 1;
  ce[GF4][1][0] = 1;  ce[GF4][1][1] = 0;
  ce[GF4][2][0] = 1;  ce[GF4][2][1] = 1;

  ce[GF8][0][0] = 0;  ce[GF8][0][1] = 0;  ce[GF8][0][2] = 1;
  ce[GF8][1][0] = 0;  ce[GF8][1][1] = 1;  ce[GF8][1][2] = 0;
  ce[GF8][2][0] = 1;  ce[GF8][2][1] = 0;  ce[GF8][2][2] = 0;
  ce[GF8][3][0] = 1;  ce[GF8][3][1] = 0;  ce[GF8][3][2] = 1;
  ce[GF8][4][0] = 1;  ce[GF8][4][1] = 1;  ce[GF8][4][2] = 1;
  ce[GF8][5][0] = 0;  ce[GF8][5][1] = 1;  ce[GF8][5][2] = 1;
  ce[GF8][6][0] = 1;  ce[GF8][6][1] = 1;  ce[GF8][6][2] = 0;

  ce[GF9][0][0] = 0;  ce[GF9][0][1] = 1; 
  ce[GF9][1][0] = 1;  ce[GF9][1][1] = 0; 
  ce[GF9][2][0] = 2;  ce[GF9][2][1] = 1; 
  ce[GF9][3][0] = 2;  ce[GF9][3][1] = 2; 
  ce[GF9][4][0] = 0;  ce[GF9][4][1] = 2; 
  ce[GF9][5][0] = 2;  ce[GF9][5][1] = 0; 
  ce[GF9][6][0] = 1;  ce[GF9][6][1] = 2; 
  ce[GF9][7][0] = 1;  ce[GF9][7][1] = 1; 

  ce[GF16][0][0]  = 0;  ce[GF16][0][1]  = 0;  ce[GF16][0][2]  = 0;  ce[GF16][0][3] = 1;
  ce[GF16][1][0]  = 0;  ce[GF16][1][1]  = 0;  ce[GF16][1][2]  = 1;  ce[GF16][1][3] = 0;
  ce[GF16][2][0]  = 0;  ce[GF16][2][1]  = 1;  ce[GF16][2][2]  = 0;  ce[GF16][2][3] = 0;
  ce[GF16][3][0]  = 1;  ce[GF16][3][1]  = 0;  ce[GF16][3][2]  = 0;  ce[GF16][3][3] = 0;
  ce[GF16][4][0]  = 1;  ce[GF16][4][1]  = 0;  ce[GF16][4][2]  = 0;  ce[GF16][4][3] = 1;
  ce[GF16][5][0]  = 1;  ce[GF16][5][1]  = 0;  ce[GF16][5][2]  = 1;  ce[GF16][5][3] = 1;
  ce[GF16][6][0]  = 1;  ce[GF16][6][1]  = 1;  ce[GF16][6][2]  = 1;  ce[GF16][6][3] = 1;
  ce[GF16][7][0]  = 0;  ce[GF16][7][1]  = 1;  ce[GF16][7][2]  = 1;  ce[GF16][7][3] = 1;
  ce[GF16][8][0]  = 1;  ce[GF16][8][1]  = 1;  ce[GF16][8][2]  = 1;  ce[GF16][8][3] = 0;
  ce[GF16][9][0]  = 0;  ce[GF16][9][1]  = 1;  ce[GF16][9][2]  = 0;  ce[GF16][9][3] = 1;
  ce[GF16][10][0] = 1;  ce[GF16][10][1] = 0;  ce[GF16][10][2] = 1;  ce[GF16][10][3] = 0;
  ce[GF16][11][0] = 1;  ce[GF16][11][1] = 1;  ce[GF16][11][2] = 0;  ce[GF16][11][3] = 1;
  ce[GF16][12][0] = 0;  ce[GF16][12][1] = 0;  ce[GF16][12][2] = 1;  ce[GF16][12][3] = 1;
  ce[GF16][13][0] = 0;  ce[GF16][13][1] = 1;  ce[GF16][13][2] = 1;  ce[GF16][13][3] = 0;
  ce[GF16][14][0] = 1;  ce[GF16][14][1] = 1;  ce[GF16][14][2] = 0;  ce[GF16][14][3] = 0;

  *c1 = ce[order][x][0];
  *c2 = ce[order][x][1];
  *c3 = ce[order][x][2];
  *c4 = ce[order][x][3];
  return;
}


int Coefficient2Index(int q, int c1, int c2, int c3, int c4)
{
  int order, i,j,k;
  int ce[4][MAX_q][MAX_degree]; /* 4 = no_FILEDS */
  int no_FILEDS;

  enum FILED {
    GF4, GF8, GF9, GF16
  };
  no_FILEDS = 4;

  order = -1;
  if (q == 4)
    order = GF4;
  if (q == 8)
    order = GF8;
  if (q == 9)
    order = GF9;
  if (q == 16)
    order = GF16;
  if (order < 0){
    fprintf(stderr,"In Coefficient2Index: Error\n");
    exit(-1);
  }

  if((c1==0)&&(c2==0)&&(c3==0)&&(c4==0)) 
    return(-1);

  for(i=0; i<no_FILEDS; i++)
    for(j=0; j<MAX_q; j++)
      for(k=0; k<MAX_degree; k++)
	ce[i][j][k] = 0;

  ce[GF4][0][0] = 0;  ce[GF4][0][1] = 1;
  ce[GF4][1][0] = 1;  ce[GF4][1][1] = 0;
  ce[GF4][2][0] = 1;  ce[GF4][2][1] = 1;

  ce[GF8][0][0] = 0;  ce[GF8][0][1] = 0;  ce[GF8][0][2] = 1;
  ce[GF8][1][0] = 0;  ce[GF8][1][1] = 1;  ce[GF8][1][2] = 0;
  ce[GF8][2][0] = 1;  ce[GF8][2][1] = 0;  ce[GF8][2][2] = 0;
  ce[GF8][3][0] = 1;  ce[GF8][3][1] = 0;  ce[GF8][3][2] = 1;
  ce[GF8][4][0] = 1;  ce[GF8][4][1] = 1;  ce[GF8][4][2] = 1;
  ce[GF8][5][0] = 0;  ce[GF8][5][1] = 1;  ce[GF8][5][2] = 1;
  ce[GF8][6][0] = 1;  ce[GF8][6][1] = 1;  ce[GF8][6][2] = 0;

  ce[GF9][0][0] = 0;  ce[GF9][0][1] = 1; 
  ce[GF9][1][0] = 1;  ce[GF9][1][1] = 0; 
  ce[GF9][2][0] = 2;  ce[GF9][2][1] = 1; 
  ce[GF9][3][0] = 2;  ce[GF9][3][1] = 2; 
  ce[GF9][4][0] = 0;  ce[GF9][4][1] = 2; 
  ce[GF9][5][0] = 2;  ce[GF9][5][1] = 0; 
  ce[GF9][6][0] = 1;  ce[GF9][6][1] = 2; 
  ce[GF9][7][0] = 1;  ce[GF9][7][1] = 1; 

  ce[GF16][0][0]  = 0;  ce[GF16][0][1]  = 0;  ce[GF16][0][2]  = 0;  ce[GF16][0][3] = 1;
  ce[GF16][1][0]  = 0;  ce[GF16][1][1]  = 0;  ce[GF16][1][2]  = 1;  ce[GF16][1][3] = 0;
  ce[GF16][2][0]  = 0;  ce[GF16][2][1]  = 1;  ce[GF16][2][2]  = 0;  ce[GF16][2][3] = 0;
  ce[GF16][3][0]  = 1;  ce[GF16][3][1]  = 0;  ce[GF16][3][2]  = 0;  ce[GF16][3][3] = 0;
  ce[GF16][4][0]  = 1;  ce[GF16][4][1]  = 0;  ce[GF16][4][2]  = 0;  ce[GF16][4][3] = 1;
  ce[GF16][5][0]  = 1;  ce[GF16][5][1]  = 0;  ce[GF16][5][2]  = 1;  ce[GF16][5][3] = 1;
  ce[GF16][6][0]  = 1;  ce[GF16][6][1]  = 1;  ce[GF16][6][2]  = 1;  ce[GF16][6][3] = 1;
  ce[GF16][7][0]  = 0;  ce[GF16][7][1]  = 1;  ce[GF16][7][2]  = 1;  ce[GF16][7][3] = 1;
  ce[GF16][8][0]  = 1;  ce[GF16][8][1]  = 1;  ce[GF16][8][2]  = 1;  ce[GF16][8][3] = 0;
  ce[GF16][9][0]  = 0;  ce[GF16][9][1]  = 1;  ce[GF16][9][2]  = 0;  ce[GF16][9][3] = 1;
  ce[GF16][10][0] = 1;  ce[GF16][10][1] = 0;  ce[GF16][10][2] = 1;  ce[GF16][10][3] = 0;
  ce[GF16][11][0] = 1;  ce[GF16][11][1] = 1;  ce[GF16][11][2] = 0;  ce[GF16][11][3] = 1;
  ce[GF16][12][0] = 0;  ce[GF16][12][1] = 0;  ce[GF16][12][2] = 1;  ce[GF16][12][3] = 1;
  ce[GF16][13][0] = 0;  ce[GF16][13][1] = 1;  ce[GF16][13][2] = 1;  ce[GF16][13][3] = 0;
  ce[GF16][14][0] = 1;  ce[GF16][14][1] = 1;  ce[GF16][14][2] = 0;  ce[GF16][14][3] = 0;

  for(i=0;i<MAX_q;i++)
    if((ce[order][i][0]==c1)&&(ce[order][i][1]==c2)&&
       (ce[order][i][2]==c3)&&(ce[order][i][3]==c4))
      return(i);

  fprintf(stderr,"In Coefficient2Index: Error\n");
  exit(-1);
}
