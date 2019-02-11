#include "pulizia.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
Pulizia::StaticTableInit::StaticTableInit(){
    ptr = new Pulizia();
    table[ptr->tipo()]=ptr;
}
Pulizia::StaticTableInit::~StaticTableInit(){ delete ptr; }
Pulizia::StaticTableInit Pulizia::a;

Pulizia::Pulizia(const std::string& b, const std::string& n, const std::string& p, float cap, float cons): ConsumableItem(b,n,cap, cons), parteDelCorpo(p){}

void Pulizia::serialize(QXmlStreamWriter& writer) const{
    writer.writeStartElement("BeautyItem");
    writer.writeAttribute("tipo", QString::fromStdString(tipo()));

    writer.writeStartElement("marca");
    writer.writeCharacters(QString::fromStdString(getMarca()));
    writer.writeEndElement();
    writer.writeStartElement("nome");
    writer.writeCharacters(QString::fromStdString(getNome()));
    writer.writeEndElement();
    writer.writeStartElement("parteDelCorpo");
    writer.writeCharacters(QString::fromStdString(getParteDelCorpo()));
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
Pulizia* Pulizia::create(QXmlStreamReader& reader) const{
    std::string marca = "No brand";
    std::string nome = "No name";
    std::string parteDelCorpo = "Ovunque";
    float capacita(0);
    float consumo(1);
    if(reader.readNextStartElement() && reader.name()=="marca")
        marca = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="nome")
        nome = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="parteDelCorpo")
        parteDelCorpo = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="capacita")
        capacita = reader.readElementText().toFloat();
    if(reader.readNextStartElement() && reader.name()=="consumo")
        consumo = reader.readElementText().toFloat();
    reader.skipCurrentElement();
    return new Pulizia(marca, nome, parteDelCorpo, capacita, consumo);
}
std::string Pulizia::getParteDelCorpo() const { return parteDelCorpo; }
void Pulizia::setParteDelCorpo(const std::string& p){ parteDelCorpo=p;}
Pulizia* Pulizia::clone() const{ return new Pulizia(*this); }
std::string Pulizia::tipo() const{ return std::string("Pulizia"); }

