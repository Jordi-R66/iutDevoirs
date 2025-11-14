#include "common.h"

#ifndef FILE_ACTIONS

typedef enum Actions {
	UNKNOWN = 0,
	// ---------------------------
	ADD_USER = 1,
	READ_USER = 2,
	EDIT_USER = 3,
	DEL_USER = 4,
	// ---------------------------
	ADD_HOMEWORK = 5,
	READ_HOMEWORK = 6,
	EDIT_HOMEWORK = 7,
	DEL_HOMEWORK = 8
	// ---------------------------
} Actions;

typedef struct {
	ptr response;
	size_t responseSize;

	bool hasReturned;
} ActionResponse, *ActionRespPtr;

typedef struct {
	Actions actionType;
	size_t actionSize;
	ptr actionBody;

	ActionResponse response;
} ActionRequest, *ActionReqPtr;

#define ACTION_REQ_SIZE sizeof(ActionRequest)
#define ACTION_RESP_SIZE sizeof(ActionResponse)

#define FILE_ACTIONS
#endif