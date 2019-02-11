#ifndef NONCONSUMABLEITEM_H
#define NONCONSUMABLEITEM_H

#include "beautyitem.h"
class NonConsumableItem: public BeautyItem {
private:
    unsigned int contatore; //contatore delle volte che si usa
    std::string materiale;
public:
    NonConsumableItem(const std::string& ="No brand", const std::string& ="No name", const std::string& = "Materiale ignoto", unsigned int=0);

    virtual bool isConsumable() const final override;
    virtual bool use() override;
    unsigned int getContatore() const;
    std::string getMateriale() const;
    void setMateriale(const std::string& = "Materiale ignoto");
    void setContatore(unsigned int=0);
};

#endif // NONCONSUMABLEITEM_H
