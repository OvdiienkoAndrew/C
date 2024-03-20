#include <iostream>
#include <ctime>
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

    double t1 = clock();
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size/4; j++)
        {
            s = vmulq_s32(mA[i][j], mB[j]);
            p = vaddq_s32(p, s);
        }
        Rez[i] += vgetq_lane_s32(p, 0) + vgetq_lane_s32(p, 1) + vgetq_lane_s32(p, 2) + vgetq_lane_s32(p, 3);
        p = vld1q_s32(sp_array);
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 128): " << t1/CLOCKS_PER_SEC << " seconds.";
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

    double t1 = clock();
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
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 256): " << t1/CLOCKS_PER_SEC << " seconds.";
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
    int n=1000;
    srand(time(NULL));
    double t1;

    for (n = 1000; n <= 22000; n += 1000)
    {
        int **A, *B, *Res1, *Res2, *Res3, *x, *y;
        A = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) 
        {
            posix_memalign((void**)&A[i], 32, n * sizeof(int));
        }
        posix_memalign((void**)&B, 32, n * sizeof(int));
        posix_memalign((void**)&Res1, 32, n * sizeof(int));
        posix_memalign((void**)&Res2, 32, n * sizeof(int));
        posix_memalign((void**)&Res3, 32, n * sizeof(int));
        posix_memalign((void**)&x, 32, n * sizeof(int));
        posix_memalign((void**)&y, 32, n * sizeof(int));
        int a __attribute__((aligned(32))) = rand() % 19 - 9;
        

        for (int i=0; i<n; i++) for (int j=0; j<n; j++) A[i][j] = rand()%19-9;
        for (int i=0; i<n; i++) B[i] = rand()%19-9;
        for (int i=0; i<n; i++) x[i] = rand()%19-9;
        for (int i=0; i<n; i++) y[i] = rand()%19-9;
        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        cout << "\n\n" << n << "\tint\n\n";

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