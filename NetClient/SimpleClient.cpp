#ifdef _WIN32
#include <conio.h>
int getch()
{
  return _getch();
}

bool my_kbhit()
{
  return _kbhit();
}

#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

bool my_kbhit()
{
  int count;
  ioctl(STDIN_FILENO, FIONREAD, &count);
  return count > 0;
}

int getch()
{
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  int ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
#endif

#include <iostream>

#include "olc_net.h"

enum class CustomMsgTypes : uint32_t
{
  ServerAccept,
  ServerDeny,
  ServerPing,
  MessageAll,
  ServerMessage,
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
  void PingServer()
  {
    std::cout << "[CLIENT] Pinging server...\n";
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerPing;

    // Caution with this
    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

    msg << timeNow;
    Send(msg);
  }

  void MessageAll()
  {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::MessageAll;
    Send(msg);
  }
};

int main()
{
  CustomClient c;
  c.Connect("127.0.0.1", 60000);

  bool bQuit = false;
  while (!bQuit)
  {
    if (my_kbhit())
    {
      int ch = _getch();
      if (ch == '1')
        c.PingServer();
      if (ch == '2')
        c.MessageAll();
      if (ch == '3')
        bQuit = true;
    }

    if (c.IsConnected())
    {
      if (!c.Incoming().empty())
      {
        auto msg = c.Incoming().pop_front().msg;

        switch (msg.header.id)
        {
          case CustomMsgTypes::ServerAccept:
          {
            // Server has responded to a ping request
            std::cout << "Server Accepted Connection\n";
          }
          break;

          case CustomMsgTypes::ServerPing:
          {
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            std::chrono::system_clock::time_point timeThen;
            msg >> timeThen;
            std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count()
                      << "\n";
          }
          break;

          case CustomMsgTypes::ServerMessage:
          {
            // Server has responded to a ping request
            uint32_t clientID;
            msg >> clientID;
            std::cout << "Hello from [" << clientID << "]\n";
          }
          break;
        }
      }
    }
    else
    {
      std::cout << "Server Down\n";
      bQuit = true;
    }
  }
  std::cout << "Program ended.\n";
  return 0;
}
