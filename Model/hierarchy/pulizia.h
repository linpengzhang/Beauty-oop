#ifndef PULIZIA_H
#define PULIZIA_H
#include "consumableitem.h"

class Pulizia: public ConsumableItem {
private:
    class StaticTableInit{
    private:
        Pulizia* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;
    std::string parteDelCorpo;
    virtual Pulizia* create(QXmlStreamReader&) const override;
public:
    Pulizia(const std::string& ="No brand", const std::string& ="No name", const std::string& ="Everywhere", float=0, float=1);

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getParteDelCorpo() const;
    void setParteDelCorpo(const std::string& ="Everywhere");
    virtual std::string tipo() const override;
    virtual Pulizia* clone() const override;
};


#endif // PULIZIA_H
