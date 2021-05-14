#include <iostream>
#include <chrono>

//
float polynomial (float x, float* poly, int degree) {
  float out = 0.;
  float xtothepowerof = 1.;
  for (int i=0; i<=degree; ++i) {
    out += xtothepowerof*poly[i];
    xtothepowerof *= x;
  }
  return out;
}

void polynomial_expansion (float* poly, int degree,
			   int n, float* array) {

#pragma omp parallel for schedule(runtime)
  for (int i=0; i< n; ++i) {
    array[i] = polynomial (array[i], poly, degree);
  }
}


int main (int argc, char* argv[]) {
  //TODO: add usage
  
  int n = atoi(argv[1]); //TODO: atoi is an unsafe function
  int degree = atoi(argv[2]);
  int nbiter = atoi(argv[3]);

  float* array = new float[n];
  float* poly = new float[degree+1];
  for (int i=0; i<n; ++i)
    array[i] = 1.;

  for (int i=0; i<degree+1; ++i)
    poly[i] = 1.;

  
  std::chrono::time_point<std::chrono::system_clock> begin, end;
  begin = std::chrono::system_clock::now();
  
  for (int iter = 0; iter<nbiter; ++iter)
    polynomial_expansion (poly, degree, n, array);

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> totaltime = (end-begin)/nbiter;

  std::cerr<<array[0]<<std::endl;
  std::cout<<n<<" "<<degree<<" "<<totaltime.count()<<std::endl;

  delete[] array;
  delete[] poly;

  return 0;
}
