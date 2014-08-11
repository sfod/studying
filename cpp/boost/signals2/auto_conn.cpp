#include <cstdlib>

#include <set>

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


class MessageAreaManager {
    typedef boost::signals2::signal<void (const NewsItem&)> signal_type;

public:
    MessageAreaManager() {}

    boost::signals2::connection add_listener(const signal_type::slot_type &listener) {
        return deliver_news_.connect(listener);
    }

    void update(const NewsItem &news) {
        deliver_news_(news);
    }

private:
    signal_type deliver_news_;
};


class ClientMessageArea_1 {
public:
    explicit ClientMessageArea_1(MessageAreaManager *msg_area_mgr)
        : msg_area_mgr_(msg_area_mgr), conn_() {
    }

    ~ClientMessageArea_1() {
        conn_.disconnect();
    }

    void init() {
        conn_ = msg_area_mgr_->add_listener(boost::bind(&ClientMessageArea_1::display_news, this, _1));
    }

    void display_news(const NewsItem &news) const {
        std::cout << "client_1: " << news.text() << std::endl;
    }

private:
    MessageAreaManager *msg_area_mgr_;
    boost::signals2::connection conn_;
};

class ClientMessageArea_2 {
public:
    explicit ClientMessageArea_2(MessageAreaManager *msg_area_mgr) : msg_area_mgr_(msg_area_mgr) {}

    ~ClientMessageArea_2() {
        conn_.disconnect();
    }

    void init() {
        conn_ = msg_area_mgr_->add_listener(boost::bind(&ClientMessageArea_2::display_news, this, _1));
    }

    void display_news(const NewsItem &news) const {
        std::cout << "client_2: " << news.text() << std::endl;
    }

private:
    MessageAreaManager *msg_area_mgr_;
    boost::signals2::connection conn_;
};


int main()
{
    MessageAreaManager msg_area_mgr;

    boost::shared_ptr<ClientMessageArea_1> cli_msg_area_1(new ClientMessageArea_1(&msg_area_mgr));
    cli_msg_area_1->init();

    {
        boost::shared_ptr<ClientMessageArea_2> cli_msg_area_2(new ClientMessageArea_2(&msg_area_mgr));
        cli_msg_area_2->init();

        NewsItem item("breaking news: it works!");
        msg_area_mgr.update(item);

        std::cout << "-----" << std::endl;
    }

    NewsItem item("breaking news: still works!");
    msg_area_mgr.update(item);

    return EXIT_SUCCESS;
}
