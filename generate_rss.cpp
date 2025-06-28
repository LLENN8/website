#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <regex>
#include <map>
#include <cmark.h>

namespace fs = std::filesystem;


std::string toISO8601(const std::string& date) {
    if (date.find('T') == std::string::npos)
        return date + "T00:00:00Z";
    return date;
}


std::map<std::string, std::string> parseFrontMatter(const std::string& markdown, std::string& contentOut) {
    std::map<std::string, std::string> metadata;
    std::regex fm("^---\\s*([\\s\\S]*?)---\\s*");
    std::smatch match;

    if (std::regex_search(markdown, match, fm)) {
        std::string yaml = match[1].str();
        contentOut = markdown.substr(match[0].length());

        std::regex kv("^(\\w+):\\s*(.+)$", std::regex::multiline);
        auto begin = std::sregex_iterator(yaml.begin(), yaml.end(), kv);
        for (auto it = begin; it != std::sregex_iterator(); ++it) {
            metadata[(*it)[1].str()] = (*it)[2].str();
        }
    } else {
        contentOut = markdown;
    }

    return metadata;
}

std::string generateAtom() {
    std::ostringstream feed;
    feed << R"(<?xml version="1.0" encoding="UTF-8"?>)"
         << "\n<feed xmlns=\"http://www.w3.org/2005/Atom\">\n";

    feed << "  <title>Misa's Blog</title>\n";
    feed << "  <id>https://blog.hiradai.space/</id>\n";
    feed << "  <link rel=\"alternate\" href=\"https://blog.hiradai.space/\"/>\n";
    feed << "  <link rel=\"self\" href=\"https://blog.hiradai.space/rss.xml\"/>\n";

    std::string latestDate = "2025-01-01T00:00:00Z"; // default fallback

    const std::string postDir = "posts/";
    for (const auto& entry : fs::directory_iterator(postDir)) {
        if (entry.path().extension() != ".md") continue;

        std::ifstream file(entry.path());
        if (!file.is_open()) continue;

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string markdown = buffer.str();
        std::string content;
        auto metadata = parseFrontMatter(markdown, content);

        std::string filename = entry.path().filename().stem().string();
        std::string title = metadata.count("title") ? metadata["title"] : filename;
        std::string date = metadata.count("date") ? toISO8601(metadata["date"]) : "2025-01-01T00:00:00Z";
        std::string url = "https://blog.hiradai.space/post/" + filename + ".html";

        if (date > latestDate) latestDate = date;

        // Render HTML from markdown
        char* html = cmark_markdown_to_html(content.c_str(), content.length(), CMARK_OPT_DEFAULT);
        std::string htmlContent = html;
        free(html);

        feed << "  <entry>\n";
        feed << "    <title>" << title << "</title>\n";
        feed << "    <link rel=\"alternate\" type=\"text/html\" href=\"" << url << "\"/>\n";
        feed << "    <id>" << url << "</id>\n";
        feed << "    <published>" << date << "</published>\n";
        feed << "    <updated>" << date << "</updated>\n";
        feed << "    <content type=\"html\"><![CDATA[" << htmlContent << "]]></content>\n";
        feed << "  </entry>\n";
    }

    feed << "  <updated>" << latestDate << "</updated>\n";
    feed << "  <author><name>Misa</name></author>\n";
    feed << "</feed>\n";
    return feed.str();
}

int main() {
    std::ofstream out("rss.xml");
    if (!out) {
        std::cerr << "Failed to write rss.xml\n";
        return 1;
    }

    out << generateAtom();
    std::cout << "rss.xml generated successfully.\n";
    return 0;
}
