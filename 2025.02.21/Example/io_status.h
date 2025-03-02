#ifndef IO_STATUS_H
#define IO_STATUS_H

#typedef enum _io_status
{
	SUCCESS,
	READ_ERROR,
	SIZE_ERROR,
	FORMAT_ERROR,
	MEMORY_ERROR
} io_status;

#endif
