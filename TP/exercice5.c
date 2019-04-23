#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int data_size = 100;
    float data[data_size], new_data[10];
    int done = 0, l;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0 && size > data_size * 2)
    {
        printf("La taille du tableau est plus grande que le nombre des processus\n");
        return 0;
    }
    else
    {
        l = data_size/size;
        for (int i = 1; i <= data_size; i++)
        {
            data[i - 1] = i;
        }
    }
    int nb=10;
    float recv_data[nb], somme = 0, moyenne  = 0;
    MPI_Scatter(&data, 10, MPI_FLOAT, &recv_data, 10, MPI_FLOAT, 0, MPI_COMM_WORLD);
    for( int i=0; i<nb; i++ ){
        somme += recv_data[i];
    }
    moyenne = somme/nb;
    MPI_Gather(&moyenne, 1, MPI_FLOAT, &new_data, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(  rank == 0 ) {
        float moyenne_tt, somme_tt = 0;
        for( int i=0; i<nb; i++ ){
            printf("new_data[%d]=%.2f\n",i,new_data[i]);
            somme_tt += new_data[i];
        }
        moyenne_tt = somme_tt / nb;
        printf("La moyenne totale: %.2f\n", moyenne_tt);
    }

    MPI_Finalize();
    return 0;
}