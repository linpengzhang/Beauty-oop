#ifndef STRUMENTO_H
#define STRUMENTO_H

#include "nonconsumableitem.h"

class Strumento: public NonConsumableItem {
private:
    class StaticTableInit{
    private:
        Strumento* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;
    std::string parteDelCorpo;
    virtual Strumento* create(QXmlStreamReader&) const override;
public:
    Strumento(const std::string& ="No brand", const std::string& ="No name", const std::string& ="Ovunque", const std::string& ="Materiale ignoto", unsigned int=0);

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getParteDelCorpo() const;
    void setParteDelCorpo(const std::string& ="Everywhere");
    virtual std::string tipo() const override;
    virtual Strumento* clone() const override;
};
#endif // STRUMENTO_H
