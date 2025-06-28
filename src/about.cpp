#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WImage.h>
#include "navbar.h"
#include "about.h"
#include "footer.h"
About::About(){

    auto layout = setLayout(std::make_unique<Wt::WBorderLayout>());
    
    //left
    auto west_container = std::make_unique<Wt::WContainerWidget>();
    west_container->setStyleClass("west-container");
    auto cat_peek = west_container->addNew<Wt::WImage>(Wt::WLink("/resources/images/cat_peek.png"));
    cat_peek->setStyleClass("cat-peek");
    auto contact = west_container->addNew<Wt::WText>();
    contact->setStyleClass("contact");
    contact->setText("Fediverse""<ul><li>Misskey: LLENN08@misskey.id</li><li>Sharkey: LLENN08@hiradai.space</li></ul>");
    contact->setTextFormat(Wt::TextFormat::XHTML);
    
    layout->addWidget(std::move(west_container), Wt::LayoutPosition::West);

    //right
    auto east_container = std::make_unique<Wt::WContainerWidget>();
    east_container->setStyleClass("east-container");
    east_container->addStyleClass("card");
    auto text = east_container->addNew<Wt::WText>();
    text->setText("<h2>About Me</h2> <p>Hi, I am Misa! <br /> Nothing interesting about me, I am just lazy person<br /> who love to lay down in comfy bed</p> <p> I am a College Student and Tutor Freelance. <br /> Usually I just teaching physics and math <br /> I just dump I don't really have things considered as a hobby, but I occasionally dabble in programming.</p>");
    text->setTextFormat(Wt::TextFormat::XHTML);

    auto cat = east_container->addNew<Wt::WImage>(Wt::WLink("/resources/images/about-card-cat.png"));
    cat->setStyleClass("cat-card");
    layout->addWidget(std::move(east_container), Wt::LayoutPosition::East);

    //footer
    auto south_container = std::make_unique<Footer>();
    layout->addWidget(std::move(south_container), Wt::LayoutPosition::South);

}

void About::onNavigate(std::function<void(const std::string&)>&& callback) {
    navigate_ = std::move(callback);
}