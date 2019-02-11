#ifndef BEAUTYITEM_H
#define BEAUTYITEM_H
#include <map>
#include <string>
class QXmlStreamReader;
class QXmlStreamWriter;

class BeautyItem
{
private:
    std::string marca;
    std::string nome;
    virtual BeautyItem* create(QXmlStreamReader&) const = 0;
protected:
    static std::map<std::string,BeautyItem*> table;
public:
    BeautyItem(const std::string& ="No brand", const std::string& ="No name");
    std::string getMarca() const;
    std::string getNome() const;
    void setMarca(const std::string& = "No brand");
    void setNome(const std::string& = "No name");

    virtual std::string tipo() const = 0;
    virtual bool use() = 0;
    virtual bool isConsumable() const = 0;
    virtual BeautyItem* clone() const = 0;
    virtual ~BeautyItem() = default;

    //SERIALIZZAZIONE
    static BeautyItem* unserialize(QXmlStreamReader&);
    virtual void serialize(QXmlStreamWriter&) const = 0;
};


#endif // BEAUTYITEM_H
