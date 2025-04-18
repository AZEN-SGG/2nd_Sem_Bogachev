typedef enum io_status_ {
    SUCCESS, /* все хорошо */
    ERROR_OPEN, /* ошибка открытия файла */
    ERROR_READ, /* ошибка чтения файла */
    ERROR_MEM, /* ошибка выделения памяти */
    } io_status;