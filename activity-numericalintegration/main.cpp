#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std;

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

int main(int argc, char * argv[]) {

  auto start_time = chrono::system_clock::now();

  if (argc < 6) {
    cerr << "usage: " << argv[0] << " <functionid> <a> <b> <n> <intensity>";
    return -1;
  }
  int current_pass_value;

  
int function_id, a, b, n, intensity;
float x, current_fun_value = 0, lower_upper_bound_sub, lubs_avg;

  function_id = strtof(argv[1],NULL);
  a = strtof(argv[2],NULL);
  b = strtof(argv[3],NULL);
  n = strtof(argv[4],NULL);
  intensity = strtof(argv[5],NULL);

  lower_upper_bound_sub = b - a;

  lubs_avg = lower_upper_bound_sub / n;

  for (current_pass_value = 0; current_pass_value <= n - 1; current_pass_value++) {
    x = a + ((current_pass_value + 0.5) * lubs_avg);

    switch (function_id) {
    case 1:
      current_fun_value = current_fun_value + f1(x, intensity);
      break;
    case 2:
      current_fun_value = current_fun_value + f2(x, intensity);
      break;
    case 3:
      current_fun_value = current_fun_value + f3(x, intensity);
      break;
    case 4:
      current_fun_value = current_fun_value + f4(x, intensity);
      break;
    default:
      cerr << "wrong F_id";
      break;

    }
  }
  /*float final_integral_val = current_fun_value * lubs_avg;*/
  cout << current_fun_value * lubs_avg;

  auto end_time = chrono::system_clock::now();
  cerr << end_time-start_time;

  return 0;
}