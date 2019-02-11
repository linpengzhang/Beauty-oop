#include "beautyitem.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
std::map<std::string,BeautyItem*> BeautyItem::table = std::map<std::string, BeautyItem*>();

BeautyItem::BeautyItem(const std::string& b, const std::string& n): marca(b), nome(n){}

BeautyItem* BeautyItem::unserialize(QXmlStreamReader& reader){
    if(reader.name()!="BeautyItem")
        throw std::string("Name is not right");
    std::string tmp = reader.attributes().value("tipo").toString().toStdString();
    if(table.count(tmp)==0)
        throw std::string("Not find type");
    return table[tmp]->create(reader);
}

std::string BeautyItem::getMarca() const{ return marca; }
std::string BeautyItem::getNome() const{ return nome; }
void BeautyItem::setMarca(const std::string& m){ marca=m; }
void BeautyItem::setNome(const std::string& n){ nome=n; }



