#include "xmlio.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDebug>

XmlIO::XmlIO(const std::string& filepath) : filename(filepath) {}

Container<DeepPtr<BeautyItem>> XmlIO::read() const {
    Container<DeepPtr<BeautyItem>> contenitore;
    QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore di apertura", "Non è stato possibile aprire il file", QMessageBox::Ok);
        return contenitore;
    }
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement() && reader.name() == "root"){
        while(reader.readNextStartElement()) {
            try{
                 contenitore.push_back(BeautyItem::unserialize(reader)); //conversione implicita grazie al costruttore ad un argomento
            } catch(std::string s) {
                QMessageBox box(QMessageBox::Warning, "Errore in lettura", "Qualche elemento potrebbe non essere stato letto correttamente", QMessageBox::Ok);
            }
        }
    }
    file.close();
    return contenitore;
}

void XmlIO::write(const Container<DeepPtr<BeautyItem>>& container) const {
    QSaveFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");
    writer.writeStartElement("root");
    auto citer = container.begin();
    while(citer!= container.end()) {
        (*citer)->serialize(writer);
        ++citer;
    }
    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine
    file.commit(); // Scrive il file temporaneo su disco
}
