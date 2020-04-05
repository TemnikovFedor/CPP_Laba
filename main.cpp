#include <iostream>
#include <chrono>
#include "Implicit.h"
#include "Explicit.h"
#include <omp.h>

int main() {
  
    double T0, T1, h;
    int DIM1 = 11, m, iter = 5000;
    char Choose;
    double C, D = 0.25, dt = 0.0001, dx = 0.01;

    std::cout << "T0 T1" << std::endl;
    std::cin >> T0 >> T1;
    std::cout << "Choose method E/I" << std::endl;
    std::cin >> Choose;
    std::cout << "Number of processes" << std::endl;
    std::cin >> m;
    std::cout << "Coefficient of phi" << std::endl;
    std::cin >> h;
    
    C = 2 * D * dt / (dx * dx);
    std::cout << "C=" << C << std::endl;
    
    h = h*dt;
    double t2[DIM1];
    for (int k = 0; k < DIM1; k++) {
        t2[k] = 0;
    }

    // check this out: if all works you will see correct number of threads
    // with current CMakeLists.txt I can't even compile this (see comments in CMakeLists.txt)
#pragma omp parallel
    {
#pragma omp single
      std::cout << "Threads used: " << omp_get_num_threads() << std::endl;
    }
    
    auto start = std::chrono::system_clock::now();
    if (Choose == 'E') {
        for (int i = 1; i <= iter; i++) {
            explic(DIM1, C, t2, m, T0, T1, h);
        }
    } else if (Choose == 'I') {
        for (int i = 1; i <= iter; i++) {
            implic(DIM1, C, t2, T0, T1, h, m);
        }
    }
    
    std::cout << T0 << " ";
    for (int k = 0; k < DIM1; k++) {
      std::cout << t2[k] << " ";
    }
    std::cout << T1 << std::endl;

    // printing is also included in time measurement. this could have impact on the results
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed parallel time: " << elapsed.count() << std::endl;

}



