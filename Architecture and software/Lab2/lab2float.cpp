#include <iostream>
#include <ctime>
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

    double t1 = clock();
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
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 128): " << t1/CLOCKS_PER_SEC << " seconds.";
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

    double t1 = clock();
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
    }
    t1 = clock() - t1;
    cout << "Time to multiplication a matrix A by a vector B (with NEON 256): " << t1/CLOCKS_PER_SEC << " seconds.";
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
    int n=1000;
    srand(time(NULL));
    double t1;

    for (n = 1000; n <= 22000; n += 1000)
    {
        float **A, *B, *Res1, *Res2, *Res3, *x, *y;
        A = (float**)malloc(n * sizeof(float*));
        for (int i = 0; i < n; i++) 
        {
            posix_memalign((void**)&A[i], 32, n * sizeof(float));
        }
        posix_memalign((void**)&B, 32, n * sizeof(float));
        posix_memalign((void**)&Res1, 32, n * sizeof(float));
        posix_memalign((void**)&Res2, 32, n * sizeof(float));
        posix_memalign((void**)&Res3, 32, n * sizeof(float));
        posix_memalign((void**)&x, 32, n * sizeof(float));
        posix_memalign((void**)&y, 32, n * sizeof(float));
        float a __attribute__((aligned(32))) = rand() % 19 - 9;
        

        for (int i=0; i<n; i++) for (int j=0; j<n; j++) A[i][j] = rand()%19-9;
        for (int i=0; i<n; i++) B[i] = rand()%19-9;
        for (int i=0; i<n; i++) x[i] = rand()%19-9;
        for (int i=0; i<n; i++) y[i] = rand()%19-9;
        for (int i=0; i<n; i++)  Res1[i] = 0;
        for (int i=0; i<n; i++)  Res2[i] = 0;
        for (int i=0; i<n; i++)  Res3[i] = 0;

        cout << "\n\n" << n << "\tfloat\n\n";

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