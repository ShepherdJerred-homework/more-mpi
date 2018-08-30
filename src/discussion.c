#include <mpi.h>
#include <string.h>
#include <stdio.h>

int DEFAULT_TAG = 0;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int numberOfProcesses;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

    int pidToSendTo = (pid + 1) % numberOfProcesses;
    int pidToReceiveFrom = pid == 0 ? numberOfProcesses - 1 : pid - 1;

//    printf("pid %d is sending to %d and receiving from %d\n", pid, pidToSendTo, pidToReceiveFrom);

    char* message = "Hello!";
    MPI_Send(&message, (int) strlen(message) + 1, MPI_CHAR, pidToSendTo, DEFAULT_TAG, MPI_COMM_WORLD);

    char* receivedMessage;
    MPI_Recv(&receivedMessage, (int) strlen(message) + 1, MPI_CHAR, pidToReceiveFrom, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received a message from process %d\n", pid, pidToReceiveFrom);

    MPI_Finalize();
}
