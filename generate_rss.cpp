#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <regex>
#include <map>

/*this one is seperated program from main website and should re-compile manually if there is new post*/
namespace fs = std::filesystem;

std::string generateRSS() {
    std::ostringstream rss;
    rss << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    rss << "<rss version=\"2.0\">\n<channel>\n";
    rss << "<title>Your Blog Title</title>\n";
    rss << "<link>http://localhost:3089/</link>\n";
    rss << "<description>My Blog Feed</description>\n";

    const std::string postDir = "posts/";

    try {
        for (const auto& entry : fs::directory_iterator(postDir)) {
            if (entry.path().extension() == ".md") {
                std::string filename = entry.path().filename().stem();
                std::ifstream file(entry.path());
                if (!file.is_open()) continue;

                std::stringstream buffer;
                buffer << file.rdbuf();
                std::string markdown = buffer.str();

                std::regex fm("^---\\s*([\\s\\S]*?)---\\s*");
                std::smatch match;
                std::map<std::string, std::string> metadata;
                std::string content;

                if (std::regex_search(markdown, match, fm)) {
                    std::string yaml = match[1].str();
                    std::regex kv("^(\\w+):\\s*(.+)$", std::regex::multiline);
                    auto begin = std::sregex_iterator(yaml.begin(), yaml.end(), kv);
                    for (auto it = begin; it != std::sregex_iterator(); ++it) {
                        metadata[(*it)[1].str()] = (*it)[2].str();
                    }
                    content = markdown.substr(match[0].length());
                } else {
                    content = markdown;
                }

                std::string desc = metadata.count("description") ? metadata["description"] : content.substr(0, 200);

                rss << "<item>\n";
                rss << "<title>" << filename << "</title>\n";
                rss << "<link>http://localhost:3089/?_=/post/" << filename << "</link>\n";
                rss << "<description><![CDATA[" << desc << "]]></description>\n";
                rss << "<guid>http://localhost:3089/?_=/post/" << filename << "</guid>\n";
                if (metadata.count("date")) {
                    rss << "<pubDate>" << metadata["date"] << "</pubDate>\n";
                }
                rss << "</item>\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error generating RSS: " << e.what() << "\n";
    }

    rss << "</channel>\n</rss>\n";
    return rss.str();
}

int main() {
    std::ofstream out("rss.xml");
    if (!out) {
        std::cerr << "Failed to write rss.xml\n";
        return 1;
    }

    out << generateRSS();
    std::cout << "rss.xml generated successfully.\n";
    return 0;
}
