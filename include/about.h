#ifndef ABOUT_H 
#define ABOUT_H

#include <functional>
#include <Wt/WContainerWidget.h>

class About : public Wt::WContainerWidget {
public:
    About();
    void onNavigate(std::function<void(const std::string& )>&& callback);
    
private:
    std::function<void(const std::string&)> navigate_;
};

#endif