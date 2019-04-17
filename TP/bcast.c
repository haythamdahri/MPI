#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;
    int data = 20;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //MPI_Barrier(MPI_COMM_WORLD);

    if( rank == 0 ) {
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        int new_data;
        MPI_Bcast(&new_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Hello i am process %d and i received %d\n", rank, new_data);
    }

    MPI_Finalize();
    return 0;
}