////
//// Created by myucesan on 10/21/19.
////
//
///*
// * 3a: A C-program will be written that will create a binary semaphore and two pthreads that use Round-Robin Scheduling. In both threads a critical section belonging to a binary
// * sempahore. In critical section 1 (thread 1) there has to be printed "Section 1" every 1 second for 5 times. In critical section 2 (thread 2) it has to print
// * "section 2" every 1 second for 5 times.
// *
// * Resources:
// * https://www.tutorialspoint.com/mutex-vs-semaphore
// * http://www.vishalchovatiya.com/binary-semaphore-example-between-threads-in-c/
// */
//#include <stdio.h>
//#include <pthread.h>
//#include <semaphore.h>
//#include <signal.h>
//#include <stdlib.h>
//#include <unistd.h>
//
//pthread_t thread1;
//pthread_t thread2;
//sem_t sem;
//
//void sender(void *ptr);
//void receiver(void *ptr);
//void sig_handler(int signum) {
//    if (signum != SIGINT) {
//        printf("Received invalid signum = %d in sig_handler()\n", signum);
//    }
//
//    printf("Received SIGINT. Exiting Application\n");
//
//    pthread_cancel(thread1);
//    pthread_cancel(thread2);
//
//
//    exit(0);
//}
//
//int main() {
//    char *cs1 = "Section 1";
//    char *cs2 = "Section 2";
//    sem_init(&sem, 0, 0);
//    pthread_attr_t tattr;
//    pthread_attr_setschedpolicy(&tattr, SCHED_RR); // change schedule police to round robin
//    pthread_attr_init(&tattr);
//    int status;
//    signal(SIGINT, sig_handler);
//    printf("Creating sender...\n");
//    status = pthread_create(&thread1, NULL, (void*) &sender, (void *)cs1);
//    if (status != 0) {
//        printf("Failed to create thread1 with status = %d\n", status);
//    }
//
//    printf("Creating receiver...\n");
//    status = pthread_create(&thread2, NULL, (void*) &receiver, (void *)cs2);
//    if (status != 0) {
//        printf("Failed to create thread2 with status = %d\n", status);
//    }
//
//    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
//
//    sem_destroy(&sem);
//    return 0;
//}
//
//void sender(void *ptr) {
//    sleep(1);
//
//    while(1){
////        sprintf(ptrSender, "%d", counter);
////        sem_wait(&sem);
//        printf ("%s \n", (char *)ptr);
//        sem_post(&sem);
//
//
//
//    }
//}
//
//
//void receiver(void *ptr) {
//    sleep (1);
//
//    while(1){
//        sem_wait(&sem);
//        printf("%s \n", (char *)ptr);
//        sem_post(&sem);
//
//    }
//}
