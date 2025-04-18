#pragma once

#include <memory>
#include "asio/io_context.hpp"
#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace olc {
namespace net{
template<typename T>
class client_interface{
  client_interface() : m_socket(m_context){
    // Intialize the socket with the io context, so it can do stuff
  }
  virtual ~client_interface(){
    // if the client is destroyed, always try and disconnect from server
    Disconnect();
  }
public:
  // Connect to server with hostname/ip-address and port
  bool Connect(const std::string& host, const uint16_t port){
    try{
      // Create a connection
      m_connection = std::make_unique<connection<T>>(); // TODO
      
      // Resolve hostname/ip-address into tangiable physical address
      asio::ip::tcp::resolver resolver(m_context);
      m_endpoints = resolver.resolve(host, std::to_string(port));

      // Tell the connection object to connect to the server
      m_connection->ConnectToServer(m_endpoints);

      // Start Context thread
      thrContext = std::thread([this]() { m_context.run(); });

    }
    catch(std::exception& e){
      std::cerr << "Client Exception: " << e.what() << '\n';
      return false;
    }
    return true;
  }

  // Disconnect from server
  void Disconnect(){
    // If connection exists, and it's connected then...
    if(IsConnected()){
      // ...disconnect from server gracefully
      m_connection->Disconnect();
    }

    // Either way, we're also done with the asio context...
    m_context.stop();
    // ... and its thread
    if (thrContext.joinable())
      thrContext.join();

    // Destroy the connection object
    m_connection.release();
  }

  // Check if client is actually connected to a server
  bool IsConnected(){
    if(m_connection)
      return m_connection->IsConnected();
    else 
      return false;
  }

  // Retrieve queue of messages from server
  tsqueue<owned_message<T>>& Incoming(){
    return m_qMessagesIn;
  }

protected:
  // asio context handles the data transfer
  asio::io_context m_context;
  // ..but needs a thread of its own to execute its work commands
  std::thread thrContext;
  // This is the hardware socket that is connected to the server
  asio::ip::tcp::socket m_socket;
  // The client has a single instance of a "connection" object, which handles data transfer
  std::unique_ptr<connection<T>> m_connection;
private:
  tsqueue<owned_message<T>> m_qMessagesIn;
};
}
}
