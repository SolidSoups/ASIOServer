#pragma once
#include "net_common.h"
#include <cstring>

namespace olc {
namespace net {
// Message header is sent at the start of all messages. The template allows us
// to use "enum class" to ensure that the messages are valid at compile time.
template <typename T> struct message_header {
  T id{};
  uint32_t size = 0;
};

template <typename T> struct message {
  message_header<T> header{};
  std::vector<uint8_t> body;

  // Returns the size of the entire message packet in bytes
  size_t size() const { return sizeof(message_header<T>) + body.size(); }

  // Override for std::cout compatibility - produces a friendly description of
  // the message
  friend std::ostream &operator<<(std::ostream &os, const message<T> &msg) {
    os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size();
    return os;
  }

  // Pushes any POD-like data into the message buffer
  template <typename DataType>
  friend message<T> &operator<<(message<T> &msg, const DataType &data) {
    // Check that the type of data being pushed is trivially copyable
    static_assert(std::is_standard_layout<DataType>::value,
                  "Data is too complex to be pushed into the vector.");

    // Cache current size of vector, as this will be the point we insert the
    // data
    size_t i = msg.body.size();

    // Resize the vector by the size of the data being pushed
    msg.body.resize(msg.body.size() + sizeof(DataType));

    // Physically copy the data into the newly allocated vector space
    std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

    // Recalculate the size
    msg.header.size = msg.size();

    return msg;
  }

  template <typename DataType>
  friend message<T> &operator>>(message<T> &msg, DataType &data) {
    // Check that the type of the data being pushed is trivially copyable
    static_assert(std::is_standard_layout<DataType>::value,
                  "Data is too complex to be popped from the vector.");

    // Cache the location torwards the end of the vector where the pulled data
    // starts
    size_t i = msg.body.size() - sizeof(DataType);

    // Physically copy the data from the vector into the users variable
    std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

    // Shrink the vector and remove read bytes, and reset end position
    msg.body.resize(i);

    // Recalculate the message size
    msg.header.size = msg.size();

    // Return the target message so that it can be "chained"
    return msg;
  }
};
} // namespace net
} // namespace olc
