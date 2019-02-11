#ifndef MAKEUP_H
#define MAKEUP_H

#include "consumableitem.h"
class MakeUp: public ConsumableItem {
private:
    class StaticTableInit{
    private:
        MakeUp* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;

    std::string colore;
    virtual MakeUp* create(QXmlStreamReader&) const override;
public:
    MakeUp(const std::string& ="No brand", const std::string& ="No name", const std::string& ="Transparent", float=0, float=1);

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getColore() const;
    void setColore(const std::string& = "Transparent");
    virtual std::string tipo() const override;
    virtual MakeUp* clone() const override;
};


#endif // MAKEUP_H
