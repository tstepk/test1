#include <omp.h>
#include <iostream>
using namespace std;

int main () {

  int c = 0;

  // Ponizszy kod to przyklad data race
  // Najpierw go uruchom i poobeserwuj nastepnie
  // tak zmodyfikuj, zeby na ekranie wypisaly sie
  // poprawnie wszystkie wartosci c (od 1 do 8)

  #pragma omp parallel num_threads(8)
  {
  	#pragma omp critical
        cout << ++c << " " << flush;
  }  
}

