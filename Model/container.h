#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <limits.h>
#include <algorithm>
template <class T>
class Container{
public:
    class iterator;
    class const_iterator;
private:
    T* v;
    unsigned int _capacity;
    unsigned int _size;
    T* copy(unsigned int, unsigned int) const; //v.copy(n,c) restituisce un array a[0..c] tale che a[0..n]==v[0..n]
    static void destroy(T* v);
public:
    class iterator{
        friend class Container;
    private:
        T* p;
        iterator(T* =0);
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;
        operator void*() const;
        T& operator*() const;
        T& operator[](unsigned int) const;
        T* operator->() const;
        iterator& operator+=(int);
        iterator& operator-=(int);
        iterator operator+(int) const;
        iterator operator-(int) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(const const_iterator&);
        iterator& operator-=(const const_iterator&);
        iterator operator+(const const_iterator&) const;
        iterator operator-(const const_iterator&) const;
        bool operator<(const const_iterator &) const;
        bool operator>(const const_iterator &) const;
        bool operator<=(const const_iterator &) const;
        bool operator>=(const const_iterator &) const;
        bool operator==(const const_iterator &) const;
        bool operator!=(const const_iterator &) const;
    };
    class const_iterator{
        friend class Container;
    private:
        const T* p;
        const_iterator(const T* =0);
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;
        const_iterator(const iterator&);
        operator void*() const;
        const T& operator*() const;
        const T& operator[](unsigned) const;
        const T* operator->() const;
        const_iterator& operator+=(int);
        const_iterator& operator-=(int);
        const_iterator operator+(int) const;
        const_iterator operator-(int) const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator<(const const_iterator &) const;
        bool operator>(const const_iterator &) const;
        bool operator<=(const const_iterator &) const;
        bool operator>=(const const_iterator &) const;
        bool operator==(const const_iterator &) const;
        bool operator!=(const const_iterator &) const;
    };
    static unsigned int max_size();
    Container(unsigned int=1, unsigned int=0);
    Container(unsigned int, const T&);

    Container(const Container&); //costruttore di copia profondo
    Container& operator=(const Container&); //assegnazione profonda
    ~Container(); //distruzione profonda

    T& operator[](unsigned int);
    const T& operator[](unsigned int) const;
    bool operator==(const Container&) const;
    bool operator<(const Container&) const;
    bool operator>(const Container&) const;
    bool operator<=(const Container&) const;
    bool operator>=(const Container&) const;
    unsigned int size() const;
    unsigned int capacity() const;
    bool empty() const;
    void clear();
    void push_back(const T&);
    void pop_back();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    iterator insert(iterator, const T&);
    void insert(iterator, int, const T&);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    iterator begin();
    iterator end();
    iterator search(const T&);
    bool removeFirst(const T&t); //rimuove la prima occorrenza dell'elemento t
    bool removeAll(const T&t); //rimuove tutte le occorrenze di t
    const_iterator search(const T&) const;
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
};

template<class T>
T* Container<T>::copy(unsigned n, unsigned c) const{ //v.copy(n,c) restituisce un array a[0..c] tale che a[0..n]==v[0..n]
    if(n<=c && n<=_size){
        T* p= new T[c];
        std::copy(v,v+n,p);
        return p;
    } else return nullptr;
}
template<class T>
void Container<T>::destroy(T* v){
    if(v) delete[] v;
}

//INIZIO ITERATOR
template<class T>
Container<T>::iterator::iterator(T* p): p(p){}
template<class T>
Container<T>::iterator::operator void*() const {
    return p;
}
template<class T>
T& Container<T>::iterator::operator*() const {
    return *p;
}
template<class T>
T& Container<T>::iterator::operator[](unsigned int x) const {
    return *(p+x);
}
template<class T>
T* Container<T>::iterator::operator->() const {
    return &p;
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(int x) {
    p+=x;
    return*this;
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(int x) {
    p-=x;
    return *this;
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator+(int x) const {
    return iterator(p+x);
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator-(int x) const {
    return iterator(p-x);
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    ++p;
    return *this;
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) {
    iterator temp=iterator(*this);
    ++p;
    return temp;
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator--() {
    --p;
    return *this;
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int) {
    iterator temp=iterator(*this);
    --p;
    return temp;
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(const const_iterator& it) {
    p+=it.p-p;
    return *this;
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(const const_iterator& it) {
    p-=it.p-p;
    return *this;
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator+(const const_iterator& it) const {
    return iterator(p+it.p);
}
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator-(const const_iterator& it) const {
    return iterator(p-it.p);
}
template<class T>
bool Container<T>::iterator::operator<(const const_iterator& it) const{
    return p<it.p;
}
template<class T>
bool Container<T>::iterator::operator>(const const_iterator& it) const{
    return p>it.p;
}
template<class T>
bool Container<T>::iterator::operator<=(const const_iterator& it) const{
    return p<=it.p;
}
template<class T>
bool Container<T>::iterator::operator>=(const const_iterator& it) const{
    return p>=it.p;
}
template<class T>
bool Container<T>::iterator::operator==(const const_iterator& it) const{
    return p==it.p;
}
template<class T>
bool Container<T>::iterator::operator!=(const const_iterator& it) const{
    return p!=it.p;
}

//INIZIO CONST_ITERATOR
template<class T>
Container<T>::const_iterator::const_iterator(const T* p): p(p){}
template<class T>
Container<T>::const_iterator::const_iterator(const iterator& it): p(it.p){}
template<class T>
Container<T>::const_iterator::operator void*() const {
    return p;
}
template<class T>
const T& Container<T>::const_iterator::operator*() const {
    return *p;
}
template<class T>
const T& Container<T>::const_iterator::operator[](unsigned int x) const {
    return *(p+x);
}
template<class T>
const T* Container<T>::const_iterator::operator->() const {
    return &p;
}
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator+=(int x) {
    p+=x;
    return*this;
}
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator-=(int x) {
    p-=x;
    return *this;
}
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator+(int x) const {
    return const_iterator(p+x);
}
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator-(int x) const {
    return const_iterator(p-x);
}
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
    ++p;
    return *this;
}
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) {
    const_iterator temp=const_iterator(*this);
    ++p;
    return temp;
}
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--() {
    --p;
    return *this;
}
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int) {
    const_iterator temp=const_iterator(*this);
    --p;
    return temp;
}
template<class T>
bool Container<T>::const_iterator::operator<(const const_iterator& it) const{
    return p<it.p;
}
template<class T>
bool Container<T>::const_iterator::operator>(const const_iterator& it) const{
    return p>it.p;
}
template<class T>
bool Container<T>::const_iterator::operator<=(const const_iterator& it) const{
    return p<=it.p;
}
template<class T>
bool Container<T>::const_iterator::operator>=(const const_iterator& it) const{
    return p>=it.p;
}
template<class T>
bool Container<T>::const_iterator::operator==(const const_iterator& it) const{
    return p==it.p;
}
template<class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& it) const{
    return p!=it.p;
}

/* INIZIO Container */
template <class T>
Container<T>::Container(unsigned int c, unsigned int s): v(new T[c]),_capacity(c), _size(s){}
template <class T>
Container<T>::Container(unsigned int c, const T& t): v(new T[c]),_capacity(c), _size(c){
    for (int i=0;i<c;++i)
        v[i]=t;
}
template <class T>
Container<T>::Container(const Container<T>& q):v(q.copy(q._size, q._capacity)),_size(q._size),_capacity(q._capacity){}
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& q){
    if(this!=&q){
        destroy(v);
        _capacity=q._capacity;
        _size=q._size;
        v = q.copy(_size, _capacity);
    }
    return *this;
}
template <class T>
Container<T>::~Container(){ destroy(v); }
template<class T>
bool Container<T>::operator==(const Container& q) const{
    if(_size!=q._size) return false;
    unsigned int i=0;
    for(;i<_size && v[i]==q.v[i];++i);
    if(i==_size)
        return true;
    return false;
}
template<class T>
bool Container<T>::operator<(const Container& q) const{
    unsigned int min=_size<q._size?_size:q._size;
    for(unsigned int i=0;i<min;++i)
        if(v[i]!=q.v[i])
            return v[i]<q.v[i];
    return _size<q._size?true:false;
}
template<class T>
bool Container<T>::operator>(const Container& q) const{
    unsigned int min=_size<q._size?_size:q._size;
    for(unsigned int i=0;i<min;++i)
        if(v[i]!=q.v[i])
            return v[i]>q.v[i];
    return _size>q._size?true:false;
}
template<class T>
bool Container<T>::operator<=(const Container& q) const{
    return *this<q || *this==q;
}
template<class T>
bool Container<T>::operator>=(const Container& q) const{
    return *this>q || *this==q;
}
template <class T>
unsigned int Container<T>::max_size(){
    return UINT_MAX;
}
template <class T>
unsigned int Container<T>::size() const{
    return _size;
}
template <class T>
unsigned int Container<T>::capacity() const{
    return _capacity;
}
template <class T>
bool Container<T>::empty() const{
    return !_size;
}
template <class T>
void Container<T>::clear(){
    erase(begin(), end());
}
template <class T>
void Container<T>::push_back(const T& t){
    if(_size>=_capacity){
        _capacity*=2;
        T* temp = copy(_size, _capacity);
        destroy(v);
        v=temp;
    }
    v[_size++]=t;
}
template <class T>
void Container<T>::pop_back(){
    if(_size) _size--;
}
template <class T>
T& Container<T>::front(){
    return *v;
}
template <class T>
T& Container<T>::back(){
    return v[_size-1];
}
template <class T>
const T& Container<T>::front() const{
    return *v;
}
template <class T>
const T& Container<T>::back() const{
    return v[_size-1];
}
template <class T>
typename Container<T>::iterator Container<T>::insert(iterator posizione, const T& t){
    if(_size+1>_capacity){
        int offset = static_cast<int>(posizione.p-v);
        _capacity*=2;
        T* temp = copy(offset, _capacity); //copia [begin(), posizione) sul nuovo array
        temp[offset] = t; //mette l'elemento t nella posizione corretta
        std::copy(posizione, end(), iterator(temp+offset+1)); //copia [posizione, end) sul nuovo array
        destroy(v); ++_size; v=temp;
        return iterator(temp+offset);
    } //_size<_capacity
    ++_size;
    std::copy_backward(posizione, end()-1, end()); //[posizione, end()) viene traslato a destra di 1
    *posizione = t; //mette l'elemento t nella posizione corretta
    return posizione;
}
template <class T>
void Container<T>::insert(iterator posizione, int n, const T& t){
    if(_size+n>_capacity){
        int offset = static_cast<int>(posizione.p-v);
        _capacity = 2*(_size+n);
        T* temp = copy(offset, _capacity); //copia [begin(), posizione) sul nuovo array
        for(int i=0;i<n;++i) //mette gli elementi t nelle giuste posizioni
            temp[offset+i]=t;
        std::copy(posizione, end(), iterator(temp+offset+n)); //copia [posizione, end) sul nuovo array
        destroy(v); _size+=n; v=temp;
    }
    else { //_size+n<=_capacity
        _size+=n;
        std::copy_backward(posizione, end()-n, end()); //[posizione, end()) viene copiato in [posizione+n,end()+n)
        for (int i=0;i<n;++i) //copia gli n elementi in [posizione, posizione+n)
            posizione[i]=t;
    }
}
template<class T>
typename Container<T>::iterator Container<T>::erase(iterator posizione){
    return erase(posizione, posizione+1);
}
template<class T>
typename Container<T>::iterator Container<T>::erase(iterator it1, iterator it2){
    if(!_size) return iterator(0);
    if(it1<begin()) return erase(begin(),it2);
    if(it2>end()) return erase(it1,end());
    std::copy(it2,end(),it1); //copio gli elementi nelle posizioni [it2, end) su it1 in poi
    int offset = static_cast<int>(it2.p-it1.p);
    _size-=offset;
    return it1;
}
template<class T>
typename Container<T>::iterator Container<T>::search(const T & t){
    iterator it = begin();
    for (;it!=end() && *it!=t;++it);
    if(it==end())
        return iterator(0);
    return it;
}
template<class T>
bool Container<T>::removeFirst(const T&t){
    unsigned int oldSize = _size;
    erase(search(t));
    return (_size<oldSize)?true:false;
}
template<class T>
bool Container<T>::removeAll(const T&t){
    unsigned int oldSize = _size;
    std::copy_if(search(t), end(), search(t), [&t,this](T&x)->bool
    {
        if(x!=t) return true;
        this->_size--; return false;
    });
    return (_size<oldSize)?true:false;
}
template<class T>
typename Container<T>::const_iterator Container<T>::search(const T & t) const{
    const_iterator cit = begin();
    for (;cit!=end() && *cit!=t;++cit);
    if(cit==end())
        return const_iterator(0);
    return cit;
}
template <class T>
const T& Container<T>::operator[](unsigned int i) const{
    return v[i];
}
template <class T>
T& Container<T>::operator[](unsigned int i){
    return v[i];
}
template <class T>
typename Container<T>::iterator Container<T>::begin(){
    return iterator(v);
}
template <class T>
typename Container<T>::iterator Container<T>::end(){
    return iterator(v+_size);
}
template <class T>
typename Container<T>::const_iterator Container<T>::begin() const{
    return const_iterator(v);
}
template <class T>
typename Container<T>::const_iterator Container<T>::end() const{
    return const_iterator(v+_size);
}
template <class T>
typename Container<T>::const_iterator Container<T>::cbegin() const{
    return const_iterator(v);
}
template <class T>
typename Container<T>::const_iterator Container<T>::cend() const{
    return const_iterator(v+_size);
}

#endif /* CONTAINER_H */
