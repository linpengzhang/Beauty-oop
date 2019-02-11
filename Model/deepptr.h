#ifndef DEEPPTR_H
#define DEEPPTR_H
template <class T>
class DeepPtr{
private:
    T* p;
public:
    DeepPtr(T* = nullptr); //costruttore che non crea una copia profonda
    DeepPtr(const DeepPtr&); //copia grazie alla clonazione polimorfa in T
    DeepPtr& operator=(const DeepPtr&);
    T* operator->() const;
    T& operator*() const;
    ~DeepPtr(); //distruzione polimorfa grazie al distruttore virtuale in T
};
template<class T>
DeepPtr<T>::DeepPtr(T* q): p(q){}
template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dp): p(dp.p!=nullptr?dp.p->clone():nullptr){}
template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dp){
    if(this!=&dp){
        if(p) delete p; //distruzione polimorfa implementata in T
        p = (dp.p!=nullptr?(dp.p)->clone():nullptr);
    }
    return *this;    
}
template<class T>
T* DeepPtr<T>::operator->() const{
    return p;
}
template<class T>
T& DeepPtr<T>::operator*() const{
    return *p;
}
template<class T>
DeepPtr<T>::~DeepPtr(){ if(p) delete p; }

#endif // DEEPPTR_H
