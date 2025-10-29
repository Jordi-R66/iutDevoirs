#pragma once

#ifndef QUEUE_HEADER

#include "common.h"

#pragma pack(1)

typedef struct queue_node {
	ptr data;
	QNodePtr next;
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

void initQueue(QPtr Queue);
void destroyQueue(QPtr Queue);

void pushQueue(QPtr Queue, ptr data);
ptr popQueue(QPtr Queue);
void stopQueue(QPtr Queue);

#define QUEUE_HEADER
#endif