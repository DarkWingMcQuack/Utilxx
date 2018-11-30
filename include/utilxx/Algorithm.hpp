#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace utilxx {

template<class InputIterator,
         class OutputIterator,
         class UnaryOperation,
         class UnaryPredicate>
OutputIterator transform_if(InputIterator first,
                            InputIterator last,
                            OutputIterator result,
                            UnaryOperation op,
                            UnaryPredicate test)
{
    while(first != last) {
        if(test(*first))
            *result++ = op(*first);
        ++first;
    }
    return result;
}

template<class Key,
         class T,
         class Compare,
         class Alloc,
         class Pred>
void erase_if(std::map<Key, T, Compare, Alloc>& c, Pred pred)
{
    for(auto i = c.begin(), last = c.end(); i != last;) {
        if(pred(*i)) {
            i = c.erase(i);
        } else {
            ++i;
        }
    }
}

template<class T,
         class Compare,
         class Alloc,
         class Pred>
void erase_if(std::set<T, Compare, Alloc>& c, Pred pred)
{
    for(auto i = c.begin(), last = c.end(); i != last;) {
        if(pred(*i)) {
            i = c.erase(i);
        } else {
            ++i;
        }
    }
}

template<class Key,
         class T,
         class Hash,
         class KeyEqual,
         class Alloc,
         class Pred>
void erase_if(std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& c, Pred pred)
{
    for(auto i = c.begin(), last = c.end(); i != last;) {
        if(pred(*i)) {
            i = c.erase(i);
        } else {
            ++i;
        }
    }
}

template<class Key,
         class Hash,
         class KeyEqual,
         class Alloc,
         class Pred>
void erase_if(std::unordered_set<Key, Hash, KeyEqual, Alloc>& c, Pred pred)
{
    for(auto i = c.begin(), last = c.end(); i != last;) {
        if(pred(*i)) {
            i = c.erase(i);
        } else {
            ++i;
        }
    }
}

template<class T,
         class Alloc,
         class Pred>
void erase_if(std::vector<T, Alloc>& c, Pred pred)
{
    c.erase(std::remove_if(c.begin(),
                           c.end(),
                           pred),
            c.end());
}


} // namespace utilxx
