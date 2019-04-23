#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank, valeur;
    int etiquette = 99;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Saisir une valeur à envoyer vers les autres processus: ");
        scanf("%d", &valeur);
        for( int i=1; i<size; i++ ){
            MPI_Send(&valeur, 1, MPI_INT, i, etiquette, MPI_COMM_WORLD);
            printf("Je suis le processus %d. J'ai envoyé la valeur %d\n", rank, valeur);
        }
    }
    else
    {
        int recv_value;
        MPI_Recv(&recv_value, 1, MPI_INT, 0, etiquette, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Je suis le processus %d. J'ai recu la valeur %d\n", rank, recv_value);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}