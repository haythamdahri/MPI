#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int data[10] = {10,20,30,40,50,60,70,80,90,100};
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int receivedData[2];
    if( rank == 0 ){
        MPI_Gather(data, 2, MPI_INT, receivedData, 2, MPI_INT, 0, MPI_COMM_WORLD);
    }
    


    MPI_Finalize();
    return 0;
}