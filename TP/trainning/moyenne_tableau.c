#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int calculerMoyenneReel(float arg_data[10], int noElements)
{
    int somme = 0;
    for (int i = 0; i < noElements; i++)
    {
        somme += arg_data[i];
    }
    float moyenne = somme / noElements;
    return moyenne;
}
int calculerSomme(int arg_data[], int noElements)
{
    int somme = 0;
    for (int i = 0; i < noElements; i++)
    {
        somme += arg_data[i];
    }
    return somme;
}
float calculerMoyenne(int arg_data[], int noElements)
{
    float somme = calculerSomme(arg_data, noElements);
    float moyenne = somme / noElements;
    return moyenne;
}
void afficherTableau(float arg_data[], int noElements)
{
    for (int i = 0; i < noElements; i++)
    {
        printf("arg_data[%d]=%.2f\n", i, arg_data[i]);
    }
}

int main(int argc, char *argv[])
{
    int rank, size;
    int data_size = 100, send_count = 10, recv_count = 10, noElements = 100;
    float moyenne_total = 0;
    int somme_totale = 0;
    int data[data_size];
    float new_data[data_size / 10];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        if (size > 10 || size < 10)
        {
            printf("Le nombre de processus est plus grand que la taille du tableau\n");
            return 0;
        }
        else
        {
            send_count = noElements / size;
            recv_count = send_count;
            for (int i = 0; i < noElements; i++)
            {
                data[i] = i + 1;
            }
        }
    }
    // Recevoir la partie des elements du tableau selon le nombre du processus pour calculer sa moyenne
    // ex: 10 processus => 10 elements par processus (100 elements au tableau / 10 = 10 elements)
    int recv_data[recv_count];
    // MPI_Scatter permet d'envoyer un partie de tableau par un procesus qui 0 dans le cas
    MPI_Scatter(&data, send_count, MPI_INT, &recv_data, recv_count, MPI_INT, 0, MPI_COMM_WORLD);
    int somme = calculerSomme(recv_data, recv_count);
    float moyenne = calculerMoyenne(recv_data, recv_count);
    //MPI_Gather permet de recuperer la moyenne calculer par chaque processus et la envoyée vers le procuessus maitre
    MPI_Gather(&moyenne, 1, MPI_FLOAT, new_data, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&somme, &somme_totale, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        afficherTableau(new_data, send_count);
        moyenne_total = somme_totale / send_count;
        printf("La somme totale! %d\n", somme_totale);
        printf("La moyenne totale totale! %f\n", moyenne_total);
    }

    MPI_Finalize();
    return 0;
}