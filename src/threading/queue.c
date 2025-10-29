#include "queue.h"

void initQueue(QPtr queue) {
	queue->head = NULL;
	queue->tail = NULL;
	queue->stop = false;

	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->cond, NULL);
}

void destroyQueue(QPtr queue) {
	bool readyToClose = false;

	do {
		readyToClose = popQueue(queue) == NULL;
	} while (!readyToClose);

	pthread_mutex_destroy(&queue->mutex);
	pthread_cond_destroy(&queue->cond);

	queue->head = NULL;
	queue->tail = NULL;
}
