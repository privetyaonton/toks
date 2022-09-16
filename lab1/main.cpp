#include "uart.h"
#include <string>

using namespace std;

Uart input_uart, output_uart;

void communication ();

int main(int argc, const char * argv[])
{
    if (argc != 3)
    {
        cout << "Неверное количество аргументов (./main <path1> <path2>)" << endl;
        exit (EXIT_FAILURE);
    }

    input_uart.open_uart(argv[1]);
    output_uart.open_uart(argv[2]);

    input_uart.set_speed (B50);
    output_uart.set_speed (B50);

    cout << "Включена минимальная скорость ввода и вывода" << endl;

    communication();

    cout << "\n-----------------------------------------" << endl;
    
    input_uart.set_speed (B230400);
    output_uart.set_speed (B230400);

    cout << "Включена максимальная скорость ввода и вывода" << endl;

    communication();

    cout << "\n-----------------------------------------" << endl;

    input_uart.set_speed (B50);
    output_uart.set_speed (B57600);

    cout << "Включена различная скорость ввода и вывода" << endl;

    communication();

    cout << "\n-----------------------------------------" << endl;

    input_uart.close_uart();
    output_uart.close_uart();

    return 0;

}

void communication()
{
    string input;

    cout << "Введите - ";

    cin >> input;

    input_uart.write_buf (input.c_str());

    char buf[MAX_SIZE_BUFFER];
    int size = output_uart.read_buf (buf);

    for (int i = 0; i < size; i++)
        cout << buf[i];
    cout << endl;
}