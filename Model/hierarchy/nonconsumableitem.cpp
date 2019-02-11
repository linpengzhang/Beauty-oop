#include "nonconsumableitem.h"

NonConsumableItem::NonConsumableItem(const std::string&b, const std::string&n, const std::string& m,unsigned int u): BeautyItem(b,n), materiale(m), contatore(u) {}

unsigned int NonConsumableItem::getContatore() const{ return contatore; }
std::string NonConsumableItem::getMateriale() const{ return materiale; }

bool NonConsumableItem::use(){
    contatore++;
    return true;
}
bool NonConsumableItem::isConsumable() const { return false;}
void NonConsumableItem::setContatore(unsigned int i) { contatore = i;}
void NonConsumableItem::setMateriale(const std::string& m) { materiale=m; }
