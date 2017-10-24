// AUTHOR: Libby Shoop
// loosely based on threaded example by
//   Victor Alessandrini, 2015
// Example in book "Shared Memory Application
// Programming"
// **************************************
// File CalPiSequential.C
//
// MonteCarlo computation of PI using a sequential for loop
// method with no paralleization.
//
//
// ------------------------------------------
#include <stdlib.h>
#include <CpuTimer.h>
#include <iostream>
//#include <Rand.h>
//#include <SPool.h>             // new
//#include <random>
using namespace std;
// SPool TH(2);            // pool of two threads
// long accepted[3];       // storage of partial results
// long nsamples;          // number of mC events


//Rand R(999);            // global random number generator

// Libby's comment:
//   I am not certain that Victor's Rand class is particularly
//   good at providing a random distribution.
//   The original C srand/rand_r combo isn't ideal either
//    but it seems better, so I used it in this example.

// NOTE: not using threading, so commented out this function
//       below for now.
//       A threaded version should use the parallel loop
//       equal chunks patterm. See the patternlet for this.

// void thread_fct(void *P)
// {
//   unsigned long ct;
//   double x, y;
//   int rank = TH.GetRank();
//   ct = 0;
//   for(int n=0; n<nsamples; n++)
//   {
//     x = R.draw();
//     y = R.draw();
//     if((x*x+y*y) <= 1.0 ) ct++;
//   }
//   accepted[rank] = ct;
// }


int main(int argc, char **argv)
{
  CpuTimer T;
  double x, y, pi;
  unsigned long ct, accepted;
  unsigned long nsamples;

  // set up seed for rand_r
  unsigned int seedx = 35791246;  //arbitrary seed values
  unsigned int seedy = 97834609;

  // Initialize nsamples
  // -------------------
  if(argc==2) nsamples = atoi(argv[1]);
  else nsamples = 1000000000;
  //nsamples /= 2;

  // Run, measuring execution times
  // ------------------------------
  T.Start();
  // -------------------------------------------------------
  //TH.Dispatch(thread_fct, NULL);
  //TH.WaitForIdle();

  for(int n=0; n<nsamples; n++)
  {
    // x = R.draw();   // not very good distribution
    // y = R.draw();   // so abandoned this

    // rand is not thread safe, but rand_r is.
    // rand_r is faster and has a better distribution also
    // so we will use it for our sequential example
    x = (double)rand_r(&seedx)/RAND_MAX;
    y = (double)rand_r(&seedy)/RAND_MAX;
    if((x*x+y*y) <= 1.0 ) ct++;
  }
  accepted = ct;

  pi = 4.0 * (double)(accepted) / (nsamples);
  // -------------------------------------------------------
  T.Stop();

  cout << "\n  accepted = " << accepted << "\n  Value of PI = " << pi << endl;
  T.Report();
}
