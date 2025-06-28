#ifndef NAVBAR_H
#define NAVBAR_H
#include <functional>
#include <vector>
#include <Wt/WContainerWidget.h>

class Navbar : public Wt::WContainerWidget {
public:
    Navbar();

    void onNavigate(std::function<void(const std::string& )>&& callback);

private:
    std::function<void(const std::string&)> navCallback_;
    std::vector<Wt::WMenuItem*> menuItems_;

};

#endif
