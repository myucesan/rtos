////
//// Created by myucesan on 10/21/19.
////
//
///* 2b
// * Sender thread sends 50 integers to receiver thread using a posix pipe
// * target_link_library for ptrhead and rt
// * Author: Mustafa Yucesan
// * Resources:
// * http://man7.org/linux/man-pages/man2/pipe.2.html
// *
// *    Linking
//       Programs  using  the  POSIX  message queue API must be compiled with cc
//       -lrt to link against the real-time library, librt.
//
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <pthread.h>
//#include <signal.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/wait.h>
//
//pthread_t thread1;
//pthread_t thread2;
//
//static unsigned int counter;
//
//void sender(void);
//void receiver(void);
//
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
//int pipefd[2]; // used to return two file descriptors
//
//int main(void) {
//    int status;
//    counter = 0;
//    signal(SIGINT, sig_handler);
//
//    if(pipe(pipefd) == -1) {
//        perror("pipe");
//        exit(EXIT_FAILURE);
//    }
//
//
//    printf("Creating sender...\n");
//    status = pthread_create(&thread1, NULL, (void*) &sender, NULL);
//    if (status != 0) {
//        printf("Failed to create thread1 with status = %d\n", status);
//    }
//
//    printf("Creating receiver...\n");
//    status = pthread_create(&thread2, NULL, (void*) &receiver, NULL);
//    if (status != 0) {
//        printf("Failed to create thread2 with status = %d\n", status);
//    }
//
//    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
//
//    sig_handler(SIGINT);
//
//
//    return 0;
//}
//
//void sender(void) {
//    int     result;
//    int     count = 0;
//
//    while(1){
//
//        result = write (pipefd[1], &count,1);
//        if (result != 1){
//            perror ("send");
//            exit (2);
//        }
//
//        printf ("sender: %d\n", count++);
//
//        if(count == 50) {
//            sig_handler(SIGINT);
//        }
//
//    }
//}
//
//
//void receiver(void) {
//    int     count = 0;
//    sleep (25);
//
//    while(1){
//        char    ch;
//        int     result;
//
//        result = read (pipefd[0],&ch,1);
//        if (result != 1) {
//            perror("receive");
//            exit(3);
//        } printf ("Receiver: %d %c\n",++count,ch);
//    }
//}
//
//
//
//
