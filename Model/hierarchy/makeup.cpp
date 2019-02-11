#include "makeup.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
MakeUp::StaticTableInit::StaticTableInit(){
    ptr = new MakeUp();
    table[ptr->tipo()]=ptr;
}
MakeUp::StaticTableInit::~StaticTableInit(){ delete ptr; }
MakeUp::StaticTableInit MakeUp::a;

MakeUp::MakeUp(const std::string& b, const std::string& n, const std::string& color, float cap, float cons): ConsumableItem (b,n,cap,cons), colore(color){}
void MakeUp::serialize(QXmlStreamWriter& writer) const{
    writer.writeStartElement("BeautyItem");
    writer.writeAttribute("tipo", QString::fromStdString(tipo()));

    writer.writeStartElement("marca");
    writer.writeCharacters(QString::fromStdString(getMarca()));
    writer.writeEndElement();
    writer.writeStartElement("nome");
    writer.writeCharacters(QString::fromStdString(getNome()));
    writer.writeEndElement();
    writer.writeStartElement("colore");
    writer.writeCharacters(QString::fromStdString(getColore()));
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
MakeUp* MakeUp::create(QXmlStreamReader& reader) const{
    std::string marca = "No brand";
    std::string nome = "No name";
    std::string colore = "Trasparente";
    float capacita(0);
    float consumo(1);
    if(reader.readNextStartElement() && reader.name()=="marca")
        marca = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="nome")
        nome = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="colore")
        colore = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="capacita")
        capacita = reader.readElementText().toFloat();
    if(reader.readNextStartElement() && reader.name()=="consumo")
        consumo = reader.readElementText().toFloat();
    reader.skipCurrentElement();
    return new MakeUp(marca, nome, colore, capacita, consumo);
}
std::string MakeUp::getColore() const { return colore; }
void MakeUp::setColore(const std::string& c){ colore = c;}
MakeUp* MakeUp::clone() const{ return new MakeUp(*this); }
std::string MakeUp::tipo() const{ return std::string("MakeUp"); }

