/*
* Pipe_server
*/
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main(int argc, const char** argv)
{
    wcout << "Creating an instance of a named pipe..." << endl;
    // Create a pipe to send data
    HANDLE pipe = CreateNamedPipe(
        L"\\\\.\\pipe\\pipe_demo", // name of the pipe
        PIPE_ACCESS_DUPLEX, // bi-direction pipe -- read/write
        PIPE_TYPE_BYTE, // send data as a byte stream
        1, // only allow 1 instance of this pipe
        0, // no outbound buffer
        0, // no inbound buffer
        0, // use default wait time
        NULL // use default security attributes
    );
    if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
        cout << "Failed to create duplex pipe instance.";
        // look up error code here using GetLastError()
        system("pause");
        return 1;
    }
    cout << "Waiting for a client to connect to the pipe...\n";
    // This call blocks until a client process connects to the pipe
    BOOL result = ConnectNamedPipe(pipe, NULL);
    if (!result) {
        cout << "Failed to make connection on named pipe.\n";
        // look up error code here using GetLastError()
        CloseHandle(pipe); // close the pipe
        system("pause");
        return 1;
    }
    cout << "Sending data to pipe...\n";
    // This call blocks until a client process reads all the data
    string data = "From Server: Server is ready";
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

    char buffer[128];
    DWORD numBytesRead = 0;
    result = ReadFile(
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
    
    // Close the pipe (automatically disconnects client too)
    CloseHandle(pipe);
    cout << "Done.\n";
    system("pause");
    return 0;
}