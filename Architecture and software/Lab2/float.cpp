#include <iostream>
#include <iomanip>
#include <arm_neon.h>
using namespace std;
float* NEON128(float** A, float* B, int size)  
{
    float* Rez;
    posix_memalign((void**)&Rez, 16, size * sizeof(float));
    for (int i = 0; i < size; i++)
    {
        Rez[i] = 0.f;
    }

    float32x4_t **mA, *mB, *mRez;
    float32_t sp_array[4] = {0.f, 0.f, 0.f, 0.f};
    float32x4_t s, p;
    s = vld1q_f32(sp_array);
    p = vld1q_f32(sp_array);

    mA = (float32x4_t**)A;
    mB = (float32x4_t*)B;
    mRez = (float32x4_t*)Rez;

    cout << "\n\nМноження матриці на вектор за допомогою NEON 128:\n\n";
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/4; j++)
        {
            s = vmulq_f32(mA[i][j], mB[j]);
            p = vaddq_f32(p, s);
        }
        float32x2_t d = vpadd_f32(vget_low_f32(p), vget_high_f32(p));
        d = vpadd_f32(d, d);

        Rez[i] += vget_lane_f32(d, 0);
        p = vld1q_f32(sp_array);
        cout << setw(6) << Rez[i] << "\n";
    }
    return Rez;
}
float* NEON256(float** A, float* B, int size)  
{
    float* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(float));
    for (int i = 0; i < size; i++)
    {
        Res[i] = 0.f;
    }

    float32_t sp_array[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    float32x4_t s, p;
    s = vld1q_f32(sp_array);
    p = vld1q_f32(sp_array);

    float32x4_t* mB = (float32x4_t*)B;
    float32x4_t* mRes = (float32x4_t*)Res;

    cout << "\n\nМноження матриці на вектор за допомогою NEON 256:\n\n";

    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_f32(0.f);
        for (int j = 0; j < size / 8; j++)
        {
            s = vmulq_f32(
                vld1q_f32(&A[i][j*2]),
                mB[j*2]
            );
            s = vaddq_f32(
                s,
                vmulq_f32(
                    vld1q_f32(&A[i][j*2+4]),
                    mB[j*2+1]
                )
            );
            p = vaddq_f32(p, s);
        }
        float32x2_t d = vpadd_f32(vget_low_f32(p), vget_high_f32(p));
        d = vpadd_f32(d, d);

        Res[i] += vget_lane_f32(d, 0);

        cout << setw(6) << Res[i] << "\n";
    }
   
    return Res;
}
float* multiply_matrix_vector_NEON128(float** A, float* B, int size, float* Res2) 
{
    float32x4_t **mA, *mB, *mRes2;
    float32_t sp_array[4] = {0.f, 0.f, 0.f, 0.f};
    float32x4_t s, p;
    s = vld1q_f32(sp_array);
    p = vld1q_f32(sp_array);
    mA = (float32x4_t**)A;
    mB = (float32x4_t*)B;
    mRes2 = (float32x4_t*)Res2;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/4; j++)
        {
            s = vmulq_f32(mA[i][j], mB[j]);
            p = vaddq_f32(p, s);
        }
        float32x2_t d = vpadd_f32(vget_low_f32(p), vget_high_f32(p));
        d = vpadd_f32(d, d);

        Res2[i] += vget_lane_f32(d, 0);
        p = vld1q_f32(sp_array);
    }
    return Res2;
}
float* multiply_matrix_vector_NEON256(float** A, float* B, int size, float* Res2)
{
    float32_t sp_array[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
    float32x4_t s, p;
    s = vld1q_f32(sp_array);
    p = vld1q_f32(sp_array);

    float32x4_t* mB = (float32x4_t*)B;
    float32x4_t* mRes2 = (float32x4_t*)Res2;

    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_f32(0.f);
        for (int j = 0; j < size / 8; j++)
        {
            s = vmulq_f32(
                vld1q_f32(&A[i][j*2]),
                mB[j*2]
            );
            s = vaddq_f32(
                s,
                vmulq_f32(
                    vld1q_f32(&A[i][j*2+4]),
                    mB[j*2+1]
                )
            );
            p = vaddq_f32(p, s);
        }
        float32x2_t d =  vpadd_f32(vget_low_f32(p), vget_high_f32(p));
        d =  vpadd_f32(d, d);

        Res2[i] = vget_lane_f32(d, 0);

    }
   
    return Res2;
}
float* multiply_vector_scalar_NEON128(float* vector, float scalar, int size, float* Res1) 
{
    float32x4_t *mv , *mRes1;
    mv = (float32x4_t*)vector;
    mRes1 = (float32x4_t*)Res1;
    float32x4_t scalar_v = vdupq_n_f32(scalar);
    for (int i = 0; i < size; i += 4) 
    {
        float32x4_t vector_v = vld1q_f32(vector + i);
        vector_v = vmulq_f32(vector_v, scalar_v);
        vst1q_f32(Res1 + i, vector_v);
    }
    return Res1;
}
float* multiply_vector_scalar_NEON256(float* vector, float scalar, int size, float* Res1)
{
    float32x4x2_t *mv, *mRes1;
    mv = (float32x4x2_t*)vector;
    mRes1 = (float32x4x2_t*)Res1;
    float32x4_t scalar_v = vdupq_n_f32(scalar);
    for (int i = 0; i < size/8; i++)
    {
        float* data_ptr1 = (float*) &mv[i].val[0];
        float* data_ptr2 = (float*) &mv[i].val[1];
        float32x4_t vector_v1 = vld1q_f32(data_ptr1);
        float32x4_t vector_v2 = vld1q_f32(data_ptr2);
        vector_v1 = vmulq_f32(vector_v1, scalar_v);
        vector_v2 = vmulq_f32(vector_v2, scalar_v);
        mRes1[i].val[0] = vector_v1;
        mRes1[i].val[1] = vector_v2;
    }
    return Res1;
}
float* vectors_plus_NEON128(float* vector1, float* vector2, int size, float* Res3) 
{
    float32x4_t *mv1, *mv2, *mRes3;
    mv1 = (float32x4_t*)vector1;
    mv2 = (float32x4_t*)vector2;
    mRes3 = (float32x4_t*)Res3;
    for (int i = 0; i < size; i += 4) 
    {
        float32x4_t v1 = vld1q_f32(&vector1[i]);
        float32x4_t v2 = vld1q_f32(&vector2[i]);

        float32x4_t res = vaddq_f32(v1, v2);

        vst1q_f32(&Res3[i], res);
    }
    return Res3;
}
float* vectors_plus_NEON256(float* vector1, float* vector2, int size, float* Res3)
{
    float32x4x2_t *mv1, *mv2, *mRes3;
    mv1 = (float32x4x2_t*)vector1;
    mv2 = (float32x4x2_t*)vector2;
    mRes3 = (float32x4x2_t*)Res3;
    for (int i = 0; i < size/8; i++)
    {
        float32x4x2_t v1 = vld2q_f32(&vector1[8*i]);
        float32x4x2_t v2 = vld2q_f32(&vector2[8*i]);

        float32x4x2_t res;
        res.val[0] = vaddq_f32(v1.val[0], v2.val[0]);
        res.val[1] = vaddq_f32(v1.val[1], v2.val[1]);

        vst2q_f32(&Res3[8*i], res);
    }
    return Res3;
}
int main() 
{
    srand(time(NULL));
    int n;

   // Множення матриці на вектор

    n = 3;

    float** A1;
    A1 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A1[i], 32, n * sizeof(float));
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

    float* B1;
    posix_memalign((void**)&B1, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B1[i] = rand()%19-9;
        cout << setw(6) << B1[i] << "\n";
    }

    float* Res1;
    posix_memalign((void**)&Res1, 32, n * sizeof(float));
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

    float** A2;
    A2 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        posix_memalign((void**)&A2[i], 32, n * sizeof(float));
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

    float* B2;
    posix_memalign((void**)&B2, 32, n * sizeof(float));
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
    float** A3;
    A3 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A3[i], 32, n * sizeof(float));
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

    float* B3;
    posix_memalign((void**)&B3, 32, n * sizeof(float));
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

    float* B4;
    posix_memalign((void**)&B4, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B4[i] = rand()%19-9;
        cout << setw(6) << B4[i] << " ";
    }

    float a __attribute__((aligned(32))) = rand() % 19 - 9;
    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал:\n\n";
    float* Res4;
    posix_memalign((void**)&Res4, 32, n * sizeof(float));
    for (int i=0; i<n; i++) 
    {
        Res4[i] = 0;
        Res4[i] = B4[i] * a;
        cout << setw(6) << Res4[i] << " ";
    }

    free(B4);
    free(Res4);

    n = 4;

    float* B5;
    posix_memalign((void**)&B5, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B5[i] = rand()%19-9;
        cout << setw(6) << B5[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 128:\n\n";
    float* Res5;
    posix_memalign((void**)&Res5, 32, n * sizeof(float));
    for (int i=0; i<n; i++) Res5[i] = 0;
    multiply_vector_scalar_NEON128(B5, a, n, Res5);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res5[i] << " ";
    }

    free(B5);
    free(Res5);

    n = 8;

    float* B6;
    posix_memalign((void**)&B6, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B6[i] = rand()%19-9;
        cout << setw(6) << B6[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 256:\n\n";
    float* Res6;
    posix_memalign((void**)&Res6, 32, n * sizeof(float));
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

    float** A7;
    A7 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A7[i], 32, n * sizeof(float));
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

    float* B7;
    posix_memalign((void**)&B7, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B7[i] = rand()%19-9;
        cout << setw(6) << B7[i] << "\n";
    }

    float* Res7;
    posix_memalign((void**)&Res7, 32, n * sizeof(float));
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

    float** A8;
    A8 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A8[i], 32, n * sizeof(float));
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

    float* B8;
    posix_memalign((void**)&B8, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B8[i] = rand()%19-9;
        cout << setw(6) << B8[i] << "\n";
    }

    float* Res8;
    posix_memalign((void**)&Res8, 32, n * sizeof(float));
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

    float** A9;
    A9 = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A9[i], 32, n * sizeof(float));
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

    float* B9;
    posix_memalign((void**)&B9, 32, n * sizeof(float));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B9[i] = rand()%19-9;
        cout << setw(6) << B9[i] << "\n";
    }

    float* Res9;
    posix_memalign((void**)&Res9, 32, n * sizeof(float));
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
    
    float* A10;
    posix_memalign((void**)&A10, 32, n * sizeof(float));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A10[i] = rand()%19-9;
        cout << setw(6) << A10[i] << " ";
    }

    float* B10;
    posix_memalign((void**)&B10, 32, n * sizeof(float));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B10[i] = rand()%19-9;
        cout << setw(6) << B10[i] << " ";
    }


    float* Res10;
    posix_memalign((void**)&Res10, 32, n * sizeof(float));
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

    float* A11;
    posix_memalign((void**)&A11, 32, n * sizeof(float));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A11[i] = rand()%19-9;
        cout << setw(6) << A11[i] << " ";
    }

    float* B11;
    posix_memalign((void**)&B11, 32, n * sizeof(float));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B11[i] = rand()%19-9;
        cout << setw(6) << B11[i] << " ";
    }


    float* Res11;
    posix_memalign((void**)&Res11, 32, n * sizeof(float));
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

    float* A12;
    posix_memalign((void**)&A12, 32, n * sizeof(float));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A12[i] = rand()%19-9;
        cout << setw(6) << A12[i] << " ";
    }

    float* B12;
    posix_memalign((void**)&B12, 32, n * sizeof(float));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B12[i] = rand()%19-9;
        cout << setw(6) << B12[i] << " ";
    }

    float* Res12;
    posix_memalign((void**)&Res12, 32, n * sizeof(float));
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