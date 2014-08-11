#include <cstdlib>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>


class NewsItem {
public:
    explicit NewsItem(const std::string &text) : text_(text) { }
    const std::string &text() const { return text_; }
private:
    std::string text_;
};

class MessageArea {
public:
    virtual void display_news(const NewsItem &news) const = 0;
};

class ClientMessageArea_1 : public MessageArea {
public:
    void display_news(const NewsItem &news) const {
        std::cout << "client_1: " << news.text() << std::endl;
    }
};

class ClientMessageArea_2 : public MessageArea {
public:
    void display_news(const NewsItem &news) const {
        std::cout << "client_2: " << news.text() << std::endl;
    }
};


int main()
{
    typedef boost::signals2::signal<void (const NewsItem&)> signal_type;

    boost::shared_ptr<ClientMessageArea_1> cli_msg_area_1(new ClientMessageArea_1());

    signal_type deliver_news;

    deliver_news.connect(
            signal_type::slot_type(
                &ClientMessageArea_1::display_news,
                cli_msg_area_1.get(),
                _1)
            .track(cli_msg_area_1));

    deliver_news.connect(
            signal_type::slot_type(
                &ClientMessageArea_1::display_news,
                cli_msg_area_1.get(),
                _1)
            .track(cli_msg_area_1));

    {
        boost::shared_ptr<ClientMessageArea_2> cli_msg_area_2(new ClientMessageArea_2());
        deliver_news.connect(
                signal_type::slot_type(
                    &ClientMessageArea_2::display_news,
                    cli_msg_area_2.get(),
                    _1)
                .track(cli_msg_area_2));

        NewsItem item("breaking news: it works!");
        deliver_news(item);

        std::cout << "-----" << std::endl;
    }

    NewsItem item2("breaking news: still works!");
    deliver_news(item2);

    return EXIT_SUCCESS;
}
