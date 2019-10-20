/* 2b
 * Sender thread sends 50 integers to receiver thread using a posix pipe
 * target_link_library for ptrhead and rt
 * Author: Mustafa Yucesan
 * Resources:
 * http://man7.org/linux/man-pages/man2/pipe.2.html
 *
 *    Linking
       Programs  using  the  POSIX  message queue API must be compiled with cc
       -lrt to link against the real-time library, librt.

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

pthread_t thread1;
pthread_t thread2;

static unsigned int counter;

void sender(void);
void receiver(void);

void sig_handler(int signum) {
    if (signum != SIGINT) {
        printf("Received invalid signum = %d in sig_handler()\n", signum);
    }

    printf("Received SIGINT. Exiting Application\n");

    pthread_cancel(thread1);
    pthread_cancel(thread2);


    exit(0);
}

int main(void) {
    pthread_attr_t attr;
    int status;
    char* message = "HELLOoooooooooo";
    signal(SIGINT, sig_handler);

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024*1024);

    printf("Creating sender...\n");
    status = pthread_create(&thread1, &attr, (void*) &sender, NULL);
    if (status != 0) {
        printf("Failed to create thread1 with status = %d\n", status);
    }

    printf("Creating receiver...\n");
    status = pthread_create(&thread2, &attr, (void*) &receiver, NULL);
    if (status != 0) {
        printf("Failed to create thread2 with status = %d\n", status);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

//    sig_handler(SIGINT);

    counter = 0;

    // pipe code here start
    int pipefd[2]; // used to return two file descriptors
    pid_t cpid;
    char buf;

    if(pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork(); // creates child process which inherits same file descriptors, close all fd that you don't need for the pipe
    if(cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(cpid == 0) {
        close(pipefd[1]); // pipefd[0] is read end of the pipe

        while(read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]); // close write end of pipe
        _exit(EXIT_SUCCESS);
    } else {
        printf("%d \n", cpid);
        close(pipefd[0]); // close unused read end
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]); // EOF, all written
        wait(NULL);
        exit(EXIT_SUCCESS);
    }


    // pipe code hereend



    return 0;
}

void sender(void) {
    unsigned int timeout_in_nanoseconds;
    int status;

    timeout_in_nanoseconds = 1000000;


    while(1) {
//        status = mq_send(mesq, (const char*)&counter, sizeof(counter), 1);
        usleep(timeout_in_nanoseconds);
    }
}


void receiver(void) {
    unsigned int exec_period_usecs;
    int status;
    int recv_counter;

    exec_period_usecs = 10000; /*in micro-seconds*/


    while(1) {
//        status = mq_receive(mesq, (char*)&recv_counter, \
//                            sizeof(recv_counter), NULL);

        if (status > 0) {
            printf("Received message from sender: %d\n", recv_counter);
            counter += 1;
        }

        if(counter == 50) {
            printf("So that was 50 integers! \n");
            sig_handler(SIGINT);
        }

        usleep(exec_period_usecs);
    }
}




