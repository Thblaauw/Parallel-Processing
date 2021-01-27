#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <utility>
#include <vector>
#include <thread>

using namespace std;

constexpr long long size= 20;
mutex myMutex;

void sumUp(double& sum, const vector<double>& val,
   unsigned long long beg, unsigned long long end){
   double localSum = 0;
    for (auto it= beg; it <= end; ++it){
        localSum+= val[it];
    }
    lock_guard<mutex> myLock(myMutex);
    sum += localSum;
}

int main(){

  cout << endl;

  vector<double> randValues;
  randValues.reserve(size);

  mt19937 engine (0);
  uniform_int_distribution<> uniformDist(1,10);
  for ( long long i=0 ; i< size ; ++i)
     randValues.push_back((double)1/(i+1.0f));
	
  double sum= 0;
  auto start = chrono::system_clock::now();

  int threads = 5;
  long long slice;
  while(size % threads != 0)
  	threads++;
  thread t[threads];
  slice = size / threads;
  int startIdx=0;
  for (int i = 0; i < threads; ++i) {
    cout << "Thread[" << i << "] - slice ["
         << startIdx << ":" << startIdx+slice-1 << "]" << endl;
    t[i] = thread(sumUp, ref(sum), ref(randValues), startIdx, startIdx+slice-1);
    startIdx += slice;
  }

  for (int i = 0; i < threads; ++i)
     t[i].join();

  chrono::duration<double> dur= chrono::system_clock::now() - start;
  cout << "Time for addition " << dur.count() << " seconds" << endl;
  cout << "Result: " << sum << endl;

  cout << endl;

}
