#include <cstdlib>
#include <cmath>
#include <stdio.h>

int main (int argc, char* argv[]) {
  if (argc!=3)
	  return 1;

  //float a = atof(argv[1]); //atof is an unsafe function //really should use strtof and check error
  //float b = atof(argv[2]); //atof is an unsafe function

  float a, b;
  
  if (sscanf(argv[1], "%f", &a) != 1)
    return 1;
  if (sscanf(argv[2], "%f", &b) != 1)
    return 1;

  return (fabs(a-b) > .1);  
}
