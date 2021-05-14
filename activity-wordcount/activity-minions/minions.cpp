#include <iostream>
#include <thread>
#include <sstream>
#include <vector>

void f (int i){
	  std::cout<<"Hello! I am minion "<<i<<"\n";
  }
void finalthread(){
	std::cout<<"hello Minions! I am the Overlord!";
}
int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr<<"usage: "<<argv[0]<<" <nbminions>\n";
    return -1;
  }
  //Your code goes here
  std::vector<std::thread> mythreads;
  
  for (int i=0;i<argc;i++){
	  std::cout<<"Values are "<<argv[i];
  }
  int myint;          
  std::istringstream iss( argv[1] );
  iss>> myint;
  for(int i=0;i<myint;++i){
	  std::thread mythread (f,i);
	  mythreads.push_back(std::move(mythread));
  }
  
  for(auto & t:mythreads){
	  if(t.joinable())
		  t.join();
	  else
		std::cout<<"T is not joinable";
  }
  std::thread myfinalthread (finalthread);
  myfinalthread.join();
  
  return 0;
}
