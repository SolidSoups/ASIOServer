// std
#include <iostream>
#include <string>
#include <thread>

// libs
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket &socket) {
  socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
                         [&](std::error_code ec, std::size_t length) {
                           if (!ec) {
                             std::cout << "\n\nRead " << length << " bytes\n\n";

                             for (int i = 0; i < length; i++) {
                               std::cout << vBuffer[i];
                             }

                             GrabSomeData(socket);
                           }
                         });
}

int main() {
  std::cout << "Hello World!" << std::endl;

  asio::error_code ec;

  // Create a "context" - essentially a platform specific interface
  asio::io_context context;

  // Give some fake work to asio so the context doesnt finish
  asio::io_context::work idleWork(context);

  // Start the context
  std::thread thrContext = std::thread([&]() { context.run(); });

  // Get the address of the thing we want to connect to
  asio::ip::tcp::endpoint endpoint(asio::ip::make_address("77.111.241.88", ec),
                                   80);

  // Create a socket, the context will deliver the implementation
  asio::ip::tcp::socket socket(context);

  // Tell the socket to try and connect
  socket.connect(endpoint, ec);

  if (!ec) {
    std::cout << "Connected!" << std::endl;
  } else {
    std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
  }

  if (socket.is_open()) {
    GrabSomeData(socket);
    std::string sRequest = "GET /index.html HTTP/1.1\r\n"
                           "Host: thegreenlionpub.se/\r\n"
                           "Connection: close\r\n\r\n";
    socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20000ms);
  }

  std::cin.ignore();
  return 0;
}
