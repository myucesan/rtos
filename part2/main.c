/*
 * Sender thread sends 50 integers to receiver thread using a POSIX message queue.
 * target_link_library for ptrhead and rt
 * Author: Mustafa Yucesan
 * Resources:
 * https://linux.die.net/man/7/mq_overview
 *
 *    Linking
       Programs  using  the  POSIX  message queue API must be compiled with cc
       -lrt to link against the real-time library, librt.

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>

#define mqbuffer "/myqueue"

pthread_t thread1;
pthread_t thread2;

static struct mq_attr my_mq_attr;
static mqd_t mesq;

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

    mq_close(mesq);
    mq_unlink(mqbuffer);

    exit(0);
}

int main(void) {
    pthread_attr_t attr;
    int status;

    signal(SIGINT, sig_handler);

    counter = 0;

    my_mq_attr.mq_maxmsg = 10;
    my_mq_attr.mq_msgsize = sizeof(counter);

    mesq = mq_open(mqbuffer, \
                    O_CREAT | O_RDWR | O_NONBLOCK, \
                    0666, \
                    &my_mq_attr);


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

    sig_handler(SIGINT);

    return 0;
}

void sender(void) {
    unsigned int timeout_in_nanoseconds;
    int status;

    timeout_in_nanoseconds = 1000000;


    while(1) {
        status = mq_send(mesq, (const char*)&counter, sizeof(counter), 1);
        usleep(timeout_in_nanoseconds);
    }
}


void receiver(void) {
    unsigned int exec_period_usecs;
    int status;
    int recv_counter;

    exec_period_usecs = 10000; /*in micro-seconds*/


    while(1) {
        status = mq_receive(mesq, (char*)&recv_counter, \
                            sizeof(recv_counter), NULL);

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




