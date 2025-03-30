#ifndef IO_STATUS_H
#define IO_STATUS_H

#define SINGULAR 2

typedef enum _io_status
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ
} io_status;

#endif
