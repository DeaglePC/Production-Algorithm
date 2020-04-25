//
// Created by dupen on 2020/3/28.
//

#ifndef CPP_LRU_H
#define CPP_LRU_H

#include <list>
#include <unordered_map>
#include <iostream>
#include <exception>

namespace proalg {

    class ElemNotExistsException : public std::exception {
    public:
        virtual const char *what() const noexcept {
            return "element is not exists!";
        }
    };

    template<class KEY_T, class VAL_T>
    class LRUCache {
    public:
        explicit LRUCache(unsigned long c);

        VAL_T &put(const KEY_T &k, const VAL_T &v);

        unsigned long Put(const KEY_T &k, const VAL_T &v);

        VAL_T &get(const KEY_T &k);

        VAL_T Get(const KEY_T &k);

        bool IsExists(const KEY_T &k);

        void Clear();

        void SetCapacity(unsigned long c);

        unsigned long GetCapacity() const;

        void DisplayAll() const;

        VAL_T &operator[](const KEY_T &k);

    private:
        std::list<std::pair<KEY_T, VAL_T> > elements;
        std::unordered_map<KEY_T, decltype(elements.begin())> mp;
        unsigned long capacity;
    };

    template<class KEY_T, class VAL_T>
    LRUCache<KEY_T, VAL_T>::LRUCache(unsigned long c): capacity(c) {
    }


    template<class KEY_T, class VAL_T>
    VAL_T &LRUCache<KEY_T, VAL_T>::put(const KEY_T &k, const VAL_T &v) {
        auto it = mp.find(k);

        if (it != mp.end()) {
            // is exists, move it to front
            elements.erase(it->second);
            elements.push_front(make_pair(k, v));
            // save the new elem address in list
            mp[k] = elements.begin();
        } else {
            if (elements.size() < capacity) {
                // just save it
                elements.push_front(make_pair(k, v));
                mp[k] = elements.begin();
            } else {
                // delete the oldest elem
                mp.erase(elements.rbegin()->first);
                elements.pop_back();
                // push new elem
                elements.push_front(make_pair(k, v));
                mp[k] = elements.begin();
            }
        }

        return elements.begin()->second;
    }

    template<class KEY_T, class VAL_T>
    unsigned long LRUCache<KEY_T, VAL_T>::Put(const KEY_T &k, const VAL_T &v) {
        put(k, v);
        return elements.size();
    }


    template<class KEY_T, class VAL_T>
    VAL_T &LRUCache<KEY_T, VAL_T>::get(const KEY_T &k) {
        auto it = mp.find(k);
        if (it != mp.end()) {
            if (it->second != elements.begin()) {
                // is not the first elem
                auto v = it->second->second;
                elements.erase(it->second);
                elements.push_front(make_pair(k, v));
                mp[k] = elements.begin();
            }

            return mp[k]->second;
        }

        throw ElemNotExistsException();
    }

    template<class KEY_T, class VAL_T>
    VAL_T LRUCache<KEY_T, VAL_T>::Get(const KEY_T &k) {
        return get(k);
    }

    template<class KEY_T, class VAL_T>
    bool LRUCache<KEY_T, VAL_T>::IsExists(const KEY_T &k) {
        return !(mp.find(k) == mp.end());
    }


    template<class KEY_T, class VAL_T>
    void LRUCache<KEY_T, VAL_T>::Clear() {
        elements.clear();
        mp.clear();
    }

    template<class KEY_T, class VAL_T>
    void LRUCache<KEY_T, VAL_T>::SetCapacity(unsigned long c) {
        capacity = c;
    }

    template<class KEY_T, class VAL_T>
    unsigned long LRUCache<KEY_T, VAL_T>::GetCapacity() const {
        return capacity;
    }

    template<class KEY_T, class VAL_T>
    void LRUCache<KEY_T, VAL_T>::DisplayAll() const {
        for (const auto &e : elements) {
            std::cout << e.first << ": " << e.second << std::endl;
        }
    }

    template<class KEY_T, class VAL_T>
    VAL_T &LRUCache<KEY_T, VAL_T>::operator[](const KEY_T &k) {
        if (IsExists(k)) {
            return get(k);
        } else {
            return put(k, VAL_T());
        }
    }
}

#endif //CPP_LRU_H
