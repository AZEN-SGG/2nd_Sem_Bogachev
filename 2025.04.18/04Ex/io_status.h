#ifndef IO_STATUS_H
#define IO_STATUS_H

#define ERR_MEM	"Error: Not enough memory!"
#define ERR_OPEN "Error: Cannot open file"
#define ERR_READ "Error: Cannot read file"
#define ERR_FUNC "Error: Algorithm is not applicable!"

typedef enum _io_status
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ
} io_status;

#endif
