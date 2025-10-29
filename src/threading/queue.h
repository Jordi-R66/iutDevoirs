#pragma once

#ifndef QUEUE_HEADER

#include "common.h"

#pragma pack(1)

typedef struct queue_node {
	ptr data;
	QNodePtr next;
} QNode, *QNodePtr;

typedef struct {
	QNodePtr head, tail;

	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool stop;
} Queue;

#pragma pack()

#define QUEUE_HEADER
#endif