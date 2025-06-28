#include "footer.h"
#include <Wt/WImage.h>
#include <Wt/WText.h>

Footer::Footer() {
    setStyleClass("footer");

    auto footer = addNew<Wt::WText>();
    footer->setText("<hr/><p>Made with <span class=\"heart\">❤️</span> by Misa</p><p>Source code available <a href=\"https://github.com/LLENN8/website\">here</a></p>");
    footer->setTextFormat(Wt::TextFormat::XHTML);

}
