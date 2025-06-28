#ifndef BLOG_H 
#define BLOG_H

#include <functional>
#include <Wt/WContainerWidget.h>

class Blog : public Wt::WContainerWidget {
public:
    Blog();
    void onNavigate(std::function<void(const std::string& )>&& callback);
    
private:
    std::function<void(const std::string&)> navigate_;
};

#endif