# pipe_demo
This one is to demo use named pipe to communicate between different process at windows platform.

The pipe_server and pipe_client are written with c++. Can run them at 2 cmd terminals, one run server, another one run client as the following

Server side:
pipe_demo\x64\Debug> .\pipe_server.exe
Creating an instance of a named pipe...
Waiting for a client to connect to the pipe...
Sending data to pipe...
Number of bytes sent: 28
Number of bytes read: 35
Message: From client: handshake successfully
Done.
Press any key to continue . . .

Client side:
pipe_demo\x64\Debug> .\pipe_client.exe
Connecting to pipe...
Reading data from pipe...
Number of bytes read: 28
Message: From Server: Server is ready
Number of bytes sent: 31
Done.
Press any key to continue . . .

There is a python version at project named_pipe_py

Server side:
pipe_demo\named_pipe_py>python3 named_pipe.py s
pipe server
waiting for client
got client
message: From client: handshake successfully
finished now

Client side:
pipe_demo\named_pipe_py>python3 named_pipe.py c
pipe client
message: From Server: Server is ready
Send date to server

Also can run c++ version and python version together, like running c++ pipe server, and run python version client together

C++ Server side:
pipe_demo\x64\Debug> .\pipe_server.exe
Creating an instance of a named pipe...
Waiting for a client to connect to the pipe...
Sending data to pipe...
Number of bytes sent: 28
Number of bytes read: 35
Message: From client: handshake successfully
Done.
Press any key to continue . . .

Python client side:
pipe_demo\named_pipe_py>python3 named_pipe.py c
pipe client
message: From Server: Server is ready
Send date to server

