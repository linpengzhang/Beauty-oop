#ifndef PROFUMO_H
#define PROFUMO_H

#include "consumableitem.h"
class Profumo: public ConsumableItem {
private:
    class StaticTableInit{
    private:
        Profumo* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;
    std::string odore;
    virtual Profumo* create(QXmlStreamReader&) const override;
public:
    Profumo(const std::string& ="No brand", const std::string& ="No name", const std::string& ="No info", float=0, float=1);

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getOdore() const;
    void setOdore(const std::string& ="Inodore");
    virtual std::string tipo() const override;
    virtual Profumo* clone() const override;
};

#endif // PROFUMO_H
