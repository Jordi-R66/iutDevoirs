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

void pushQueue(QPtr queue, ptr data) {
	QNodePtr node = calloc(1, QNODE_SIZE);

	node->data = data;
	node->next = NULL;

	pthread_mutex_lock(&queue->mutex);

	if (queue->tail) {
		queue->tail->next = node;
	} else {
		queue->head = node;
	}

	queue->tail = node;

	pthread_cond_signal(&queue->cond);
	pthread_mutex_unlock(&queue->mutex);
}

