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
using CustomConnection = olc::net::connection<CustomMsgTypes>;
using CustomMessage = olc::net::message<CustomMsgTypes>;

class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
public:
  CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort)
  {
  }

protected:
  virtual bool OnClientConnect(std::shared_ptr<CustomConnection> client)
  {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerAccept;
    client->Send(msg);
    
    return true;
  }

  // Called when a client appears to have disconnected
  virtual void OnClientDisconnect(std::shared_ptr<CustomConnection> client)
  {
    std::cout << "Removing Client [" << client->GetID() << "]\n";
  }

  virtual void OnMessage(std::shared_ptr<CustomConnection> client, CustomMessage& msg)
  {
    switch (msg.header.id)
    {
      case CustomMsgTypes::ServerPing:
      {
        std::cout << "[" << client->GetID() << "]: Server Ping\n";

        // Simply bounce message back to client
        client->Send(msg);
      }
      break;

      case CustomMsgTypes::MessageAll:
      {
        std::cout << "[" << client->GetID() << "]: Message All\n";
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerMessage;
        msg << client->GetID();
        MessageAllClients(msg, client);
      }
      break;
    }
  }
};

int main()
{
  CustomServer server(60000);
  server.Start();

  while (1)
  {
    server.Update();
  }

  return 0;
}
