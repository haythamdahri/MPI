#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int nb = 20, vecteur1[nb], vecteur2[nb], vecteur3[nb], rank ,size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if( rank == 0 ) {
        if( size != nb ) {
            printf("Le nombre de processus n'est pas équivalent à la taille du tableau!\n");
            return 0;
        }
        for( int i=0; i<nb; i++ ) {
            vecteur1[i] = i+2;
            vecteur2[i] = i+4;
        }
    } 
    int nb1, nb2, multi;
    MPI_Scatter(&vecteur1, 1, MPI_INT, &nb1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&vecteur2, 1, MPI_INT, &nb2, 1, MPI_INT, 0, MPI_COMM_WORLD);
    multi = nb1*nb2;
    MPI_Gather(&multi, 1, MPI_INT, &vecteur3, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if( rank == 0 ){
        int somme = 0;
        for( int i=0; i<nb; i++ ){
            printf("%d * %d = %d\n",vecteur1[i],vecteur2[i],vecteur3[i]);
            somme += vecteur3[i];
        }
        printf("Somme=%d", somme);
    }

    MPI_Finalize();
    return 0;
}