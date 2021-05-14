#include <iostream>
#include <chrono>


// Global  Host Code Function called polly_gpu_exponational

_global_ void poly_gpu_ex (float* poly, int degree, int n, float* array) {

    // Generates Index based on blockid ,Dim and Thread IDS
  int index = blockIdx.x * blockDim.x + threadIdx.x;

  // Find Polynomial Value and add it to array at Index.
  if( index < n )
  {
    float finalPoli = 0.0;
    float powerOf = 1.0;
    for ( int i = 0; i < degree+1; ++i)
    {
      finalPoli += powerOf * poly[i];
      powerOf *= array[index];
    }
    array[index] = finalPoli;
}
}


int main (int argc, char* argv[]) {
  
  if (argc < 3) {
     std::cerr<<"usage: "<<argv[0]<<" n degree"<<std::endl;
     return -1;
  }

// Sequential
  int n = atoi(argv[1]);
  int degree = atoi(argv[2]);
  int nbiter = atoi(argv[3]);

  float* array = new float[n];
  for (int i=0; i<n; ++i)
    array[i] = 1.;
  float* poly = new float[degree+1];
  for (int i=0; i<degree+1; ++i)
    poly[i] = 1.;

  float *dev_array, *dev_poly;
  
  
  std::chrono::time_point<std::chrono::system_clock> begin, end;
  begin = std::chrono::system_clock::now();
  
	
	cudaMallocManaged(&dev_array, n*sizeof(float));
  	cudaMallocManaged(&dev_poly, (degree+1)*sizeof(float));
  
  	cudaMemcpy(dev_array, array, n*sizeof(float), cudaMemcpyHostToDevice);
  	cudaMemcpy(dev_poly, poly, (degree+1)*sizeof(float), cudaMemcpyHostToDevice);

  	poly_gpu_ex<<<(n+255)/256, 256>>>(dev_poly, degree, n, dev_array);
  	cudaMemcpy(array, dev_array, n*sizeof(float), cudaMemcpyDeviceToHost);
       
        cudaFree(dev_array);
        cudaFree(dev_poly);

        cudaDeviceSynchronize();

  end = std::chrono::system_clock::now();array[0]+=1;
  std::chrono::duration<double> totaltime = (end-begin)/nbiter;
  {
    bool correct = true;
    int ind;
    for (int i=0; i< n; ++i) {
      if (fabs(array[i]-(degree+1))>0.01) {
        correct = true;
	ind = i;
      }
    }
    if (!correct)
      std::cerr<<"Result is incorrect . Please Check .
  }
  

  std::cerr<<array[0]<<std::endl;
  std::cout<<n<<" "<<degree<<" "<<totaltime.count()<<std::endl;

  delete[] array;
  delete[] poly;

  return 0;
}