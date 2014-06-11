#include "tcp_client.hpp"

int main(int /* argc */, char ** /* argv */)
{
    boost::asio::io_service io_service;
    tcp_client tc(io_service);
    tc.request("rutracker.org", "/forum/index.php");
    io_service.run();

    return EXIT_SUCCESS;
}
