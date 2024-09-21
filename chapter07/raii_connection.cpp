#include <gtest/gtest.h>
#include <iostream>

class Connection {

public:
  Connection(const std::string &) {
    std::cout << "Connection constructed" << "\n";
  }

  ~Connection() { std::cout << "Connection destructed" << "\n"; }
};

auto close(Connection &) { std::cout << "in close fn: closing..." << "\n"; }

auto open_connection(const std::string &url) { return Connection{url}; }

auto send_request(Connection &, const std::string &) {
  std::cout << "in send_request fn: sending req" << "\n";
}

class RAIIConnection {

public:
  RAIIConnection(const std::string &url) : connection_{open_connection(url)} {}
  ~RAIIConnection() {
    try {
      close(connection_);
    }

    catch (const std::exception &) {
      std::cout << "handling exception but never throwing from a destructor."
                << "\n";
    }
  }

  auto &get() { return connection_; }

private:
  Connection connection_;
};

auto send(const std::string &message) {
  auto connection = RAIIConnection("http://example.com");
  send_request(connection.get(), message);
}

TEST(RaiiConnection, SendMessage) {
  send("a message");
  send("another message");
}
