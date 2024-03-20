#include <iostream>
#include <iomanip>
#include <arm_neon.h>
using namespace std;
double* NEON128(double** A, double* B, int size) 
{
    double* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(double));
    for (int i=0; i<size; i++)  Res[i] = 0;
    cout << "\n\nМноження матриці на вектор за допомогою NEON 128:\n\n";
    float64x2_t **mA;
    float64x2_t *mB, *mRes;
    float64_t sp_array[2] = {0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);
    mA = (float64x2_t**)A;
    mB = (float64x2_t*)B;
    mRes = (float64x2_t*)Res;
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
        cout << setw(6) << Res[i] << "\n";
    }
    return Res;
}
double* NEON256(double** A, double* B, int size)
{
    double* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(double));
    for (int i=0; i<size; i++)  Res[i] = 0;
    cout << "\n\nМноження матриці на вектор за допомогою NEON 256:\n\n";
    float64_t sp_array[4] = {0.0, 0.0, 0.0, 0.0};
    float64x2_t s, p;
    s = vld1q_f64(sp_array);
    p = vld1q_f64(sp_array);

    float64x2_t* mB = (float64x2_t*)B;
    float64x2_t* mRes = (float64x2_t*)Res;
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
        cout << setw(6) << Res[i] << "\n";
    }
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
    srand(time(NULL));
    int n;

    // Множення матриці на вектор
    
    n = 3;
    double** A1;
    A1 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A1[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A1[i][j] = rand() % 19 - 9;
            cout << setw(6) << A1[i][j] << " ";
        }
        cout << endl;
    }

    double* B1;
    posix_memalign((void**)&B1, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B1[i] = rand()%19-9;
        cout << setw(6) << B1[i] << "\n";
    }

    double* Res1;
    posix_memalign((void**)&Res1, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res1[i] = 0;
    cout << "\n\nМноження матриці на вектор звичайним способом:\n\n";
    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++)
        {
            Res1[i] += A1[i][j] * B1[j];
        }
        cout << setw(6) << Res1[i] << "\n";
    }

    free(A1);
    free(B1);
    free(Res1);

    n = 4;

    double** A2;
    A2 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        posix_memalign((void**)&A2[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A2[i][j] = rand() % 19 - 9;
            cout << setw(6) << A2[i][j] << " ";
        }
        cout << endl;
    }

    double* B2;
    posix_memalign((void**)&B2, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B2[i] = rand()%19-9;
        cout << setw(6) << B2[i] << "\n";
    }
    NEON128(A2, B2, n); 

    free(A2);
    free(B2);

    n = 8;
    
    double** A3;
    A3 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A3[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A3[i][j] = rand() % 19 - 9;
            cout << setw(6) << A3[i][j] << " ";
        }
        cout << endl;
    }

    double* B3;
    posix_memalign((void**)&B3, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B3[i] = rand()%19-9;
        cout << setw(6) << B3[i] << "\n";
    }

    NEON256(A3, B3, n); 

    free(A3);
    free(B3);

    // Множення вектора на сакрал

    n = 3;

    double* B4;
    posix_memalign((void**)&B4, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B4[i] = rand()%19-9;
        cout << setw(6) << B4[i] << " ";
    }

    double a __attribute__((aligned(32))) = rand() % 19 - 9;
    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал:\n\n";
    double* Res4;
    posix_memalign((void**)&Res4, 32, n * sizeof(double));
    for (int i=0; i<n; i++) 
    {
        Res4[i] = 0;
        Res4[i] = B4[i] * a;
        cout << setw(6) << Res4[i] << " ";
    }

    free(B4);
    free(Res4);

    n = 4;

    double* B5;
    posix_memalign((void**)&B5, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B5[i] = rand()%19-9;
        cout << setw(6) << B5[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 128:\n\n";
    double* Res5;
    posix_memalign((void**)&Res5, 32, n * sizeof(double));
    for (int i=0; i<n; i++) Res5[i] = 0;
    multiply_vector_scalar_NEON128(B5, a, n, Res5);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res5[i] << " ";
    }

    free(B5);
    free(Res5);

    n = 8;

    double* B6;
    posix_memalign((void**)&B6, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B6[i] = rand()%19-9;
        cout << setw(6) << B6[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 256:\n\n";
    double* Res6;
    posix_memalign((void**)&Res6, 32, n * sizeof(double));
    for (int i=0; i<n; i++) Res6[i] = 0;
    multiply_vector_scalar_NEON256(B6, a, n, Res6);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res6[i] << " ";
    }

    free(B6);
    free(Res6);

    // Множення матриці на вектор

    n = 3;

    double** A7;
    A7 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A7[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A7[i][j] = rand() % 19 - 9;
            cout << setw(6) << A7[i][j] << " ";
        }
        cout << endl;
    }

    double* B7;
    posix_memalign((void**)&B7, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B7[i] = rand()%19-9;
        cout << setw(6) << B7[i] << "\n";
    }

    double* Res7;
    posix_memalign((void**)&Res7, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res7[i] = 0;
    cout << "\n\nМноження матриці на вектор звичайним способом:\n\n";
    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++)
        {
            Res7[i] += A7[i][j] * B7[j];
        }
        cout << setw(6) << Res7[i] << "\n";
    }

    free(A7);
    free(B7);
    free(Res7);

    n = 4;
    
    double** A8;
    A8 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A8[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A8[i][j] = rand() % 19 - 9;
            cout << setw(6) << A8[i][j] << " ";
        }
        cout << endl;
    }

    double* B8;
    posix_memalign((void**)&B8, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B8[i] = rand()%19-9;
        cout << setw(6) << B8[i] << "\n";
    }

    double* Res8;
    posix_memalign((void**)&Res8, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res8[i] = 0;
    cout << "\n\nМноження матриці на вектор за допомогою NEON 128:\n\n";
    multiply_matrix_vector_NEON128(A8, B8, n, Res8);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res8[i] << "\n";
    }

    free(A8);
    free(B8);
    free(Res8);

    n = 8;
    
    double** A9;
    A9 = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A9[i], 32, n * sizeof(double));
    }
    cout << "\n\nМатриця:\n\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            A9[i][j] = rand() % 19 - 9;
            cout << setw(6) << A9[i][j] << " ";
        }
        cout << endl;
    }

    double* B9;
    posix_memalign((void**)&B9, 32, n * sizeof(double));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B9[i] = rand()%19-9;
        cout << setw(6) << B9[i] << "\n";
    }

    double* Res9;
    posix_memalign((void**)&Res9, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res9[i] = 0;
    cout << "\n\nМноження матриці на вектор за допомогою NEON 256:\n\n";
    multiply_matrix_vector_NEON256(A9, B9, n, Res9);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res9[i] << "\n";
    }

    free(A9);
    free(B9);
    free(Res9);

    // Складання векторів
    
    n = 3;
    
    double* A10;
    posix_memalign((void**)&A10, 32, n * sizeof(double));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A10[i] = rand()%19-9;
        cout << setw(6) << A10[i] << " ";
    }

    double* B10;
    posix_memalign((void**)&B10, 32, n * sizeof(double));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B10[i] = rand()%19-9;
        cout << setw(6) << B10[i] << " ";
    }

    double* Res10;
    posix_memalign((void**)&Res10, 32, n * sizeof(double));
    cout << "\n\nСкладання векторів:\n\n";
    for (int i=0; i<n; i++)  Res10[i] = 0;
    for (int i=0; i<n; i++) 
    {
        Res10[i] = B10[i] + A10[i];
        cout << setw(6) << Res10[i] << " ";
    }

    free(A10);
    free(B10);
    free(Res10);

    n = 4;
    
    double* A11;
    posix_memalign((void**)&A11, 32, n * sizeof(double));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A11[i] = rand()%19-9;
        cout << setw(6) << A11[i] << " ";
    }

    double* B11;
    posix_memalign((void**)&B11, 32, n * sizeof(double));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B11[i] = rand()%19-9;
        cout << setw(6) << B11[i] << " ";
    }

    double* Res11;
    posix_memalign((void**)&Res11, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res11[i] = 0;
    cout << "\n\nСкладання векторів за допомогою NEON 128:\n\n";
    vectors_plus_NEON128(A11, B11, n, Res11); 
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res11[i] << " ";
    }
    free(A11);
    free(B11);
    free(Res11);

    n = 8;

    double* A12;
    posix_memalign((void**)&A12, 32, n * sizeof(double));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A12[i] = rand()%19-9;
        cout << setw(6) << A12[i] << " ";
    }

    double* B12;
    posix_memalign((void**)&B12, 32, n * sizeof(double));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B12[i] = rand()%19-9;
        cout << setw(6) << B12[i] << " ";
    }


    double* Res12;
    posix_memalign((void**)&Res12, 32, n * sizeof(double));
    for (int i=0; i<n; i++)  Res12[i] = 0;
    cout << "\n\nСкладання векторів за допомогою NEON 256:\n\n";
    vectors_plus_NEON256(A12, B12, n, Res12); 
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res12[i] << " ";
    }
    free(A12);
    free(B12);
    free(Res12);

    cout << "\n\n";
    return 0;
}