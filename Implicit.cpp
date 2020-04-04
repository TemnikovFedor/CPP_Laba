#include <omp.h>

void implic (int DIM1, double C, double t2[],double T0,double T1,double h,int m) {
    double t1[DIM1], A, B, E, alpha[DIM1], beta[DIM1], F[DIM1];
    A = C / 2;
    B = - 1 - C;
    E = C / 2;
#pragma omp parallel  num_threads(m)
    {
#pragma omp for

        for (int j = 0; j < DIM1; j++) {
            t1[j] = t2[j];
        }

        F[0] = -(1 + h) * t1[0] - C / 2 * T0;
#pragma omp for
        for (int i = 1; i < DIM1 - 1; i++) {
            F[i] = -t1[i] - h * t1[i];
        }
        F[DIM1 - 1] = -(1 + h) * t1[DIM1 - 1] - C / 2 * T1;

        alpha[0] = C / (2 + 2 * C);
        beta[0] = 1 / (1 + C) * (T0 * C / 2 + (1 + h) * t1[0]);
#pragma omp for

        for (int i = 0; i < DIM1 - 1; i++) {
            alpha[i + 1] = -E / (alpha[i] * A + B);
            beta[i + 1] = (F[i + 1] - A * beta[i]) / (A * alpha[i] + B);
        }
        alpha[DIM1 - 1] = 0;
        t2[DIM1 - 1] = beta[DIM1 - 1];
#pragma omp for
        for (int i = DIM1 - 2; i > -1; i--) {
            t2[i] = alpha[i + 0] * t2[i + 1] + beta[i + 0];
        }
    }

}
