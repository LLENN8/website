#include "rss.h"
#include "navbar.h"

#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>


Rss::Rss() {
    setStyleClass("blog");
    addNew<Wt::WText>("<h3>http://localhost:3090/rss.xml</h3>");
}



void Rss::onNavigate(std::function<void(const std::string&)>&& callback) {
    navigate_ = std::move(callback);
}