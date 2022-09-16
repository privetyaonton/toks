#ifndef UART_H
#define UART_H
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#define MAX_SIZE_BUFFER 1000

int write_all (int fd, const void * buffer, int size);
int read_all (int fd, void * buffer, int size);

class Uart
{
    private:
        int fd;
        struct termios old_settings;
        struct termios new_settings;

    public: 

        void open_uart(const char* path_name);

        void close_uart();

        int read_buf (char * buf);

        void write_buf (const char* buf);

        int get_fd ();

        void set_speed (speed_t value);
};



#endif