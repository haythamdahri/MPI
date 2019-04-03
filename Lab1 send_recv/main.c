#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Collect the processes number and the current process rank
    int size, rank;
    int etiquette = 99;
    int number;
    MPI_Status status;
    // Initialize parallelism environment
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if( rank == 0 ){
        printf("Number of processes is %d | displayed from process %d\n",size, rank);
        number = -1;
        printf("Process %d is sending value %d to process 1.\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 1,etiquette, MPI_COMM_WORLD);
    }else if( rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, etiquette, MPI_COMM_WORLD, &status);
        printf("Process %d received the value %d from the process 0.\n", rank, number);
    }
    

    // Terminate parallelism environment
    MPI_Finalize();
    return 0;
}