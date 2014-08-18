#ifndef IVIEW_HPP
#define IVIEW_HPP

class IView
{
public:
    virtual ~IView() {}

    virtual bool init() = 0;
    virtual void on_msg() = 0;
    virtual void on_update() = 0;
};

#endif // IVIEW_HPP
