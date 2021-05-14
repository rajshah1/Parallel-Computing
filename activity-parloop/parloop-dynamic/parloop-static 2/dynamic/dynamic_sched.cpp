#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "seq_loop.hpp"

#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

float charToFloat(char* str){
  char *remaining;
  float number = strtof(str, &remaining);
  if (str == remaining){
    std::cerr<<"Non numeric character in input!"<<std::endl;
    exit(0);
  } 
  return number;
}

float calculateIntegral(float functionId, float a, float b, int n, int intensity, int nbthreads, int granularity){
  SeqLoop sl(n, nbthreads, granularity);

  float firstPartOfEquation = (float)(b-a)/n;
  float functionResponse = 0;
  std::vector<float> functionResponseVec;
  sl.parfor<float>(0, n, 1, 
    [&](float& tls) -> void{
		   tls = 0;
		},
		[&](int i, float& tls) -> void{
		   float secondPartOfEquation = a + ((i + 0.5) * firstPartOfEquation);

       switch ((int) functionId){
        case 1:
          tls += f1(secondPartOfEquation,intensity);
          break;
        case 2:
          tls += f2(secondPartOfEquation,intensity);
          break;
        case 3:
          tls += f3(secondPartOfEquation,intensity);
          break;
        case 4:
          tls += f4(secondPartOfEquation,intensity);
          break;
        default:
          std::cerr<<"Function ID is incorrect."<<std::endl;
          exit(0);
        }
		  },
		 [&](float &tls) -> void{
      functionResponse += tls;
		 }
  );
  
  return (firstPartOfEquation*functionResponse);
}

int main (int argc, char* argv[]) {

  if (argc < 8) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads> <granularity>"<<std::endl;
    return -1;
  }
  float functionId = charToFloat(argv[1]);;
  float a = charToFloat(argv[2]);
  float b = charToFloat(argv[3]);
  int n = charToFloat(argv[4]);
  int intensity = charToFloat(argv[5]);
  int nbthreads = charToFloat(argv[6]);
  int granularity = charToFloat(argv[7]);

  auto start =std::chrono::steady_clock::now();

  float response = (float) calculateIntegral(functionId, a, b, n, intensity, nbthreads, granularity);
  
   auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> difference = stop-start;

  std::cout<< response<<std::endl;
  std::cerr << difference.count() << std::endl;

  return 0;
}
