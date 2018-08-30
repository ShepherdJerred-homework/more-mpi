#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int DEFAULT_TAG = 0;
int ROOT_PID = 0;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int numberOfProcesses;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

    int *myNumbers = malloc(3 * sizeof(int));

    if (pid == ROOT_PID) {
        int *numbers = malloc((size_t) numberOfProcesses * sizeof(int));

        int number;
        int process;

        // Read numbers in
        for (process = 0; process < numberOfProcesses; process++) {
//            printf("Enter a value for process %d\n", process);
            scanf("%d", &number);
            numbers[process] = number;
        }

        // Send numbers to each process
        for (process = 0; process < numberOfProcesses; process++) {
//            printf("pid %d\n", process);
            if (process == 0) {
                myNumbers = malloc(sizeof(int) * 2);
//                myNumbers[0] = numbers[0];
//                myNumbers[1] = numbers[1];
                memcpy(myNumbers, numbers, 2 * sizeof(int));
//                printf("pid %d: %d %d\n", process, myNumbers[0], myNumbers[1]);
            } else {
                if (process == numberOfProcesses - 1) {
//                    printf("going to send pid %d: %d %d\n", process, numbers[process - 1], numbers[process]);
                    MPI_Send(&numbers[process - 1], 2, MPI_INT, process, DEFAULT_TAG, MPI_COMM_WORLD);
                } else {
//                    printf("addr %p %p %p %p\n", &numbers, &numbers[process - 1], &numbers[process], &numbers[process + 1]);
//                    printf("going to send pid %d: %d %d %d\n", process, numbers[process - 1], numbers[process], numbers[process + 1]);
                    MPI_Send(&numbers[process - 1], 3, MPI_INT, process, DEFAULT_TAG, MPI_COMM_WORLD);
                }
            }
        }

        free(numbers);
    }

//    printf("pid %d is about to recv\n", pid);

    // Receive numbers
    if (pid != ROOT_PID) {
        int numberOfIntsToReceive;
        if (pid == numberOfProcesses - 1) {
            MPI_Recv(myNumbers, 2, MPI_INT, ROOT_PID, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            printf("recv pid %d: %d %d\n", pid, myNumbers[0], myNumbers[1]);

        } else {
            MPI_Recv(myNumbers, 3, MPI_INT, ROOT_PID, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            printf("recv pid %d: %d %d %d\n", pid, myNumbers[0], myNumbers[1], myNumbers[2]);
        }
//        printf("pid %d recv'd\n", pid);
    }

//    printf("pid %d is has recv'd\n", pid);

    double blurredNumber;

    // Blur numbers and send back if needed
    if (pid == ROOT_PID) {
//        printf("recv pid %d: %d %d\n", pid, myNumbers[0], myNumbers[1]);
        blurredNumber = myNumbers[0] * 2 + myNumbers[1];
    } else {
        if (pid == numberOfProcesses - 1) {
            blurredNumber = myNumbers[0] + myNumbers[1] * 2;
        } else {
            blurredNumber = myNumbers[0] + myNumbers[1] * 2 + myNumbers[2];
        }
        MPI_Send(&blurredNumber, 1, MPI_DOUBLE, ROOT_PID, DEFAULT_TAG, MPI_COMM_WORLD);
    }

//    printf("pid %d has blurred to %f\n", pid, blurredNumber);

    // Receive blurred numbers and print
    if (pid == ROOT_PID) {
        double *blurredNumbers = malloc((size_t) numberOfProcesses * sizeof(double));

        int process;
        for (process = 0; process < numberOfProcesses; process++) {
//            printf("processing blur for pid %d\n", process);
            if (process != 0) {
//                printf("waiting for pid %d\n", process);
                MPI_Recv(&blurredNumbers[process], 1, MPI_DOUBLE, process, DEFAULT_TAG, MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
            } else {
                blurredNumbers[process] = blurredNumber;

            }

        }

        for (process = 0; process < numberOfProcesses; process++) {
            printf("%f\n", blurredNumbers[process]);
        }

        free(blurredNumbers);
//        free(myNumbers);
    }

    free(myNumbers);

    MPI_Finalize();
}