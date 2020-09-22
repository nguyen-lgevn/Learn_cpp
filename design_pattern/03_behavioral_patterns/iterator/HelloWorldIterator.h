#ifndef __HELLOWORLD_ITERATOR_H__
#define __HELLOWORLD_ITERATOR_H__

#include "IHelloWorld.h"

namespace design_patterns {

template<class Item>
class Iterator {
public:
    virtual void begin() = 0;
    virtual void next() = 0;
    virtual bool end() const = 0;
    virtual Item currentItem() const = 0;
};

template<class Item>
class List {
public:
    virtual Iterator<Item>* createIterator() const = 0;
    virtual unsigned int size() const = 0;
    virtual void push(Item) = 0;
};

template<class Item>
class HelloWorldIterator;

template<class Item>
class HelloWorldList: public List<Item> {
public:
    Iterator<Item>* createIterator() const {
        return new HelloWorldIterator<Item>(this);
    }

    unsigned int size() const {
        return m_lstItem.size();
    }

    void push(Item _item) {
        m_lstItem.push_back(_item);
    }

    const Item& get(const unsigned int _index) const {
        return m_lstItem.at(_index);
    }

private:
    std::vector<Item> m_lstItem;
};

template<class Item>
class HelloWorldIterator: public Iterator<Item> {
public:
    HelloWorldIterator(const HelloWorldList<Item>* _list): m_ptrList(_list), m_index(0) {}

    void begin() {
        m_index = 0;
    }

    void next() {
        m_index++;
    }

    bool end() const {
        return (m_ptrList->size() <= m_index);
    }

    Item currentItem() const {
        if (end())
            return Item();
        return m_ptrList->get(m_index);
    }

private:
    const HelloWorldList<Item> *m_ptrList;
    unsigned int m_index;
};

} // design_patterns

#endif
