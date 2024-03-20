#include <iostream>
#include <ctime>
#include <arm_neon.h>
using namespace std;
double* NEON128(double** A, double* B, int size) 
{
    double* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(double));
    for (int i=0; i<size; i++)  Res[i] = 0;
    
    float64x2_t **mA;
    float64x2_t *mB, *mRes;
    float64_t sp_array[2] = {0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);
    mA = (float64x2_t**)A;
    mB = (float64x2_t*)B;
    mRes = (float64x2_t*)Res;
    double t1 = clock();
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/2; j++)
        {
            s = vmulq_f64(mA[i][j], mB[j]);
            p = vaddq_f64(p, s);
        }
        float64_t d = vgetq_lane_f64(p, 0) + vgetq_lane_f64(p, 1);
        Res[i] += d;
        p = vld1q_f64(sp_array);
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 128): " << t1/CLOCKS_PER_SEC << " seconds.";
    return Res;
}
double* NEON256(double** A, double* B, int size)
{
    double* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(double));
    for (int i=0; i<size; i++)  Res[i] = 0;
    float64_t sp_array[4] = {0.0, 0.0, 0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);

    float64x2_t* mB = (float64x2_t*)B;
    float64x2_t* mRes = (float64x2_t*)Res;
    double t1 = clock();
    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_f64(0.0);
        for (int j = 0; j < size / 4; j++)
        {
            s = vmulq_f64(vld1q_f64(A[i] + j * 4), mB[j * 2]);
            s = vaddq_f64(s, vmulq_f64(vld1q_f64(A[i] + j * 4 + 2), mB[j * 2 + 1]));
            p = vaddq_f64(p, s);
        }
        double d = (double)vgetq_lane_f64(p, 0) + (double)vgetq_lane_f64(p, 1);
        Res[i] += d;
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 256): " << t1/CLOCKS_PER_SEC << " seconds.";
    return Res;
}
double* multiply_vector_scalar_NEON128(double* vector, double scalar, int size, double* Res1)
{
    float64x2_t* mv = (float64x2_t*)vector;
    float64x2_t* mRes1 = (float64x2_t*)Res1;
    float64x2_t scalar_v = vdupq_n_f64(scalar);
    for (int i = 0; i < size; i += 2)
    {
        float64x2_t vector_v = vld1q_f64(vector + i);
        vector_v = vmulq_f64(vector_v, scalar_v);
        vst1q_f64(Res1 + i, vector_v);
    }
    return Res1;
}
double* multiply_vector_scalar_NEON256(double* vector, double scalar, int size, double* Res1)
{
    double* mv = vector;
    double* mRes1 = Res1;
    float64x2_t scalar_v = vdupq_n_f64(scalar);
    for (int i = 0; i < size / 8; i++)
    {
        float64x2_t v0 = vld1q_f64(&mv[i * 8]);
        float64x2_t v1 = vld1q_f64(&mv[i * 8 + 2]);
        float64x2_t v2 = vld1q_f64(&mv[i * 8 + 4]);
        float64x2_t v3 = vld1q_f64(&mv[i * 8 + 6]);
        v0 = vmulq_f64(v0, scalar_v);
        v1 = vmulq_f64(v1, scalar_v);
        v2 = vmulq_f64(v2, scalar_v);
        v3 = vmulq_f64(v3, scalar_v);
        vst1q_f64(&mRes1[i * 8], v0);
        vst1q_f64(&mRes1[i * 8 + 2], v1);
        vst1q_f64(&mRes1[i * 8 + 4], v2);
        vst1q_f64(&mRes1[i * 8 + 6], v3);
    }
    for (int i = (size / 8) * 8; i < size; i++)
    {
        mRes1[i] = mv[i] * scalar;
    }
    return Res1;
}
double* multiply_matrix_vector_NEON128(double** A, double* B, int size, double* Res2) 
{
    float64x2_t **mA;
    float64x2_t *mB, *mRes2;
    float64_t sp_array[2] = {0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);
    mA = (float64x2_t**)A;
    mB = (float64x2_t*)B;
    mRes2 = (float64x2_t*)Res2;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/2; j++)
        {
            s = vmulq_f64(mA[i][j], mB[j]);
            p = vaddq_f64(p, s);
        }
        float64_t d = vgetq_lane_f64(p, 0) + vgetq_lane_f64(p, 1);
        Res2[i] += d;
        p = vld1q_f64(sp_array);
    }
    return Res2;
}
double* multiply_matrix_vector_NEON256(double** A, double* B, int size, double* Res2)
{
    float64_t sp_array[4] = {0.0, 0.0, 0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);

    float64x2_t* mB = (float64x2_t*)B;
    float64x2_t* mRes2 = (float64x2_t*)Res2;
    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_f64(0.0);
        for (int j = 0; j < size / 4; j++)
        {
            s = vmulq_f64(vld1q_f64(A[i] + j * 4), mB[j * 2]);
            s = vaddq_f64(s, vmulq_f64(vld1q_f64(A[i] + j * 4 + 2), mB[j * 2 + 1]));
            p = vaddq_f64(p, s);
        }
        double d = (double)vgetq_lane_f64(p, 0) + (double)vgetq_lane_f64(p, 1);
        Res2[i] += d;
    }
    return Res2;
}
double* vectors_plus_NEON128(double* vector1, double* vector2, int size, double* Res3) 
{ 
    float64x2_t *mv1, *mv2, *mRes3; 
    mv1 = (float64x2_t*)vector1; 
    mv2 = (float64x2_t*)vector2; 
    mRes3 = (float64x2_t*)Res3; 
    for (int i = 0; i < size; i += 2) 
    { 
        float64x2_t v1 = vld1q_f64(&vector1[i]); 
        float64x2_t v2 = vld1q_f64(&vector2[i]);

        float64x2_t res = vaddq_f64(v1, v2);

        vst1q_f64(&Res3[i], res);
    }
    return Res3;
}
double* vectors_plus_NEON256(double* vector1, double* vector2, int size, double* Res3)
{
    float64x2x4_t *mv1, *mv2, *mRes3;
    mv1 = (float64x2x4_t*)vector1;
    mv2 = (float64x2x4_t*)vector2;
    mRes3 = (float64x2x4_t*)Res3;
    for (int i = 0; i < size/8; i++)
    {
        float64x2x4_t v1 = vld4q_f64(&vector1[8*i]);
        float64x2x4_t v2 = vld4q_f64(&vector2[8*i]);

        float64x2x4_t res;
        res.val[0] = vaddq_f64(v1.val[0], v2.val[0]);
        res.val[1] = vaddq_f64(v1.val[1], v2.val[1]);
        res.val[2] = vaddq_f64(v1.val[2], v2.val[2]);
        res.val[3] = vaddq_f64(v1.val[3], v2.val[3]);

        vst4q_f64(&Res3[8*i], res);
    }
    return Res3;
}
int main()
{
    int n=1000;
    srand(time(NULL));
    double t1;

    for (n = 1000; n <= 22000; n += 1000)
    {
        double **A, *B, *Res1, *Res2, *Res3, *x, *y;
        A = (double**)malloc(n * sizeof(double*));
        for (int i = 0; i < n; i++) 
        {
            posix_memalign((void**)&A[i], 32, n * sizeof(double));
        }
        posix_memalign((void**)&B, 32, n * sizeof(double));
        posix_memalign((void**)&Res1, 32, n * sizeof(double));
        posix_memalign((void**)&Res2, 32, n * sizeof(double));
        posix_memalign((void**)&Res3, 32, n * sizeof(double));
        posix_memalign((void**)&x, 32, n * sizeof(double));
        posix_memalign((void**)&y, 32, n * sizeof(double));
        double a __attribute__((aligned(32))) = rand() % 19 - 9;
        

        for (int i=0; i<n; i++) for (int j=0; j<n; j++) A[i][j] = rand()%19-9;
        for (int i=0; i<n; i++) B[i] = rand()%19-9;
        for (int i=0; i<n; i++) x[i] = rand()%19-9;
        for (int i=0; i<n; i++) y[i] = rand()%19-9;
        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        cout << "\n\n" << n << "\tdouble\n\n";

        t1 = clock();
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) Res1[i] += A[i][j] * B[j];
        t1 = clock() - t1;
        cout << "Time to multiplication a matrix A by a vector B: " << t1/CLOCKS_PER_SEC << " seconds.\n";

        NEON128(A, B, n);
        cout << "\n";
        NEON256(A, B, n);
        cout << "\n";

        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        t1 = clock();
        for (int i=0; i < n; i++) Res1[i] = x[i] * a;
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) Res2[i] += A[i][j] * Res1[j];
        for (int i=0; i<n; i++) Res3[i] = Res2[i] + y[i];
        t1 = clock() - t1;
        cout << "Time to perfomance aAx + y: " << t1/CLOCKS_PER_SEC << " seconds.\n";

        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        t1 = clock();
        multiply_vector_scalar_NEON128(x, a, n, Res1);
        multiply_matrix_vector_NEON128(A, Res1, n, Res2);
        vectors_plus_NEON128(Res2, y, n, Res3);
        t1 = clock() - t1;
        cout << "Time to perfomance aAx + y (whith NEON 128): " << t1/CLOCKS_PER_SEC << " seconds.\n";

        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        t1 = clock();
        multiply_vector_scalar_NEON256(x, a, n, Res1);
        multiply_matrix_vector_NEON256(A, Res1, n, Res2);
        vectors_plus_NEON256(Res2, y, n, Res3);
        t1 = clock() - t1;
        cout << "Time to perfomance aAx + y (whith NEON 256): " << t1/CLOCKS_PER_SEC << " seconds.\n";

        cout << "\n\n";
        delete[] B;
        delete[] Res1;
        delete[] Res2;
        delete[] Res3;
        delete[] x;
        delete[] y;
        for (int i=0; i<n; i++) delete[] A[i]; delete[] A;
    }
    return 0;
}