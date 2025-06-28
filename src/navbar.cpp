#include "navbar.h"
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WApplication.h>
Navbar::Navbar() {
    auto contents = addNew<Wt::WStackedWidget>();
    auto menu = addNew<Wt::WMenu>(contents);
    menu->setStyleClass("nav");

    auto addItem = [&](const std::string& name, const std::string& route) {
        auto item = menu->addItem(name);
        menuItems_.push_back(item);

        item->clicked().connect([=] {

            for (auto* i : menuItems_)
                i->setStyleClass("");

         
            item->setStyleClass("active");

         
            if (navCallback_) navCallback_(route);
        });
    };

    addItem("Home", "home");
    addItem("Blog", "blog");
    addItem("About Me", "about");
     addItem("Rss", "rss");

    //active page on navigasi
    std::string currentPath = Wt::WApplication::instance()->internalPath();
    if (currentPath == "/blog") {
        menuItems_[1]->setStyleClass("active");
    } else if (currentPath == "/about") {
        menuItems_[2]->setStyleClass("active");
    } else if (currentPath == "/rss") {
        menuItems_[3]->setStyleClass("active");
    } else {
        menuItems_[0]->setStyleClass("active"); // Default ke Home
    }
}

void Navbar::onNavigate(std::function<void(const std::string&)>&& callback) {
    navCallback_ = std::move(callback);
}
