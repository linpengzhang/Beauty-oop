#include "consumableitem.h"

ConsumableItem::ConsumableItem(const std::string& b, const std::string& n, float cap, float cons): BeautyItem(b,n), capacita(cap), consumo(cons){}
float ConsumableItem::getCapacita() const{ return capacita; }
float ConsumableItem::getConsumo() const{ return consumo; }
void ConsumableItem::setConsumo(float c){ consumo = c;}
void ConsumableItem::setCapacita(float c){ capacita = c;}

bool ConsumableItem::use(){
    if(capacita>0){
        capacita = (capacita>consumo)?capacita-consumo:0;
        return true;
    } return false;
}
bool ConsumableItem::isConsumable() const { return true;}
bool ConsumableItem::isEmpty() const { return capacita==0;}
