#ifndef RSS_H 
#define RSS_H

#include <Wt/WContainerWidget.h>
#include <functional>

class Rss : public Wt::WContainerWidget {
public:
    Rss();
    void onNavigate(std::function<void(const std::string& )>&& callback);

private:
    std::function<void(const std::string&)> navigate_;

    
};

#endif