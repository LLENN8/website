#include "rss.h"
#include "navbar.h"

#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>


Rss::Rss() {
    setStyleClass("blog");
    addNew<Wt::WText>("<h3>RSS/Atom Feed:</h3>");
    addNew<Wt::WText>("https://blog.hiradai.space/rss.xml");
}



void Rss::onNavigate(std::function<void(const std::string&)>&& callback) {
    navigate_ = std::move(callback);
}