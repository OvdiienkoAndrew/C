#include <iostream>
#include <iomanip>
#include <arm_neon.h>
using namespace std;
int* NEON128(int** A, int* B, int size)  
{
    int* Rez;
    posix_memalign((void**)&Rez, 16, size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        Rez[i] = 0;
    }

    int32x4_t **mA, *mB, *mRez;
    int32_t sp_array[4] = {0,0,0,0};
    int32x4_t s, p;
    s = vld1q_s32(sp_array);
    p = vld1q_s32(sp_array);

    mA = (int32x4_t**)A;
    mB = (int32x4_t*)B;
    mRez = (int32x4_t*)Rez;

    cout << "\n\nМноження матриці на вектор за допомогою NEON 128:\n\n";
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/4; j++)
        {
            s = vmulq_s32(mA[i][j], mB[j]);
            p = vaddq_s32(p, s);
        }
        Rez[i] += vgetq_lane_s32(p, 0) + vgetq_lane_s32(p, 1) + vgetq_lane_s32(p, 2) + vgetq_lane_s32(p, 3);
        p = vld1q_s32(sp_array);
        cout << setw(6) << Rez[i] << "\n";
    }
    return Rez;
}
int* NEON256(int** A, int* B, int size)  
{
    int* Res;
    posix_memalign((void**)&Res, 32, size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        Res[i] = 0;
    }

    int32_t sp_array[8] = {0,0,0,0,0,0,0,0};
    int32x4_t s, p;
    s = vld1q_s32(sp_array);
    p = vld1q_s32(sp_array);

    int32x4_t* mB = (int32x4_t*)B;
    int32x4_t* mRes = (int32x4_t*)Res;

    cout << "\n\nМноження матриці на вектор за допомогою NEON 256:\n\n";

    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_s32(0);
        for (int j = 0; j < size / 8; j++)
        {
            s = vmulq_s32(
                vld1q_s32(&A[i][j*2]),
                mB[j*2]
            );
            s = vaddq_s32(
                s,
                vmulq_s32(
                    vld1q_s32(&A[i][j*2+4]),
                    mB[j*2+1]
                )
            );
            p = vaddq_s32(p, s);
        }
        p = vaddq_s32(p, vrev64q_s32(p));
        p = vaddq_s32(p, vcombine_s32(vget_high_s32(p), vget_low_s32(p)));
        int sum = vgetq_lane_s32(p, 0);

        Res[i] = sum;

        cout << setw(6) << Res[i] << "\n";
    }
   
    return Res;
}
int* multiply_vector_scalar_NEON256(int* vector, int scalar, int size, int* Res1)
{
    int32x4x2_t *mv, *mRes1;
    mv = (int32x4x2_t*)vector;
    mRes1 = (int32x4x2_t*)Res1;
    int32x4_t scalar_v = vdupq_n_s32(scalar);
    for (int i = 0; i < size/8; i++)
    {
        int32_t* data_ptr1 = (int32_t*) &mv[i].val[0];
        int32_t* data_ptr2 = (int32_t*) &mv[i].val[1];
        int32x4_t vector_v1 = vld1q_s32(data_ptr1);
        int32x4_t vector_v2 = vld1q_s32(data_ptr2);
        vector_v1 = vmulq_s32(vector_v1, scalar_v);
        vector_v2 = vmulq_s32(vector_v2, scalar_v);
        mRes1[i].val[0] = vector_v1;
        mRes1[i].val[1] = vector_v2;
    }
    return Res1;
}
int* multiply_vector_scalar_NEON128(int* vector, int scalar, int size, int* Res1) 
{
    int32x4_t *mv , *mRes1;
    mv = (int32x4_t*)vector;
    mRes1 = (int32x4_t*)Res1;
    int32x4_t scalar_v = vdupq_n_s32(scalar);
    for (int i = 0; i < size; i += 4) 
    {
        int32x4_t vector_v = vld1q_s32(vector + i);
        vector_v = vmulq_s32(vector_v, scalar_v);
        vst1q_s32(Res1 + i, vector_v);
    }
    return Res1;
}
int* multiply_matrix_vector_NEON128(int** A, int* B, int size, int* Res2) 
{
    int32x4_t **mA, *mB, *mRes2;
    int32_t sp_array[4] = {0,0,0,0};
    int32x4_t s, p;
    s = vld1q_s32(sp_array);
    p = vld1q_s32(sp_array);
    mA = (int32x4_t**)A;
    mB = (int32x4_t*)B;
    mRes2 = (int32x4_t*)Res2;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/4; j++)
        {
            s = vmulq_s32(mA[i][j], mB[j]);
            p = vaddq_s32(p, s);
        }
        Res2[i] += vgetq_lane_s32(p, 0) + vgetq_lane_s32(p, 1) + vgetq_lane_s32(p, 2) + vgetq_lane_s32(p, 3);
        p = vld1q_s32(sp_array);
    }
    return Res2;
}
int* multiply_matrix_vector_NEON256(int** A, int* B, int size, int* Res2)
{
   int32_t sp_array[8] = {0,0,0,0,0,0,0,0};
    int32x4_t s, p;
    s = vld1q_s32(sp_array);
    p = vld1q_s32(sp_array);

    int32x4_t* mB = (int32x4_t*)B;
    int32x4_t* mRes2 = (int32x4_t*)Res2;

    for (int i = 0; i < size; i++)
    {
        p = vdupq_n_s32(0);
        for (int j = 0; j < size / 8; j++)
        {
            s = vmulq_s32(
                vld1q_s32(&A[i][j*2]),
                mB[j*2]
            );
            s = vaddq_s32(
                s,
                vmulq_s32(
                    vld1q_s32(&A[i][j*2+4]),
                    mB[j*2+1]
                )
            );
            p = vaddq_s32(p, s);
        }
        p = vaddq_s32(p, vrev64q_s32(p));
        p = vaddq_s32(p, vcombine_s32(vget_high_s32(p), vget_low_s32(p)));
        int sum = vgetq_lane_s32(p, 0);

        Res2[i] = sum;

    }
   
    return Res2;
}
int* vectors_plus_NEON128(int* vector1, int* vector2, int size, int* Res3) 
{
    int32x4_t *mv1, *mv2, *mRes3;
    mv1 = (int32x4_t*)vector1;
    mv2 = (int32x4_t*)vector2;
    mRes3 = (int32x4_t*)Res3;
    for (int i = 0; i < size; i += 4) 
    {
        int32x4_t v1 = vld1q_s32(&vector1[i]);
        int32x4_t v2 = vld1q_s32(&vector2[i]);

        int32x4_t res = vaddq_s32(v1, v2);

        vst1q_s32(&Res3[i], res);
    }
    return Res3;
}
int* vectors_plus_NEON256(int* vector1, int* vector2, int size, int* Res3)
{
    int32x4x2_t *mv1, *mv2, *mRes3;
    mv1 = (int32x4x2_t*)vector1;
    mv2 = (int32x4x2_t*)vector2;
    mRes3 = (int32x4x2_t*)Res3;
    for (int i = 0; i < size/8; i++)
    {
        int32x4x2_t v1 = vld2q_s32(&vector1[8*i]);
        int32x4x2_t v2 = vld2q_s32(&vector2[8*i]);

        int32x4x2_t res;
        res.val[0] = vaddq_s32(v1.val[0], v2.val[0]);
        res.val[1] = vaddq_s32(v1.val[1], v2.val[1]);

        vst2q_s32(&Res3[8*i], res);
    }
    return Res3;
}
int main() 
{
    srand(time(NULL));
    int n;

    // Множення матриці на вектор

    n = 3;

    int** A1;
    A1 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A1[i], 32, n * sizeof(int));
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

    int* B1;
    posix_memalign((void**)&B1, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B1[i] = rand()%19-9;
        cout << setw(6) << B1[i] << "\n";
    }

    int* Res1;
    posix_memalign((void**)&Res1, 32, n * sizeof(int));
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

    int** A2;
    A2 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        posix_memalign((void**)&A2[i], 32, n * sizeof(int));
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

    int* B2;
    posix_memalign((void**)&B2, 32, n * sizeof(int));
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
    int** A3;
    A3 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) 
    {
        posix_memalign((void**)&A3[i], 32, n * sizeof(int));
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

    int* B3;
    posix_memalign((void**)&B3, 32, n * sizeof(int));
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

    int* B4;
    posix_memalign((void**)&B4, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B4[i] = rand()%19-9;
        cout << setw(6) << B4[i] << " ";
    }

    int a __attribute__((aligned(32))) = rand() % 19 - 9;
    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал:\n\n";
    int* Res4;
    posix_memalign((void**)&Res4, 32, n * sizeof(int));
    for (int i=0; i<n; i++) 
    {
        Res4[i] = 0;
        Res4[i] = B4[i] * a;
        cout << setw(6) << Res4[i] << " ";
    }

    free(B4);
    free(Res4);

    n = 4;

    int* B5;
    posix_memalign((void**)&B5, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B5[i] = rand()%19-9;
        cout << setw(6) << B5[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 128:\n\n";
    int* Res5;
    posix_memalign((void**)&Res5, 32, n * sizeof(int));
    for (int i=0; i<n; i++) Res5[i] = 0;
    multiply_vector_scalar_NEON128(B5, a, n, Res5);
    for (int i=0; i<n; i++) 
    {
        cout << setw(6) << Res5[i] << " ";
    }

    free(B5);
    free(Res5);

    n = 8;

    int* B6;
    posix_memalign((void**)&B6, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B6[i] = rand()%19-9;
        cout << setw(6) << B6[i] << " ";
    }

    cout << "\n\nCакрал: " << a << "\n\nМноження вектора на сакрал за допомогою NEON 256:\n\n";
    int* Res6;
    posix_memalign((void**)&Res6, 32, n * sizeof(int));
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

    int** A7;
    A7 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A7[i], 32, n * sizeof(int));
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

    int* B7;
    posix_memalign((void**)&B7, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B7[i] = rand()%19-9;
        cout << setw(6) << B7[i] << "\n";
    }

    int* Res7;
    posix_memalign((void**)&Res7, 32, n * sizeof(int));
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

    int** A8;
    A8 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A8[i], 32, n * sizeof(int));
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

    int* B8;
    posix_memalign((void**)&B8, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B8[i] = rand()%19-9;
        cout << setw(6) << B8[i] << "\n";
    }

    int* Res8;
    posix_memalign((void**)&Res8, 32, n * sizeof(int));
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

    int** A9;
    A9 = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        posix_memalign((void**)&A9[i], 32, n * sizeof(int));
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

    int* B9;
    posix_memalign((void**)&B9, 32, n * sizeof(int));
    cout << "\n\nВектор:\n\n";
    for (int i=0; i<n; i++) 
    {
        B9[i] = rand()%19-9;
        cout << setw(6) << B9[i] << "\n";
    }

    int* Res9;
    posix_memalign((void**)&Res9, 32, n * sizeof(int));
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

    int* A10;
    posix_memalign((void**)&A10, 32, n * sizeof(int));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A10[i] = rand()%19-9;
        cout << setw(6) << A10[i] << " ";
    }

    int* B10;
    posix_memalign((void**)&B10, 32, n * sizeof(int));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B10[i] = rand()%19-9;
        cout << setw(6) << B10[i] << " ";
    }

    int* Res10;
    posix_memalign((void**)&Res10, 32, n * sizeof(int));
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

    int* A11;
    posix_memalign((void**)&A11, 32, n * sizeof(int));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A11[i] = rand()%19-9;
        cout << setw(6) << A11[i] << " ";
    }

    int* B11;
    posix_memalign((void**)&B11, 32, n * sizeof(int));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B11[i] = rand()%19-9;
        cout << setw(6) << B11[i] << " ";
    }

    int* Res11;
    posix_memalign((void**)&Res11, 32, n * sizeof(int));
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

    int* A12;
    posix_memalign((void**)&A12, 32, n * sizeof(int));
    cout << "\n\nВектор(1):\n\n";
    for (int i=0; i<n; i++) 
    {
        A12[i] = rand()%19-9;
        cout << setw(6) << A12[i] << " ";
    }

    int* B12;
    posix_memalign((void**)&B12, 32, n * sizeof(int));
    cout << "\n\nВектор(2):\n\n";
    for (int i=0; i<n; i++) 
    {
        B12[i] = rand()%19-9;
        cout << setw(6) << B12[i] << " ";
    }


    int* Res12;
    posix_memalign((void**)&Res12, 32, n * sizeof(int));
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