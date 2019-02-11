#include "strumento.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
Strumento::StaticTableInit::StaticTableInit(){
    ptr = new Strumento();
    table[ptr->tipo()]=ptr;
}
Strumento::StaticTableInit::~StaticTableInit(){ delete ptr; }
Strumento::StaticTableInit Strumento::a;

Strumento::Strumento(const std::string& b, const std::string& n, const std::string& p, const std::string& m, unsigned int c): NonConsumableItem(b,n,m,c), parteDelCorpo(p){}

void Strumento::serialize(QXmlStreamWriter& writer) const{
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
    writer.writeStartElement("materiale");
    writer.writeCharacters(QString::fromStdString(getMateriale()));
    writer.writeEndElement();
    writer.writeStartElement("contatore");
    writer.writeCharacters(QString::fromStdString(std::to_string(getContatore())));
    writer.writeEndElement();

    writer.writeEndElement();
    if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
        throw std::exception();
}
Strumento* Strumento::create(QXmlStreamReader& reader) const{
    std::string marca = "No brand";
    std::string nome = "No name";
    std::string parteDelCorpo = "Ovunque";
    std::string materiale = "Materiale ignoto";
    unsigned int contatore = 0;
    if(reader.readNextStartElement() && reader.name()=="marca")
        marca = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="nome")
        nome = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="parteDelCorpo")
        parteDelCorpo = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="materiale")
        materiale = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="contatore")
        contatore = reader.readElementText().toUInt();
    reader.skipCurrentElement();
    return new Strumento(marca, nome, parteDelCorpo, materiale, contatore);
}
std::string Strumento::getParteDelCorpo() const { return parteDelCorpo; }
void Strumento::setParteDelCorpo(const std::string& p){ parteDelCorpo = p;}
Strumento* Strumento::clone() const{ return new Strumento(*this); }
std::string Strumento::tipo() const{ return std::string("Strumento"); }

