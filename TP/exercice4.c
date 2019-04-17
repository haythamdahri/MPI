#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(argc,argv)
int argc;
char *argv[];
{
    int done = 0, n, rank, size, i;
    double PIFIX = 3.141592653589793238462643;
    double local_pi, pi, h, somme, x;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    while (!done)
    {
	if (rank == 0) {
	    printf("Entrer le nombre des intervals: (0 pour quitter) ");
	    scanf("%d",&n);
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (n == 0) break;
  
	h   = 1.0 / (double) n;
	somme = 0.0;
	for (i = rank + 1; i <= n; i += size) {
	    x = h * ((double)i - 0.5);
	    somme += 4.0 / (1.0 + x*x);
	}
	local_pi = h * somme;
    
	MPI_Reduce(&local_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);
    
	if (rank == 0)
	    printf("pi approximative %.16f, Erreur est %.16f\n",
		   pi, fabs(pi - PIFIX));
    }
    MPI_Finalize();
    return 0;
}