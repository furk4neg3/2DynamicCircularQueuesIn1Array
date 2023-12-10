#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int array[20];
int rear1 = 0, front1 = 0, queueLast1 = 0, queueFirst2 = 10, capacity1 = 0, capacity2 = 0, front2 = 10, rear2 = 10, queueLast2 = 10; 
//Necessary variables gets created


void enqueue1(int value) {//Enqueue function for first queue
    if (capacity1 == 0) {//If the capacity is 0, queue is empty so it should get created first
        if (queueFirst2 > 1) {//Checks if there's space for creating the queue
            array[++rear1] = value;
            queueLast1++;
            capacity1 = 2;//If there is enough space to create the first queue, it gets created
            printf("%d\tis inserted to queue\tFIRST\n", value);
            return;
        }
        else {
            printf("Queue\tFIRST\tis full\n");//If there's no space, warning occurs
            return;
        }
    }
    if ((rear1 + 1) % capacity1 == front1) {//checks if rear is at the end of the queue
        if (rear1 == queueLast1) {//checks if rear is at the end of the capacity
            if (queueLast1 + 1 != queueFirst2) {//If the next item is available for insertion
                capacity1++;
                rear1 = ++queueLast1;
                array[rear1] = value;//If there's space to add elements to first queue, capacity increases
                printf("%d\tis inserted to queue\tFIRST\n", value);
                return;
            }
            printf("Queue\tFIRST\tis full\n");
            return;
        }
        else {
            printf("Queue\tFIRST\tis full\n");
            return;
        }
        return;
    }

    rear1 = (rear1 + 1) % capacity1;
    array[rear1] = value;//When the other ifs don't satisfy, it's just a normal circular queue, so code is the same as it
    printf("%d\tis inserted to queue\tFIRST\n", value);
}

void dequeue1() {//Dequeue function for first queue

    if (front1 == rear1) {
        printf("Queue\tFIRST\tis empty\n");
        return;
    }

    front1 = (front1 + 1) % capacity1;
    printf("%d\tis deleted from queue\tFIRST\n", array[front1]);

    if (front1 == rear1) {//If queue gets empty reset the values so the other queue can use free elements
        rear1 = 0;
        front1 = 0;
        queueLast1 = 0;
        capacity1 = 0;
    }
}

void print1() {//Print function for first queue
    if (capacity1 == 0) {
        printf("QUEUE:FIRST\tFRONT:%d\tREAR:%d\tSIZE:%d\n", front1, rear1, capacity1);
        printf("NO_CONTENT\n");
        return;
    }

    int i = front1;//Variable to travel around the first queue's elements
    int realCap1 = 0;//Variable to store number of first queue's meaningful values

    do {
        realCap1++;
        i = (i + 1) % capacity1;
    } while (i != (rear1 + 1) % capacity1);//From front to end (travel the whole list) count number of items 

    printf("QUEUE:FIRST\tFRONT:%d\tREAR:%d\tSIZE:%d\n", front1, rear1, realCap1 - 1);

    i = (front1 + 1) % capacity1;//Starting from the second element of the queue which is the first meaningful value because no value gets stored in front value of circular queue
    do {
        printf("%d\t", array[i]);
        i = (i + 1) % capacity1;
    } while (i != (rear1 + 1) % capacity1);//Print every item of the queue
    printf("\n");
}

void enqueue2(int value) {//Enqueue function for second queue
    if (capacity2 == 0) {//If the capacity is 0, queue is empty so it should get created first
        if (queueFirst2 < 19) {//If there's enough space to create the queue
            front2 = queueFirst2;
            rear2 = queueFirst2 + 1;
            array[rear2] = value;
            capacity2 = 2;
            queueLast2 = rear2;
            printf("%d\tis inserted to queue\tSECOND\n", value);
            return;//Queue gets created
        }
        else {
            printf("Queue\tSECOND\tis full\n");
            return;
        }
    }
    if ((queueFirst2 + (rear2 - queueFirst2 + 1) % capacity2 ) == front2) {//Because of first queue does not start from the first element, formula of traveling around the queue is different
        //That formula substracts first index of second queue from rear value so getting moderation with capacity works correctly, then it adds first value again so index value of rear gets corrected
        //And it checks if rear is at the end of the queue
        if (rear2 == queueLast2) {//If it is at the end of the capacity
            if (queueLast2 < 19) {//If there's space after the last value
                capacity2++;
                rear2 = ++queueLast2;
                array[rear2] = value;
                printf("%d\tis inserted to queue\tSECOND\n", value);
                return;//Next item gets added to queue
            }
            else if (queueFirst2 - 1 != queueLast1) {//If rear is at the end but there's no space after the queue and there's space before the queue which is originally first queue's space
                array[front2 - 1] = value;///New item should get added right before the front so order does not change
                capacity2++;
                rear2 = front2 - 1;
                queueFirst2--;
                printf("%d\tis inserted to queue\tSECOND\n", value);
                return;
            }
            printf("Queue\tSECOND\tis full\n");
            return;
        }
        else if (queueFirst2 - 1 != queueLast1) {
            for (int i = 0; i < front2 - queueFirst2; i++) {
                array[queueFirst2 - 1 + i] = array[queueFirst2 + i];
            }//New item should get added right before the front so every item before front moves to one index left
            array[front2 - 1] = value;//New item gets added right before the front and because of moving the other items no value has been lost neither the order of the queue changed
            capacity2++;
            rear2 = front2 - 1;
            queueFirst2--;
            printf("%d\tis inserted to queue\tSECOND\n", value);
            return;
        }
        else {
            printf("Queue\tSECOND\tis full\n");
            return;
        }
        return;
    }

    rear2 = queueFirst2 + (rear2 - queueFirst2 + 1) % capacity2;
    array[rear2] = value;//When the other ifs don't satisfy, it's just a normal circular queue, so code is the same as it
    printf("%d\tis inserted to queue\tSECOND\n", value);
}

void dequeue2() {//Dequeue function for second queue

    if (rear2 == front2) {
        printf("Queue\tSECOND\tis empty\n");
        return;
    }
    
    front2 = queueFirst2 + (front2 - queueFirst2 + 1) % capacity2;
    printf("%d\tis deleted from queue\tSECOND\n", array[front2]);

    if (front2 == rear2) {//If queue gets empty 
        queueFirst2++;//First variable moves to next location so the other queue can use the free location
        rear2 = queueFirst2;
        front2 = queueFirst2;
        queueLast2 = queueFirst2;//Then the other values gets assigned respect to first variable
        capacity2 = 0;
    }

}

void print2() {//Print function for second queue
    if (capacity2 == 0) {
        printf("QUEUE:SECOND\tFRONT:%d\tREAR:%d\tSIZE:%d\n", front2, rear2, capacity2);
        printf("NO_CONTENT\n");
        return;
    }

    int i = front2;//Variable to travel around the second queue's elements
    int realCap2 = 0;//Variable to store number of second queue's meaningful values

    do {
        realCap2++;
        i = queueFirst2 + (i - queueFirst2 + 1) % capacity2;
    } while (i != queueFirst2 + (rear2 - queueFirst2 + 1) % capacity2);//From front to end (travel the whole list) count number of items 

    printf("QUEUE:SECOND\tFRONT:%d\tREAR:%d\tSIZE:%d\n", front2, rear2, realCap2 - 1);

    i = queueFirst2 + (front2 - queueFirst2 + 1) % capacity2;//Starting from the second element of the queue which is the first meaningful value because no value gets stored in front value of circular queue
    do {
        printf("%d\t", array[i]);
        i = queueFirst2 + (i - queueFirst2 + 1) % capacity2;
    } while (i != queueFirst2 + (rear2 - queueFirst2 + 1) % capacity2);//Print every item of the queue

    printf("\n");
}

int main() {

   

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    char command[20];//Array to store the command of input
    char queue[10];//Array to store which queue that command will work on
    int value;//Value that will get inserted in queue

    while (fscanf(file, "%s", command) == 1) {//Reads input and calls functions with respect to it
        if (strcmp(command, "ENQUEUE") == 0) {
            fscanf(file, "%s %d", queue, &value);
            if (strcmp(queue, "FIRST") == 0) {
                enqueue1(value);
            }
            else if (strcmp(queue, "SECOND") == 0) {
                enqueue2(value);
            }
        }
        else if (strcmp(command, "DEQUEUE") == 0) {
            fscanf(file, "%s", queue);
            if (strcmp(queue, "FIRST") == 0) {
                dequeue1();
            }
            else if (strcmp(queue, "SECOND") == 0) {
                dequeue2();
            }
        }
       else if (strcmp(command, "PRINT") == 0) {
            fscanf(file, "%s", queue);
            if (strcmp(queue, "FIRST") == 0) {
                print1();
            }
            else if (strcmp(queue, "SECOND") == 0) {
                print2(); 
            }
        }
    }

    fclose(file);



    return 0;
}

