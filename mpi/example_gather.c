#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// mpicc example_gather.c && mpiexec -np 4 ./a.out
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* in = (int*)malloc(sizeof(int) * 2);
    in[0] = rank * 2;
    in[1] = rank * 2 + 1;

    int* out = (int*)malloc(sizeof(int) * size * 2);

    // MPI_Allgather(in, 2, MPI_INT, out, 2, MPI_INT, MPI_COMM_WORLD);
    MPI_Gather(in, 2, MPI_INT, out, 2, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size * 2; ++i) {
            printf("%d ", out[i]);
        }

        printf("\n");
    }

    free(in);
    free(out);
    return MPI_Finalize();
}
