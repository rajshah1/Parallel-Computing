#include <vector>
#include <iostream>
#include "seq_loop.hpp"


int main ( ) {

  SeqLoop sl;

  std::vector<int> a = {1,1,1,1,1};
  std::vector<int> b (a.size());
  
  sl.parfor(0, a.size(), 1,
	    [&](int i) -> void{
	      b[i] = 2*a[i];
	    }
	    );

  for (auto val : b)
    std::cout<<val<<" ";
  std::cout<<"\n";

  int sum = 0;
    
  sl.parfor<int>(0, b.size(), 1,
		 [&](int& tls) -> void{
		   tls = 0;
		 },
		 [&](int i, int& tls) -> void{
		   tls += b[i];
		  },
		 [&](int tls) -> void{
		   sum += tls;
		 }
		 );

    std::cout<<sum<<"\n";
    
  return 0;
}
