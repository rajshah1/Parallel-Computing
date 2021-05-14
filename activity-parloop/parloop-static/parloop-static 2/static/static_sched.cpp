#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include <vector>
#include "seq_loop.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

  float f1(float x, int intensity);
  float f2(float x, int intensity);
  float f3(float x, int intensity);
  float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

float calInteFunction(float functionId, float a, float b, int n, int intensity, int nbthreads)
{
  SeqLoop sl(n, nbthreads);

  float lub_avg = (float)(b - a) / n;
  float fResponseSum = 0;
  std::vector<float> fResponseSumVec;
  sl.parfor<float>(
      0, n, 1,
      [&](float &tls) -> void {
        tls = 0;
      },
      [&](int i, float &tls) -> void {
        float secondTerm = a + ((i + 0.5) * lub_avg);

        switch ((int)functionId)
        {
        case 1:
          tls += f1(secondTerm, intensity);
          break;
        case 2:
          tls += f2(secondTerm, intensity);
          break;
        case 3:
          tls += f3(secondTerm, intensity);
          break;
        case 4:
          tls += f4(secondTerm, intensity);
          break;
        }
      },
      [&](float &tls) -> void {
        fResponseSum += tls;
      });

  return (lub_avg * fResponseSum);
}

int main(int argc, char *argv[])
{

  if (argc < 7)
  {
    std::cerr << "usage: " << argv[0] << " <functionid> <a> <b> <n> <intensity> <nbthreads>" << std::endl;
    return -1;
  }
  float functionId = strtof(argv[1], NULL);
  float a = strtof(argv[2], NULL);
  float b = strtof(argv[3], NULL);
  int n = strtof(argv[4], NULL);
  ;
  int intensity = strtof(argv[5], NULL);
  int nbthreads = strtof(argv[6], NULL);

  auto start = std::chrono::steady_clock::now();

  float Final_response = (float)calInteFunction(functionId, a, b, n, intensity, nbthreads);

  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> difference = stop - start;

  std::cout << Final_response << std::endl;
  std::cerr << difference.count() << std::endl;
  return 0;
}
