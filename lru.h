//! @file lru.h
//! @author caohw
//! @brief LRU (least recent used)


#ifndef __lru_H__
#define __lru_H__

#include <map>
#include <list>
#include <cassert>

template<typename K, typename P>
class lru
{
public:
  unsigned size() const {assert(_map.size() == _list.size()); return _list.size();}
  P    get(const K& k);
  void put(const K& k, const P& p);
  P    least() const {assert(size()); return _list.back().second;}
  void delLeast();

private:
  typedef std::pair<K, P> pair;
  typedef typename std::list<pair> list;
  typename std::map<K, typename list::iterator> _map;
  list _list;
};


template<typename K, typename P> 
void 
lru<K, P>::put(const K& k, const P& p) 
{
  assert(_map.size() == _list.size());
  assert(_map.find(k) == _map.end()); 
  _list.push_front(pair(k, p)); 
  _map[k] = _list.begin();
}
 
 
template<typename K, typename P> 
P 
lru<K, P>::get(const K& k) 
{
  assert(_map.size() == _list.size());
  const auto i = _map.find(k); 
  if (i == _map.end()) {
    return 0; 
  }
  assert(i->first == k); 
  assert(i->second->first ==k);
  const auto p = i->second->second; 
  _list.erase(i->second); 
  _list.push_front(pair(k, p)); 
  _map[k] = _list.begin(); 
  return p;
}


template<typename K, typename P> 
void 
lru<K, P>::delLeast()
{
  assert(size());
  const auto p = _list.back();
  const auto i = _map.find(p.first);
  assert(i != _map.end());
  assert(i->first == p.first);
  assert(i->second->first == p.first);
  assert(i->second->second == p.second);
  _map.erase(p.first);
  _list.pop_back();
}
 

#endif //__lru_H__

