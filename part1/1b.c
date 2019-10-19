////
//// Created by myucesan on 10/18/19.
////
//
///* 1b
// * There are four tasks below, which are to become pthreads. Two tasks have an infinite loop and two other tasks are finite loops. These four tasks will be scheduled with the Round Robin scheduling
// * policy. But first task 3 and 4 and when those two have finished task 1 and 2 because these are infinite. The POSIX api will be used for this.
// * Resources:
// * Carnegie Mellon University: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// * Linux Man: http://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html
// * To be able to use pthread_setaffinity you have to define _GNU_SOURCE
// *
// * // FOR README:
// * 1. To use pthreads on ubuntu add target_link_library in cmakelists.txt
// *
// * This code has to be tested for correctness: NOT DONE YET
// */
//#define _GNU_SOURCE
//#include <stdio.h>
//#include <pthread.h>
//#include <sched.h>
//
//void* taskOne() {
//    int i, j, m, n;
//
//    while(1) {
//        for(i=0;i<5;i++) {
//            for(j=1;j<=8;j++) {
//                printf("taak 1 %i \n", j);
//                for(m=0;m<=1000;m++) {
//                    for(n=0;n<=10000;m++) {
//                        // This code is meant to cause delay for a pre-emptive context switch to be possible
//                    }
//                }
//            }
//        }
//    }
//}
//
//void* taskTwo() {
//    int i, j, m, n;
//
//    while(1) {
//        for(i=0;i<5;i++) {
//            for(j=1;j<=8;j++) {
//                printf("taak 2 %i \n", j);
//                for(m=0;m<=1000;m++) {
//                    for(n=0;n<=10000;m++) {
//                        // This code is meant to cause delay for a pre-emptive context switch to be possible
//                    }
//                }
//            }
//        }
//    }
//}
//
//void* taskThree() {
//    int i, j, m, n;
//
//    for(i=0;i<5;i++) {
//        for(j=1;j<=8;j++) {
//            printf("taak 3 %i \n", j);
//            for(m=0;m<=1000;m++) {
//                for(n=0;n<=10000;m++) {
//                    // This code is meant to cause delay for a pre-emptive context switch to be possible
//                }
//            }
//        }
//    }
//}
//
//void* taskFour() {
//    int i, j, m, n;
//
//    for(i=0;i<5;i++) {
//        for(j=1;j<=8;j++) {
//            printf("taak 4 %d \n", j);
//            for(m=0;m<=1000;m++) {
//                for(n=0;n<=10000;m++) {
//                    // This code is meant to cause delay for a pre-emptive context switch too be possible
//                }
//            }
//        }
//    }
//}
//
//int main() {
//    pthread_t task1, task2, task3, task4;
//    pthread_t thread;
//    thread = pthread_self();
//    pthread_attr_t tattr;
//    pthread_attr_init(&tattr);
//    cpu_set_t cpuset; // represents a set of CPU's
//    CPU_ZERO(&cpuset); // empties cpu set
//    pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset); // sets the affinity to itself so new threads will be appointed to calling core
//    struct sched_param param;
//    pthread_attr_getschedparam (&tattr, &param);
//    param.__sched_priority = 1;
//    pthread_attr_setschedparam (&tattr, &param);
//    pthread_attr_setschedpolicy(&tattr, SCHED_RR); // change schedule police to round robin
//    pthread_create(&task3, &tattr, taskThree, NULL);
//    pthread_create(&task4, &tattr, taskFour, NULL);
//    pthread_attr_getschedparam (&tattr, &param);
//    param.__sched_priority = 2;
//    pthread_attr_setschedparam (&tattr, &param);
//    pthread_join(task3, NULL);
//    pthread_join(task4, NULL);
//    pthread_create(&task1, &tattr, taskOne, NULL);
//    pthread_create(&task2, &tattr, taskTwo, NULL);
//
//
//    printf("Hello, World!\n");
//    return 0;
//}