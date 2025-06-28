#include "mdreader.h"
#include <Wt/WText.h>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <cmark.h>
#include "footer.h"

#include <string>
#include <regex>
#include <iostream>

std::string extractFrontMatter(const std::string& markdown, std::map<std::string, std::string>& metadata, std::string& contentOut) {
    std::regex frontMatterRegex("^---\\s*([\\s\\S]*?)---\\s*");
    std::smatch match;

    if (std::regex_search(markdown, match, frontMatterRegex)) {
        std::string yaml = match[1].str();

        // Parse key-value pairs
        std::regex kvRegex("^(\\w+):\\s*(.+)$", std::regex::multiline);
        auto begin = std::sregex_iterator(yaml.begin(), yaml.end(), kvRegex);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            std::string key = (*it)[1].str();
            std::string value = (*it)[2].str();
            metadata[key] = value;
        }

        // Remove front matter from the markdown
        contentOut = markdown.substr(match[0].length());
        return yaml;
    } else {
        contentOut = markdown;
        return "";
    }
}

MDReader::MDReader() {
    setStyleClass("post-page");

    
    
}

void MDReader::load(const std::string& slug) {
    clear(); 

    std::ifstream file("posts/" + slug + ".md");
    if (!file) {
        addNew<Wt::WText>("<h3>404 Not Found</h3><p>Post tidak ditemukan.</p>")
            ->setTextFormat(Wt::TextFormat::XHTML);
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string markdown = buffer.str();

    // take a meta data from front matter
    std::map<std::string, std::string> metadata;
    std::string markdownWithoutFrontMatter;
    extractFrontMatter(markdown, metadata, markdownWithoutFrontMatter);

    // change to html
    const char* html = cmark_markdown_to_html(
        markdownWithoutFrontMatter.c_str(),
        markdownWithoutFrontMatter.length(),
        CMARK_OPT_DEFAULT
    );

    auto contentContainer = addNew<Wt::WContainerWidget>();
    auto htmlWidget = contentContainer->addNew<Wt::WText>();
    htmlWidget->setTextFormat(Wt::TextFormat::XHTML);
    htmlWidget->setText(html);

    // footer
    addWidget(std::make_unique<Footer>());

    free((void*)html);
}
