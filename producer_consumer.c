#include<stdio.h>
#include<stdlib.h>

void producer();
void consumer();
int wait(int);
int signal(int);

int mutex = 1;
int full = 0;
int empty = 3;
int item = 0;
 
int main()
{
	int choice;
	while(1) {
		printf("\n1.Producer\n2.Consumer\n3.Exit\n");
		printf("\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice) {
			case 1: 
				if ((mutex == 1) && (empty != 0)) { //cheching condition for creating items of upto limit by producer
					producer();
				} else {
					printf("\nIt's full...\n");
				}
				break;
			case 2: 
				if ((mutex == 1) && (full != 0)) { //cheching condition for giving items to producers from the produced items
					consumer();
				} else {
					printf("\nIt's empty...\n");
				}
				break;
			case 3:
				exit(0);
				break;
		}
	}
	return 0;
}
 
int wait(int s) //for decreament
{
	return --s;
}
 
int signal(int s)
{
	return ++s;
}
 
void producer()
{
	mutex = wait(mutex);
	full = signal(full);
	empty = wait(empty);
	item++;
	printf("\nProducer produces the item %d", item);
	mutex = signal(mutex);
}
 
void consumer()
{
	mutex = wait(mutex);
	full = wait(full);
	empty = signal(empty);
	printf("\nConsumer consumes item %d", item);
	item--;
	mutex = signal(mutex);
}
