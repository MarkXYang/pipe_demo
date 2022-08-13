/*
* Pipe_client
*/
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main(int argc, const char** argv)
{
    wcout << "Connecting to pipe...\n";
    // Open the named pipe
    // Most of these parameters aren't very relevant for pipes.
    
    HANDLE pipe = CreateFile(
        L"\\\\.\\pipe\\pipe_demo",
        GENERIC_READ | GENERIC_WRITE, // can be read/write
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (pipe == INVALID_HANDLE_VALUE) {
        cout << "Failed to connect to pipe.\n";
        // look up error code here using GetLastError()
        system("pause");
        return 1;
    }
    
    cout << "Reading data from pipe...\n";
    // The read operation will block until there is data to read
    char buffer[128];
    DWORD numBytesRead = 0;
    BOOL result = ReadFile(
        pipe,
        buffer, // the data from the pipe will be put here
        127 * sizeof(char), // number of bytes allocated
        &numBytesRead, // this will store number of bytes actually read
        NULL // not using overlapped IO
    );
    if (result) {
        buffer[numBytesRead / sizeof(char)] = '\0'; // null terminate the string
        cout << "Number of bytes read: " << numBytesRead << endl;
        cout << "Message: " << buffer << endl;
    }
    else {
        cout << "Failed to read data from the pipe.\n";
    }

    string data = "From client: handshake is done!";
    DWORD numBytesWritten = 0;
    result = WriteFile(
        pipe, // handle to our outbound pipe
        data.c_str(), // data to send
        data.length(), // length of data to send (bytes)
        &numBytesWritten, // will store actual amount of data sent
        NULL // not using overlapped IO
    );
    if (result) {
        cout << "Number of bytes sent: " << numBytesWritten << endl;
    }
    else {
        cout << "Failed to send data.\n";
        // look up error code here using GetLastError()
    }
    // Close our pipe handle
    CloseHandle(pipe);
    cout << "Done." << endl;
    system("pause");
    return 0;
}