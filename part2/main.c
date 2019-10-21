/* 2c
 * Sender thread sends 50 integers to receiver thread using a posix shared memory
 * target_link_library for ptrhead and rt
 * Author: Mustafa Yucesan
 * Resources:
 * https://www.geeksforgeeks.org/posix-shared-memory-api/
 * http://manpages.ubuntu.com/manpages/xenial/man3/shm_open.3.html
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
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

pthread_t thread1;
pthread_t thread2;
const int SIZE = 4096;
const char* name = "T1T2";
int shm_fd; // file descriptor for shared memory
void* ptrSender; // pointer to shared memory object
void* ptrReceiver;
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

    int status;
    counter = 0;
    signal(SIGINT, sig_handler);
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); // creating shared memory object
    ftruncate(shm_fd, SIZE); // size configured for shared memory object
    ptrSender = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); // memory map to shared memory object
    ptrReceiver = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);




    printf("Creating sender...\n");
    status = pthread_create(&thread1, NULL, (void*) &sender, NULL);
    if (status != 0) {
        printf("Failed to create thread1 with status = %d\n", status);
    }

    printf("Creating receiver...\n");
    status = pthread_create(&thread2, NULL, (void*) &receiver, NULL);
    if (status != 0) {
        printf("Failed to create thread2 with status = %d\n", status);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sig_handler(SIGINT);


    return 0;
}

void sender(void) {
    int     count = 0;

    while(1){
        sprintf(ptrSender, "%d", counter);

        printf ("sender: %d\n", ++count);
        if(count == 50) {
            sig_handler(SIGINT);
        }


    }
}


void receiver(void) {
    sleep (25);
    int count = 0;

    while(1){
        count++;
        printf ("Receiver: %d %c\n",counter);

    }
}




