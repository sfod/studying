#ifndef STUDY_BOOST_ASIO_TCP_CLIENT_
#define STUDY_BOOST_ASIO_TCP_CLIENT_

#include <boost/asio.hpp>
#include <boost/bind.hpp>

class tcp_client {
public:
    tcp_client(boost::asio::io_service &io_service);
    ~tcp_client();

    void request(const std::string &host, const std::string &path);

private:
    void handle_connect(const boost::system::error_code &ec);
    void handle_write(const boost::system::error_code &ec);
    void handle_read_status_line(const boost::system::error_code &ec);
    void handle_read_header(const boost::system::error_code &ec);
    void handle_read_content(const boost::system::error_code &ec);

private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
};

#endif  // STUDY_BOOST_ASIO_TCP_CLIENT_
