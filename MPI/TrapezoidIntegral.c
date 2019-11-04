#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const double a = 0;
const double b = 2000000000;

/* Function declarations */
void Get_input(int argc, char *argv[], int my_rank, double *n_p);
double Trap(double left_endpt, double right_endpt, int trap_count,
            double base_len);
double f(double x);

int main(int argc, char **argv)
{
    int my_rank, comm_sz, local_n;
    double n, h, local_a, local_b;
    double local_int, total_int;
    double start, finish, loc_elapsed, elapsed;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    Get_input(argc, argv, my_rank, &n); /*Read user input */

    /*Note: h and local_n are the same for all processes*/
    h = (b - a) / n;       /* length of each trapezoid */
    local_n = n / comm_sz; /* number of trapezoids per process */

    /* Length of each process' interval of integration = local_n*h. */
    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    /* Calculate each process' local integral using local endpoints*/
    local_int = Trap(local_a, local_b, local_n, h);
    finish = MPI_Wtime();
    loc_elapsed = finish - start;
    MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    /* Add up the integrals calculated by each process */
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("With n = %.0f trapezoids, our estimate\n", n);
        printf("of the integral from %.0f to %.0f = %.0f\n",
               a, b, total_int);
        printf("Elapsed time = %f milliseconds \n", elapsed * 1000);
    }

    /* Shut down MPI */
    MPI_Finalize();

    return 0;
} /*  main  */

void Get_input(int argc, char *argv[], int my_rank, double *n_p)
{
    if (my_rank == 0)
    {
        if (argc != 2)
        {
            fprintf(stderr, "usage: mpirun -np <N> %s <number of trapezoids> \n", argv[0]);
            fflush(stderr);
            *n_p = -1;
        }
        else
        {
            *n_p = atoi(argv[1]);
        }
    }
    // Broadcasts value of n to each process
    MPI_Bcast(n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // negative n ends the program
    if (*n_p <= 0)
    {
        MPI_Finalize();
        exit(-1);
    }
} /* Get_input */

* /
    double Trap(double left_endpt, double right_endpt, int trap_count, double base_len)
{
    double estimate, x;
    int i;

    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (i = 1; i <= trap_count - 1; i++)
    {
        x = left_endpt + i * base_len;
        estimate += f(x);
    }
    estimate = estimate * base_len;

    return estimate;
} /*  Trap  */

double f(double x)
{
    return x * x;
} /* f */
