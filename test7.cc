#include <omp.h>
#include <iostream>
using namespace std;

#define N 1000000
#define PI 3.1415926535
#define DELTA .01415926535

// Ponizszy kod prowadzi do deadlock
// Zmodyfikuj tak blokady, zeby kod sie wykonal

int main () {

int nthreads, tid, i;
float a[N], b[N];
omp_lock_t locka, lockb;

// Inicjalizacja blokad locks
omp_init_lock(&locka);
omp_init_lock(&lockb);

// Blok rownolegly
#pragma omp parallel shared(a, b, nthreads, locka, lockb) private(tid) num_threads(6)
  {

  tid = omp_get_thread_num();
  #pragma omp master
    {
    nthreads = omp_get_num_threads();
    cout << "Liczba watkow = " << nthreads << endl;
    }
  cout << "Watek nr " << tid << " zaczyna... " << endl;
  #pragma omp barrier

  #pragma omp sections nowait
    {
    #pragma omp section
      {
      cout << "Watek " << tid << " inicjalizujacy a[]\n";
      omp_set_lock(&locka);
      for (i=0; i<N; i++)
        a[i] = i * DELTA;
      omp_unset_lock(&locka);
      omp_set_lock(&lockb);
      cout << "Watek " << tid << " sumujacy a[] to b[]\n";
      for (i=0; i<N; i++)
        b[i] += a[i];
      omp_unset_lock(&lockb);
      }
    #pragma omp section
      {
      cout << "Watek " << tid << " inicjalizujacy b[]\n";
      omp_set_lock(&lockb);
      for (i=0; i<N; i++)
        b[i] = i * PI;
      omp_unset_lock(&lockb);
      omp_set_lock(&locka);
      cout << "Watek " << tid << " sumujacy a[] to b[]\n";
      for (i=0; i<N; i++)
        a[i] += b[i];
      omp_unset_lock(&locka);
      }
    }  
  }
  omp_destroy_lock(&locka);  
  omp_destroy_lock(&lockb); 
}
