#ifndef MDREADER_H
#define MDREADER_H

#include <Wt/WContainerWidget.h>

class MDReader : public Wt::WContainerWidget {
public:
    MDReader();
    void load(const std::string& slug);
};

#endif
