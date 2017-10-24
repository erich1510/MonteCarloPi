// AUTHOR: Victor Alessandrini, 2015
// Example in book "Shared Memory Application
// Programming"
// ***********************************************
// File McObj.C
//
// MonteCarlo computation of PI
//
// Thread safe version, using a C++ Rand class and
// private Rand objects to generate random numbers
// -----------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <SPool.h>
#include <CpuTimer.h>
#include <iomanip>
#include <math.h>

#include <pthread.h>
using namespace std;

// Global variables for this example
// ---------------------------------
int nTh;               //numter of threads?
SPool *TH;             // pool of two threads
unsigned long nsamples;         // number of MC events
double accepted[1024];   // storage of partial results
// --------------------------------------------------
// A simple generator, that produces uniform deviates
// in [0,1]. The integer "seed" is preserved between
// calls.
// --------------------------------------------------
//
#define PI     3.1415926535
#define IMUL   314159269
#define IADD   453806245
#define MASK   2147483647
#define SCALE  0.4656612873e-9



class Rand
{
private:
 unsigned int seed;

public:
 Rand(long S) : seed(S) {}

 double Draw()
 {
    // seed = (seed * IMUL + IADD) & MASK;
    // return (seed * SCALE);
  return (double)rand_r(&seed)/RAND_MAX;

}
};

// The task function
// -----------------
void task_fct(void *P)
{
   double x, y;
   double count;
   double beg, end;
   double end2;
   int rank;

  unsigned int seedx = 123482;  //arbitrary seed values
  unsigned int seedy = 567843;

  beg = 0;
  end = nsamples;
  end2 = nsamples/nTh;

  TH->ThreadRange(beg, end);

  rank = TH->GetRank();   // in SPool, ranks start at 1
  Rand Rx(seedx*rank);      // thread dependent initialization
  Rand Ry(seedy*rank);
  //std::cout << "Hello from Thread " << rank << endl;

  for(int i = beg; i < end; i++)
  {
   x = Rx.Draw();
   y = Ry.Draw();
   if( (x*x+y*y) <= 1.0)
    count++;
}

accepted[rank] = count;

   // rank = TH.GetRank();   // in SPool, ranks start at 1
   // Rand R(999*rank);      // thread dependent initialization
   // count = 0;
   // for(size_t n=0; n<nsamples; n++)
   //    {
   //    x = R.Draw();
   //    y = R.Draw();
   //    if((x*x+y*y) <= 1.0 ) count++;
   //    }
   // accepted[rank] = count;
}

// The main function
// -----------------
int main(int argc, char **argv)
{
  double C;
  CpuTimer T;

  if(argc >= 2) nsamples = atoi(argv[1]);
  else nsamples = 1000000000;

  if(argc == 3) nTh = atoi(argv[2]);
  else nTh = 2;

  TH = new SPool(nTh);

  T.Start();

  TH->Dispatch(task_fct, NULL);
  TH->WaitForIdle(); 

  T.Stop();

 for (int i = 1; i <= nTh; i++) // in SPool, ranks start at 1
 {
   C = C + accepted[i];
//cout << "Accepted [" << i <<  "]: = " << accepted[i] << endl;
}

 // C = C / (nTh - 1); //average results

double pi = 4 * C / (nsamples);

// if (nTh > 2)
//   for (int i = 2; i > nTh; i++){
//     pi = sqrt(pi);
// }

   //cout << "\n Value of PI = " << pi << endl;

std::cout << std::fixed;
std::cout << std::setprecision(12);

std::cout << "\nActual Value of Pi = " << PI << endl;
std::cout << "Calculated Value of Pi = " << pi << endl;
cout << "Number of Threads = " << nTh << endl;
cout << "Number of Throws = " << nsamples << endl;
T.Report();
}
