#ifndef MODELLO_H
#define MODELLO_H

#include "container.h"
#include "deepptr.h"
#include "hierarchy/beautyitem.h"
#include <vector>

class Model
{
private:
    Container<DeepPtr<BeautyItem>> contenitore;
public:
    Model() = default;
    ~Model() = default;
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string&);
    unsigned int count() const;
    void add(BeautyItem*); // aggiunge un BeautyItem in coda
    void remove(unsigned int); // c.remove(i) rimuove il BeautyItem di indice i
    bool use(unsigned int);
    BeautyItem* operator[] (unsigned int) const; //m[i] restituisce un puntatore al beautyitem di indice i
    BeautyItem* getBeautyItem(unsigned int) const; //m.getBeautyItem(i) restituisce un puntatore al beautyitem di indice i
    void useIndexes(const std::vector<unsigned int> &); //m.useIndexes(v) usa *m[i] sse v è ordinato e i è contenuto in v
    //per usi futuri
    void removeIndexes(const std::vector<unsigned int> &);  //m.removeIndexes(v) rimuove *m[i] sse v è ordinato i è contenuto in v
    void removeType(const std::string& s);
    void removeBrand(const std::string& s);
};

#endif // MODELLO_H
