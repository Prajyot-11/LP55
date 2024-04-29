#include<iostream>
#include<cuda_runtime.h>

__global__ void addvect(int *A,int *B,int *C,int n)
{
    int i= blockIdx.x *  blockDim.x + threadIdx.x;

    if(i<n)
    {
        C[i]=A[i]+B[i];
    }
}

int main()
{
    int n=100;
    int *A,*B,*C;
    int size=n*sizeof(int);

    cudaMallocHost(&A,size);
    cudaMallocHost(&B,size);
    cudaMallocHost(&C,size);

    for(int i=0;i<n;i++)
    {
        A[i]=i;
        B[i]=i*2;
    }

    int *da,*db,*dc;

    cudaMalloc(&da,size);
    cudaMalloc(&db,size);
    cudaMalloc(&dc,size);

    cudaMemcpy(da,A,size,cudaMemcpyHostToDevice);
    cudaMemcpy(db,B,size,cudaMemcpyHostToDevice);

    int blocksize=256;
    int numblock=(n+blocksize-1)/blocksize;

    addvect<<<numblock,blocksize>>>(da,db,dc,n);

    cudaMemcpy(C,dc,size,cudaMemcpyDeviceToHost);

    for(int i=0;i<10;i++)
    {
        printf("%d + %d = %d \n",A[i],B[i],C[i]);
    }

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    cudaFreeHost(A);
    cudaFreeHost(B);
    cudaFreeHost(C);

    return 0;
}