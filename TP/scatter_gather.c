#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    int size, rank;
    int data[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int received_data[10];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int recv_data;
    MPI_Scatter(&data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process: %d | Data: %d\n", rank, recv_data);
    int new_send_data = recv_data * 2;
    int dt;
    MPI_Gather(&new_send_data, 1, MPI_INT, &received_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for( int i=0; i<10; i++ ) {
            printf("Data: %d\n", received_data[i]);
        }
    }
    MPI_Finalize();
    return 0;
}