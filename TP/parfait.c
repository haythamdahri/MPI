#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int size, rank, nombre;
    int etiquette = 19;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if( rank == 0 ){
        printf("Saisir un nombre: ");
        scanf("%d", &nombre);
        MPI_Send(&nombre, 1, MPI_INT, 1, etiquette, MPI_COMM_WORLD);
    }else if( rank == 1 ){
        int nb, s=0;
        MPI_Recv(&nb, 1, MPI_INT, 0, etiquette, MPI_COMM_WORLD, &status);
        for( int j=1; j<(int)nb; j++ ){
            if( nb%j == 0 )
            {
                s =s+ j;
            }
        }
        if( s == nb ){
            printf("%d est un nombre parfait\n", nb);
        }else{
            printf("%d n'est pas un nombre parfait\n", nb);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}