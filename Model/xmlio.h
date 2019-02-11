#ifndef XMLIO_H
#define XMLIO_H

#include "container.h"
#include "deepptr.h"
#include "hierarchy/beautyitem.h"
class XmlIO {
private:
    std::string filename;
public:
    XmlIO(const std::string&);
    Container<DeepPtr<BeautyItem>> read() const;
    void write(const Container<DeepPtr<BeautyItem>>&) const;
};

#endif // XMLIO_H
