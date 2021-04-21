#include <cstdlib>
#include <cmath>

int main (int argc, char* argv[]) {
  if (argc!=3)
	  return 1;
  float a = atof(argv[1]); //atof is an unsafe function //really should use strtof and check error
  float b = atof(argv[2]); //atof is an unsafe function

  return (fabs(a-b) > .1);  
}
