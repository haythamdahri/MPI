#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init (&argc, &argv); //initialize MPI library

    MPI_Comm_size(MPI_COMM_WORLD, &size); //get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get my process id

    //Number of processes
    printf("There is %d process\n",size);

    //do something
    printf("Hello World from rank %d\n", rank);
    for( int i=0; i<size; i++ ){
        printf("MPI World size = %d processes\n", size);
    }
    
    MPI_Finalize(); //MPI cleanup
    return 0;
}