/*
 * Sender thread sends 50 integers to receiver thread using a POSIX message queue.
 *
 * Author: Mustafa Yucesan
 * Resources:
 * https://linux.die.net/man/7/mq_overview
 */

#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>
struct mq_attr attr;
mqd_t mqdes;
char buf[4096];
unsigned int integer;
void* sender() {
    printf("Hello sender \n");

    // Setting up attribute structure of message queue

    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 4096;
    attr.mq_flags = 0;

    // Now we open a queue with the attribute structure
    mqdes = mq_open("Sender", O_RDWR | O_CREAT, 0664, &attr);

}

void* receiver() {
    printf("Hello receiver \n");

    while (mq_receive (mqdes, &buf[0], 4096, &integer) != -1)
        printf ("Received a message with integer: %d.\n", integer);
}
int main() {
    pthread_t senderT, receiverT;
    pthread_create(&senderT, NULL, sender, NULL);
    pthread_create(&receiverT, NULL, receiver, NULL);
    pthread_join(senderT, NULL);
    pthread_join(receiverT, NULL);
    return 0;
}