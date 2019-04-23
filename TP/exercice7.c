#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int nb=4,vecteur[nb], matrice[nb][nb], vecteur_res[nb];
    int rank ,size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if( rank == 0 ) {
        for( int i=0; i<nb; i++ ) {
            vecteur[i] = i+2;
            printf("----------------------------------------\n");
            printf("vecteru[%d]=%d\n",i,vecteur[i]);
            for( int j=0; j<nb; j++ ){
                matrice[i][j] = i + j + 2;
                printf("matrice[%d][%d]=%d\n",i,j,matrice[i][j]);
            }
            printf("----------------------------------------\n");
        }
    }

    int nombre, vecteur_recu[nb], new_vecteur[nb], somme=0;

    MPI_Scatter(&vecteur, 1, MPI_INT, &nombre, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&matrice[rank], MPI_INT, &vecteur_recu, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for( int i=0; i<nb; i++ ){
        //printf("vecteur_recu[%d]=%d\n\n",i,vecteur_recu[i]);
        somme += nombre * vecteur_recu[i];
    }
    new_vecteur[rank] = somme;

    MPI_Gather(&new_vecteur, 1, MPI_INT, &vecteur_res, nb, MPI_INT, 0, MPI_COMM_WORLD);

    if( rank == 0 ){
        for( int i=0; i<nb; i++ ){
            printf("vecteur_res[%d]=%d\n", i, vecteur_res[i]);
        }
    } 



    MPI_Finalize();
    return 0;

}
