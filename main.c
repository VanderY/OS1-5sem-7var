#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void errorOutput() {
    printf("Process can't be created.\n");
    _exit(EXIT_FAILURE);
}

void pidAndPpidOutput(int relative_process_number) {
    printf("Process %i is created!\n"
           "ID of created process is %i.\n"
           "ID of the parent process is %i.\n"
           "--------------------\n",
           relative_process_number, getpid(), getppid());
}

void processFinishedOutput(int relative_process_number) {
    printf("Process %i with PID %i and PPID %i has finished.\n"
           "--------------------\n",
           relative_process_number, getpid(), getppid());
    _exit(EXIT_SUCCESS);
}

int main() {
//    printf("ID of the root process is %i.\n"
//           "ID of the parent process is %i.\n"
//           "--------------------\n",
//           getpid(), getppid());
    pidAndPpidOutput(1);
    pid_t pid2 = fork();
    if (pid2 < 0) {
        errorOutput();
    } else if (pid2 == 0) {
        pidAndPpidOutput(2);

        pid_t pid7 = fork();
        if(pid7 < 0) {
            errorOutput();
        } else if (pid7 == 0) {
            pidAndPpidOutput(7);

            char *binaryPath = "/bin/ps";
            char *arg1 = "aux";
            printf("Executing command ps aux: \n");
            execl(binaryPath, binaryPath, arg1, NULL);
            processFinishedOutput(7);
        } else {
            wait(NULL);
        }
        processFinishedOutput(2);
    } else {
        wait(NULL);
    }

    pid_t pid3 = fork();
    if (pid3 < 0)  {
        errorOutput();
    } else if (pid3 == 0) {
        pidAndPpidOutput(3);

        pid_t pid5 = fork();
        if(pid5 < 0) {
            errorOutput();
        } else if (pid5 == 0) {
            pidAndPpidOutput(5);
            processFinishedOutput(5);
        } else {
            wait(NULL);
        }

        pid_t pid6 = fork();
        if(pid6 < 0) {
            errorOutput();
        } else if (pid6 == 0) {
            pidAndPpidOutput(6);
            processFinishedOutput(6);
        } else {
            wait(NULL);
        }

        processFinishedOutput(3);
    } else {
        wait(NULL);
    }

    pid_t pid4 = fork();
    if(pid4 < 0) {
        errorOutput();
    } else if (pid4 == 0) {
        pidAndPpidOutput(4);
        processFinishedOutput(4);
    } else {
        wait(NULL);
    }

    processFinishedOutput(1);
}