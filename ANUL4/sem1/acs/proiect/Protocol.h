#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

/*
Framed protocol:
[4 bytes length] [1 byte op] [payload...]
*/

#define OP_EDIT     1
#define OP_CLEAR    2
#define OP_SAVE     3
#define OP_LOAD     4
#define OP_JOIN     5
#define OP_USERS    6
#define OP_PING     7
#define OP_RENAME   8

// === SERVER → CLIENT ===
#define OP_FILE     9    // payload = current filename
#define OP_STATUS   10   // payload = "saved" | "unsaved"

// === NEW ===
#define OP_EDITORS  11   // payload = "user1,user2,..."

#define SERVER_PORT_DEFAULT 8080
#define MAX_CLIENTS 32
#define BUFFER_CHUNK 1024
#define MAX_FILE_SIZE 1048576


#endif
