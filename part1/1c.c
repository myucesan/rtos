////
//// Created by myucesan on 10/18/19.
////
//
///* 1c
// * Two periodic tasks are created
// * Thread 1: 0.5 seconds period
// * Thread 2: 1.3 seconds period
// * Each thread prints thread name and period number per run
// * Resources:
// * Carnegie Mellon University: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// * Linux Ma/* 1b
// * Two periodic tasks are created
// * Thread 1: 0.5 seconds period
// * Thread 2: 1.3 seconds period
// * Each thread prints thread name and period number per run
// * Resources:
// * Carnegie Mellon University: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// * Linux Man: http://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html
// * To be able to use pthread_setaffinity you have to define _GNU_SOURCE
// *
// * http://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html
// * To be able to use pthread_setaffinity you have to define _GNU_SOURCE
// *
// * // FOR README:
// * 1. To use pthreads on ubuntu add target_link_library in cmakelists.txt
// * 2. Unit is nanoseconds: 1 ms is 1,000,000 nanoseconds
// *
// * This code has to be tested for correctness: ...
// */
//#define _GNU_SOURCE
//#include <stdio.h>
//#include <pthread.h>
//#include <sched.h>
//float counterOne = 0;
//float counterTwo = 0;
//void* taskOne() {
//    struct timespec deadline; long int period=100000L;
//    clock_gettime(CLOCK_MONOTONIC, &deadline);
//
//    while (1){
//        printf("Name: taskOne Periodnumber: %f \n", counterOne);
//        deadline.tv_nsec=deadline.tv_nsec+period;
//        if (deadline.tv_nsec>=500000000L) {
//            deadline.tv_nsec-=500000000L;
//            ++deadline.tv_sec;
//        }
//        counterOne++;
//        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
//    }
//
//
//}
//
//void* taskTwo() {
//
//    struct timespec deadline; long int period=100000L;
//    clock_gettime(CLOCK_MONOTONIC, &deadline);
//
//    while (1){
//        printf("Name: taskTwo Periodnumber: %f \n", counterTwo);
//        deadline.tv_nsec=deadline.tv_nsec+period;
//        if (deadline.tv_nsec>=1300000000L) {
//            deadline.tv_nsec-=1300000000L;
//            ++deadline.tv_sec;
//        }
//        counterTwo = counterTwo + 1;
//        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
//    }
//
//}
//
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
//    pthread_create(&task1, &tattr, taskOne, NULL);
////    pthread_join(task1, NULL);
//    pthread_create(&task2, &tattr, taskTwo, NULL);
//    pthread_join(task2, NULL);
//    return 0;
//}