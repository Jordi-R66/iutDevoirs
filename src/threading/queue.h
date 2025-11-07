#pragma once

#ifndef QUEUE_HEADER

#include "common.h"

#pragma pack(1)

typedef struct queue_node {
	ptr data;
	ptr next; // QNodePTR
} QNode, *QNodePtr;

typedef struct queue {
	QNodePtr head, tail;

	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool stop;
} Queue, *QPtr;

#pragma pack()

#define QNODE_SIZE sizeof(QNode)
#define QUEUE_SIZE sizeof(Queue)

// Fonctions

void initQueue(QPtr queue);
void destroyQueue(QPtr queue);

void pushQueue(QPtr queue, ptr data);
ptr popQueue(QPtr queue);
void stopQueue(QPtr queue);

#define QUEUE_HEADER
#endif