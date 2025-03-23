#ifndef IO_STATUS_H
#define IO_STATUS_H

#define LEN 1234

typedef enum _io_status
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ,
	ERROR_MEM
} io_status;

#endif
