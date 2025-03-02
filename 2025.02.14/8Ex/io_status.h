#ifndef IO_STATUS_H
#define IO_STATUS_H

#define LEN 1234

typedef enum io_status_ {
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_PATTERN,
} io_status;

#endif
