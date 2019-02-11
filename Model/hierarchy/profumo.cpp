#include "profumo.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
Profumo::StaticTableInit::StaticTableInit(){
    ptr = new Profumo();
    table[ptr->tipo()]=ptr;
}
Profumo::StaticTableInit::~StaticTableInit(){ delete ptr; }
Profumo::StaticTableInit Profumo::a;


Profumo::Profumo(const std::string& b, const std::string& n, const std::string& o, float cap, float cons): ConsumableItem (b,n,cap, cons), odore(o){}
void Profumo::serialize(QXmlStreamWriter& writer) const{
    writer.writeStartElement("BeautyItem");
    writer.writeAttribute("tipo", QString::fromStdString(tipo()));

    writer.writeStartElement("marca");
    writer.writeCharacters(QString::fromStdString(getMarca()));
    writer.writeEndElement();
    writer.writeStartElement("nome");
    writer.writeCharacters(QString::fromStdString(getNome()));
    writer.writeEndElement();
    writer.writeStartElement("odore");
    writer.writeCharacters(QString::fromStdString(getOdore()));
    writer.writeEndElement();
    writer.writeStartElement("capacita");
    writer.writeCharacters(QString::fromStdString(std::to_string(getCapacita())));
    writer.writeEndElement();
    writer.writeStartElement("consumo");
    writer.writeCharacters(QString::fromStdString(std::to_string(getConsumo())));
    writer.writeEndElement();

    writer.writeEndElement();
    if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
        throw std::exception();
}
Profumo* Profumo::create(QXmlStreamReader& reader) const{
    std::string marca = "No brand";
    std::string nome = "No name";
    std::string odore = "Inodore";
    float capacita(0);
    float consumo(1);
    if(reader.readNextStartElement() && reader.name()=="marca")
        marca = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="nome")
        nome = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="odore")
        odore = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="capacita")
        capacita = reader.readElementText().toFloat();
    if(reader.readNextStartElement() && reader.name()=="consumo")
        consumo = reader.readElementText().toFloat();
    reader.skipCurrentElement();
    return new Profumo(marca, nome, odore, capacita, consumo);
}
std::string Profumo::getOdore() const { return odore; }
void Profumo::setOdore(const std::string& o){ odore=o;}
Profumo* Profumo::clone() const{ return new Profumo(*this); }
std::string Profumo::tipo() const{ return std::string("Profumo"); }
