#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WResource.h>

#include "mdreader.h"
#include "navbar.h"
#include "blog.h"
#include "about.h"
#include "rss.h"


class MainApp : public Wt::WApplication {
public:
    MainApp(const Wt::WEnvironment& env);

private:
    Wt::WStackedWidget* stack_;
    Wt::WContainerWidget* home_;
    Blog* blog_;
    Navbar* navbar_;
    About* about_;
    MDReader* postReader_;
    Rss* rss_;

    void navigate(const std::string& route);
};

MainApp::MainApp(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Misa");


    addMetaHeader("viewport", "width=device-width, initial-scale=1");
    useStyleSheet("/resources/style.css");

    // Navbar
    navbar_ = root()->addNew<Navbar>();
    navbar_->onNavigate([=](const std::string& route) {
        navigate(route);
    });

    //save all page in stack
    stack_ = root()->addNew<Wt::WStackedWidget>();
    stack_->setStyleClass("body");

    // Home page
    home_ = stack_->addNew<Wt::WContainerWidget>();
    home_->setStyleClass("hero");
    home_->addNew<Wt::WText>("<h1>Hello And Welcome</h1>");
    home_->addNew<Wt::WText>("I am Misa!")->setStyleClass("typewriter");
    home_->addNew<Wt::WImage>(Wt::WLink("/resources/images/cat.png"))->setStyleClass("cats");

    // Blog page
    blog_ = stack_->addNew<Blog>();
    
     // Post
    postReader_ = stack_->addNew<MDReader>();

    //About Me Page
    about_ = stack_->addNew<About>();

    //Rss
    rss_ = stack_->addNew<Rss>();

    //Route listener, fuccckkkkkkkkkkkk
    internalPathChanged().connect([=] {
        std::string path = internalPath();
        if (path.find("/post/") == 0) {
            std::string slug = path.substr(6); 
            postReader_->load(slug);           
            stack_->setCurrentWidget(postReader_);
        } else if (path == "/blog") {
            stack_->setCurrentWidget(blog_);
        } else if (path == "/about") {
            stack_->setCurrentWidget(about_);
        } else if (path == "/rss") {
            stack_->setCurrentWidget(rss_);
        } else {
            stack_->setCurrentWidget(home_);
        }
    });

    //first logic if damn user give link with path url, also fuckkkkkkkk
    std::string path = env.internalPath();
    if (path.find("/post/") == 0) {
        std::string slug = path.substr(6);
        postReader_->load(slug);
        stack_->setCurrentWidget(postReader_);
    }else if (path == "/blog") {
        stack_->setCurrentWidget(blog_);
    } else if (path == "/about") {
        stack_->setCurrentWidget(about_);
    }else if (path == "/rss") {
            stack_->setCurrentWidget(rss_);
    }else {
   
        if (path.empty() || path == "/") {
            navigate("home");
        }
    }
    
}

void MainApp::navigate(const std::string& route) {

    setInternalPath("/" + route, true);
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {

        return std::make_unique<MainApp>(env);
    });
}
