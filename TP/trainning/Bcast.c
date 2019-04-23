#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank, cast_value;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Saisir une valeur à diffuser: ");
        scanf("%d", &cast_value);
        MPI_Bcast(&cast_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Je suis le processus du rang %d. J'ai envoyé la valeur du cast %d\n", rank, cast_value);
    }
    else
    {
        int recv_value;
        MPI_Bcast(&recv_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Je suis le processus du rang %d. J'ai recu la valeur du cast %d\n", rank, recv_value);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}