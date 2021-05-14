#ifndef __SEQ_LOOP_H
#define __SEQ_LOOP_H

#include <thread>
#include <iostream>
#include <functional>
#include <vector>


class SeqLoop {
private:
  int n;
  int nbthread;

public:
  SeqLoop(int n1, int nbthread1){
    this->n = n1;
    this->nbthread = nbthread1;
  }

  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel
  void parfor (size_t beg, size_t end, size_t inc,
	       std::function<void(int)> f) {
    for (size_t i=beg; i<end; i+= inc) {
      f(i);
    }
  }

  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel.
  ///
  /// Each thread that participate in the calculation will have its
  /// own TLS object.
  ///
  /// Each thread will execute function before prior to any
  /// calculation on a TLS object.
  ///
  /// Each thread will be passed the TLS object it executed before on.
  ///
  /// Once the iterations are complete, each thread will execute after
  /// on the TLS object. No two thread can execute after at the same time.
  template<typename TLS>
  void parfor (size_t beg, size_t end, size_t increment,
	       std::function<void(TLS&)> before,
	       std::function<void(int, TLS&)> f,
	       std::function<void(TLS&)> after
	       ) {
    
    std::vector<TLS> tlsGroup;
    std::vector<std::thread> threadgroup;

    for(int i=0; i<nbthread; i++){
      TLS tls;
      tlsGroup.push_back(tls);
    }
    int computations = n / nbthread;

    for(int t=0; t<nbthread; t++){
      before(tlsGroup[t]);
	  
      threadgroup.push_back(std::thread([&](size_t begOne, size_t endOne, int incrementOne, TLS& tls) {
              for (size_t i=begOne; i<endOne; i+= incrementOne){					   
                f(i, tls);
              }
     
            }, t * computations, (nbthread - 1) == t ? n : (t * computations) + computations, 1, std::ref(tlsGroup[t]))
      );
    }
    for (auto& thread : threadgroup){
      thread.join();
    }
    for(auto& s : tlsGroup){
      after(s);
    }
  }
  
};

#endif
