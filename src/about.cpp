#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WImage.h>
#include <Wt/WContainerWidget.h>
#include "navbar.h"
#include "about.h"
#include "footer.h"

About::About() {
    auto wrapper = this->addNew<Wt::WContainerWidget>();
    wrapper->setStyleClass("about-wrapper");

    // ===== LEFT CONTAINER  =====
    auto west_container = wrapper->addNew<Wt::WContainerWidget>();
    west_container->setStyleClass("west-container");

    auto cat_peek = west_container->addNew<Wt::WImage>(Wt::WLink("/resources/images/cat_peek.png"));
    cat_peek->setStyleClass("cat-peek");

    auto contact = west_container->addNew<Wt::WText>();
    contact->setStyleClass("contact");
    contact->setText("Fediverse"
                     "<ul>"
                     "<li>Sharkey: LLENN08@hiradai.space</li>"
                     "<li>Misskey: LLENN08@misskey.id</li>"
                     "</ul>");
    contact->setTextFormat(Wt::TextFormat::XHTML);

    // ===== RIGHT CONTAINER  =====
    auto east_container = wrapper->addNew<Wt::WContainerWidget>();
    east_container->setStyleClass("east-container");

    auto card = east_container->addNew<Wt::WContainerWidget>();
    card->setStyleClass("card");

    auto text = card->addNew<Wt::WText>();
    text->setText("<h2>About Me</h2>"
                  "<p>Hi, I am Misa! <br />"
                  "Nothing interesting about me, I am just lazy person<br />"
                  "who love to lay down in comfy bed</p>"
                  "<p>I am a College Student and Tutor Freelance.<br />"
                  "Usually I just teaching physics and math<br />"
                  "I just dump I don't really have things considered as a hobby, <br /> "
                  "but I occasionally dabble in programming.</p>");
    text->setTextFormat(Wt::TextFormat::XHTML);
    card->addNew<Wt::WBreak>();
    card->addNew<Wt::WBreak>();
    auto cat_card = card->addNew<Wt::WImage>(Wt::WLink("/resources/images/about-card-cat.png"));
    cat_card->setStyleClass("cat-card");

    // ===== FOOTER =====
    auto footer_container = this->addNew<Footer>();

}
