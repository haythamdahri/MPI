#include <mpi.h>
#include <stdio.h>

// This program send a message from process 0 to all other processes

int main(int argc, char *argv[])
{
    int size, rank;
    char message[200] = "Hello, this is a message";
    int etiquette = 99;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if( rank == 0 ){
        MPI_Bcast(&message, 200, MPI_CHAR, 0, MPI_COMM_WORLD);
    }else{
        char received_message[200];
        MPI_Recv(&received_message, 200, MPI_CHAR, 0,etiquette, MPI_COMM_WORLD, &status); 
        //printf("Received message from 0 to %d is %s", rank, received_message);
    }

    MPI_Finalize();
    return 0;
}