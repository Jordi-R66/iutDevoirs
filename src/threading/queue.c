#include "queue.h"

void initQueue(QPtr queue) {
	queue->head = NULL;
	queue->tail = NULL;
	queue->stop = false;

	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->cond, NULL);
}

