#ifndef CONSUMABLEITEM_H
#define CONSUMABLEITEM_H

#include "beautyitem.h"
class ConsumableItem: public BeautyItem {
private:
    float capacita; //ml
    float consumo; //ml
public:
    ConsumableItem(const std::string& ="No brand", const std::string& ="No name", float=0, float=1);

    virtual bool use() override;
    virtual bool isConsumable() const final override;
    float getCapacita() const;
    float getConsumo() const;
    void setCapacita(float = 0);
    void setConsumo(float = 0);
    bool isEmpty() const;
};

#endif // CONSUMABLEITEM_H
