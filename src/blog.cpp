#include "blog.h"
#include <Wt/WMenu.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>
#include <filesystem>
#include <string>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include <fstream>
#include <sstream>
#include <map>
#include "footer.h"
#include <unistd.h>

namespace fs = std::filesystem;

static bool extractFrontMatterLightweight(const std::string& path, std::map<std::string, std::string>& metadata) {
    std::ifstream file(path);
    if (!file) return false;

    std::string line;
    bool inFrontMatter = false;

    while (std::getline(file, line)) {
        if (line == "---") {
            if (!inFrontMatter) {
                inFrontMatter = true;
                continue;
            } else {
                break; 
            }
        }

        if (inFrontMatter) {
            auto sep = line.find(':');
            if (sep != std::string::npos) {
                std::string key = line.substr(0, sep);
                std::string value = line.substr(sep + 1);
                //clean space lol, i got one hours error just beause space
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                metadata[key] = value;
            }
        }
    }

    return inFrontMatter;
}

Blog::Blog() {
    setStyleClass("blog");
    auto layout = setLayout(std::make_unique<Wt::WVBoxLayout>());

    const std::string postDir = "posts/";
    try {
        for (const auto& entry : fs::directory_iterator(postDir)) {
            if (entry.path().extension() == ".md") {
                std::string filename = entry.path().filename().stem();

                std::map<std::string, std::string> meta;
                extractFrontMatterLightweight(entry.path().string(), meta);

                // Create container for each post preview
                auto postContainer = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
                postContainer->setStyleClass("post");

                // Title as link
                if (meta.find("title") != meta.end()) {
                    auto link = postContainer->addNew<Wt::WAnchor>(
                    Wt::WLink(Wt::LinkType::InternalPath, "/post/" + filename),
                             "<h2>" + meta["title"] + "</h2>" // Can be changed if you store title in frontmatter
                     );
                     link->setTextFormat(Wt::TextFormat::XHTML);
                }
                
                

                // Date
                if (meta.find("date") != meta.end()) {
                    auto dateText = postContainer->addNew<Wt::WText>("<p class='date'>" + meta["date"] + "</p>");
                    dateText->setTextFormat(Wt::TextFormat::XHTML);
                }

                // Description
                if (meta.find("description") != meta.end()) {
                    auto descText = postContainer->addNew<Wt::WText>("<p>" + meta["description"] + "</p>");
                    descText->setTextFormat(Wt::TextFormat::XHTML);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading posts: " << e.what() << std::endl;
        layout->addWidget(std::make_unique<Wt::WText>(
            "<p style='color:red'>Error reading posts folder.</p>"
        ))->setTextFormat(Wt::TextFormat::XHTML);
    }

    layout->addWidget(std::make_unique<Footer>());
}


void Blog::onNavigate(std::function<void(const std::string&)>&& callback) {
    navigate_ = std::move(callback);
}