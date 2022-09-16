#include "uart.h"
using namespace std;

void Uart::open_uart (const char * path_name)
{
    fd = open (path_name, O_RDWR);
    tcgetattr (fd, &old_settings);
    new_settings = old_settings;
}

void Uart::close_uart ()
{
    tcsetattr (fd, TCSANOW, &old_settings);
    close (fd);
}

int Uart::read_buf (char * buf)
{
    char * pbuf = buf;

    int total = 0;

    while (1)
    {
        int count = read (fd, pbuf, 32);

        pbuf += count;
        total += count;

        if (count == -1) {cout << "Ошибка при чтении файла" << endl; return -1; }

        if (count < 32) break;
    }

    cout << "Чтение прошло успешно" << endl;

    return total;
}

void Uart::write_buf (const char * buf)
{
    if (strlen (buf) > MAX_SIZE_BUFFER)
    {
        cout << "Слишком большой буффер" << endl;
        return;
    }

    int size = write_all (fd, buf, strlen (buf));

    if (size == -1)
    {
        cout << "Ошибка при записи в файл" << endl;
    }
    else cout << "Запись прошла успешно" << endl;
}



int write_all (int fd, const void * buffer, int size)
{
    const char * buf = (const char *) buffer;

    int total = 0;

    while (size > 0)
    {
        int count = write (fd, buf, size);

        if (count < 1) return -1;

        buf += count;
        size -= count;
        total += count;
    }

    return total;
}

int Uart::get_fd()
{
    return fd;
}

void Uart::set_speed(speed_t value)
{
    cfsetspeed (&new_settings, value);
    tcsetattr (fd, TCSANOW, &new_settings);
}

