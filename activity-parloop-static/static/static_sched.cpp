#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>


#include "./static_parloop.hpp"

using namespace std;

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

struct my_struct
{
  float sum;
  int ub, lb, function_id, intensity;
  float a, b, mid;
};

float total_sum = 0;

void *numerical_integration(void *p)
{

  my_struct *struct_info = (my_struct *)p;

  switch (struct_info->function_id)
  {
  case 1:
    for (int i = struct_info->lb; i <= struct_info->ub; i++)
    {
      float x = (struct_info->a + (i + 0.5) * struct_info->mid);
      struct_info->sum += f1(x, struct_info->intensity);
    }
    break;

  case 2:
    for (int i = struct_info->lb; i <= struct_info->ub; i++)
    {
      float x = (struct_info->a + (i + 0.5) * struct_info->mid);
      struct_info->sum += f2(x, struct_info->intensity);
    }
    break;

  case 3:
    for (int i = struct_info->lb; i <= struct_info->ub; i++)
    {
      float x = (struct_info->a + (i + 0.5) * struct_info->mid);
      struct_info->sum += f3(x, struct_info->intensity);
    }
    break;

  case 4:
    for (int i = struct_info->lb; i <= struct_info->ub; i++)
    {
      float x = (struct_info->a + (i + 0.5) * struct_info->mid);
      struct_info->sum += f4(x, struct_info->intensity);
    }
    break;
  }


  return NULL;
}

int main(int argc, char *argv[])
{

  if (argc < 7)
  {
    std::cerr << "usage: " << argv[0] << " <functionid> <a> <b> <n> <intensity> <nbthreads>" << std::endl;
    return -1;
  }
  int function_id, a, b, n, intensity, nbthreads;
  float x, current_fun_value = 0, current_fun_value_sum = 0, lower_upper_bound_sub, lubs_avg;
  int current_pass_value;

  function_id = strtof(argv[1], NULL);
  a = strtof(argv[2], NULL);
  b = strtof(argv[3], NULL);
  n = strtof(argv[4], NULL);
  intensity = strtof(argv[5], NULL);
  nbthreads = strtof(argv[6], NULL);

  lower_upper_bound_sub = b - a;

  lubs_avg = lower_upper_bound_sub / n;

  SeqLoop l1;

  float sum[nbthreads];
  int computations = n / nbthreads;
  struct my_struct struct_info[nbthreads];
  pthread_t thread[nbthreads];

  auto start_time = chrono::system_clock::now();

  /*
  l1.parfor<float>(
      0, n , 1,
      [&](float &tls) -> void {
        tls = 0;
      },
      [&](int i, float &tls) -> void {
        x = a + ((i + 0.5) * lubs_avg);
        switch (function_id)
        {
        case 1:
          tls += f1(x, intensity);
          break;
        case 2:
          tls += f2(x, intensity);
          break;
        case 3:
          tls += f3(x, intensity);
          break;
        case 4:
          tls += f4(x, intensity);
          break;
        }
      },
      [&](float& tls) -> void {
        current_fun_value_sum += tls;
      });
  std::cout << current_fun_value_sum * lubs_avg;
*/
  int j = 0;

  for (int i = 0; i < nbthreads; i++)
  {
    if (j < n)
    {
      struct_info[i].a = a;

      struct_info[i].b = b;
      struct_info[i].function_id = function_id;
      struct_info[i].intensity = intensity;
      struct_info[i].mid = lubs_avg;
      struct_info[i].lb = j;
      struct_info[i].sum = 0;

      if ((i + 1) >= nbthreads)
      {

        struct_info[i].ub = n - 1;
      }

      else
      {

        struct_info[i].ub = j + (computations - 1);
      }

      pthread_create(&thread[i], NULL, numerical_integration, (void *)&struct_info[i]);
    }

    j += computations;
  }
  for (int i = 0; i < nbthreads; i += 1)
  {
    pthread_join(thread[i], NULL);
  }
  for (int i = 0; i < nbthreads; i += 1)
  {
    total_sum += struct_info[i].sum;
  }

  cout << lubs_avg * total_sum;

  auto end_time = chrono::system_clock::now();
  chrono::duration<double> mytime = end_time - start_time;
  std::cerr << mytime.count();
  return 0;
}
