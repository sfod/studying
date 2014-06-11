#include "tcp_client.hpp"

tcp_client::tcp_client(boost::asio::io_service &io_service)
        : io_service_(io_service), socket_(io_service), request_(), response_()
{
}

tcp_client::~tcp_client()
{
}

void tcp_client::request(const std::string &host, const std::string &path)
{
    std::ostream request_stream(&request_);
    request_stream << "GET " << path << " HTTP/1.0\r\n";
    request_stream << "Host: " << host << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query(host, "http");
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    boost::asio::async_connect(socket_, it,
            boost::bind(&tcp_client::handle_connect, this,
                boost::asio::placeholders::error));

    io_service_.run();
}

void tcp_client::handle_connect(const boost::system::error_code &ec)
{
    if (!ec) {
        boost::asio::async_write(socket_,
                request_,
                boost::bind(&tcp_client::handle_write, this,
                    boost::asio::placeholders::error));
    }
    else {
        std::cerr << "failed to connect: " << ec.message() << std::endl;
    }
}

void tcp_client::handle_write(const boost::system::error_code &ec)
{
    if (!ec) {
        boost::asio::async_read_until(socket_, response_, "\r\n",
                boost::bind(&tcp_client::handle_read_status_line, this,
                    boost::asio::placeholders::error));
    }
    else {
        std::cerr << "read failed: " << ec.message() << std::endl;
    }
}

void tcp_client::handle_read_status_line(const boost::system::error_code &ec)
{
    if (!ec) {
        std::istream response_stream(&response_);
        std::string http_version;
        unsigned int status_code;
        std::string status_message;
        response_stream >> http_version >> status_code;
        std::getline(response_stream, status_message);

        std::cout << status_code << " " << status_message << std::endl;

        boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
                boost::bind(&tcp_client::handle_read_header, this,
                    boost::asio::placeholders::error));
    }
    else {
        std::cerr << "read failed: " << ec.message() << std::endl;
    }
}

void tcp_client::handle_read_header(const boost::system::error_code &ec)
{
    if (!ec) {
        std::istream response_stream(&response_);
        std::string header;
        while (std::getline(response_stream, header) && (header != "\r")) {
            std::cout << header << std::endl;
        }
        std::cout << std::endl;

        std::cout << &response_;
        boost::asio::async_read(socket_, response_,
                boost::asio::transfer_at_least(1),
                boost::bind(&tcp_client::handle_read_content, this,
                    boost::asio::placeholders::error));
    }
    else {
        std::cerr << "read failed: " << ec.message() << std::endl;
    }
}

void tcp_client::handle_read_content(const boost::system::error_code &ec)
{
    if (!ec) {
        std::cout << &response_;
        boost::asio::async_read(socket_, response_,
                boost::asio::transfer_at_least(1),
                boost::bind(&tcp_client::handle_read_content, this,
                    boost::asio::placeholders::error));
    }
    else {
        std::cerr << "read failed: " << ec.message() << std::endl;
    }
}
