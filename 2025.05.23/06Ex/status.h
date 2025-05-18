#ifndef STATUS_H
#define STATUS_H

#define ERR_MSG_MEM	"Error: Not enough memory"
#define ERR_MSG_OPEN	"Error: Cannot open file"
#define ERR_MSG_READ	"Error: Cannot read file"

typedef enum
{
	SUCCESS,
	ERR_OPEN = -1,
	ERR_READ = -2,
	ERR_MEM = -3
} io_status;

#endif
