#include <omp.h>
void explic (int DIM1, double C, double t2[], int m,double T0,double T1,double h){
    double t1[DIM1];
    t1[0]=C / 2 * (T0) + (1 - C + h) * (t2[0]) + C / 2 * (t2[1]);
#pragma omp parallel  num_threads(m)
    {
#pragma omp for
        for (int j = 1; j < DIM1 - 1; j++) {
            t1[j] = C / 2 * (t2[j - 1]) + (1 - C + h) * (t2[j]) + C / 2 * (t2[j + 1]);
        }

        t1[DIM1 - 1] = C / 2 * (t2[DIM1 - 2]) + (1 - C + h) * (t2[DIM1 - 1]) + C / 2 * (T1);
#pragma omp for

        for (int j = 0; j < DIM1; j++) {
            t2[j] = t1[j];
        }
    }
}
