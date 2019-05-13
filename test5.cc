#include <omp.h>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void fun( int t ) {
  this_thread::sleep_for(chrono::seconds(t));
}

int main () {

    // Wykonaj petle na czterech rownoleglych watkach
    // oraz tak dobierz opcje optymalizujaca wysylanie
    // kolejnych iteracji do watkow, zeby liczylo sie to
    // istotnie szybciej, niz w przypadku domyslnej strategii
	#pragma omp parallel num_threads(4) 
	{
		#pragma omp for schedule(static,1)
	      for (int i=0; i<16; ++i) fun(i);
	}
}

