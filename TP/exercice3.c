#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size, nombre;
    int etiquette = 99;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if( rank == 0 ) {
        printf("Saisir un nombre: ");
        scanf("%d", &nombre);
        MPI_Send(&nombre, 1, MPI_INT, 1, etiquette, MPI_COMM_WORLD);
    } else if( rank == 1 ) {
        int nb;
        int somme = 0;
        MPI_Recv(&nb, 1, MPI_INT, 0, etiquette, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for( int i=1 ; i < nb; i++ ){
            if( nb % i == 0 ) {
                somme += i;
            }
        }
        if( somme == nb ) {
            printf("%d est un nombre parfait.\n", nb);
        } else {
            printf("%d n'est pas un nombre parfat.\n", nb);
        }
    }


    MPI_Finalize();
    return 0;

}