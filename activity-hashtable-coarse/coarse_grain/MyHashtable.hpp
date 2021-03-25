#ifndef _MY_HASHTABLE_H
#define _MY_HASHTABLE_H

#include <functional>
#include <iostream>
#include <vector>

template<class K, class V>
struct Node {
  K key;
  V value;
  Node* next;

  Node(const K& key, const V& value)
    : key(key), value(value), next(nullptr)
  {}

  Node() = default;
  ~Node() = default;
};

template<class K, class V>
class MyHashtable : public Dictionary<K, V> {
protected:
  typedef typename Dictionary<K, V>::dict_iter dict_iter;

  int capacity;
  int count;
  double loadFactor;
  std::vector<Node<K,V>*> table;

  struct hashtable_iter : public dict_iter {
    MyHashtable& mt;
    int bucket;
    Node<K,V>* cur;

    hashtable_iter() = default;
    virtual ~hashtable_iter() = default;

    void advance() {
      if (cur != nullptr) {
        cur = cur->next;
      }
      
      if (cur == nullptr) {
	      if (bucket == mt.capacity) return;
	      bucket++;
	      //need to advance to the next valid entry
	      while (bucket < mt.capacity && mt.table[bucket] == nullptr) {
	        bucket++;
	      }
	      if (bucket < mt.capacity) cur = mt.table[bucket];
	      else cur = nullptr;
      }
    }

    hashtable_iter (MyHashtable& myhash, int buck, Node<K,V>*ptr)
      : mt(myhash), bucket(buck), cur(ptr) {
      if (cur == nullptr) advance();
    }

    
    virtual bool operator==(dict_iter& ite) {
      hashtable_iter& a = dynamic_cast<hashtable_iter&>(ite);
      return bucket == a.bucket && cur == a.cur;
    }
    virtual bool operator!=(dict_iter& ite) {
      hashtable_iter& a = dynamic_cast<hashtable_iter&>(ite);
      return bucket != a.bucket || cur != a.cur;
    }
    virtual dict_iter& operator++() {
      advance();
      return *this;
    }
    virtual std::pair<K,V> operator*() {
      return std::make_pair(cur->key, cur->value);
    }
  };

  void resize(int capacity) {
    //Note that this function works by creating a brand new hashtable
    //and stealing its data at the end. This causes more memory
    //allocation than are really necessary as we could reuse all the
    //node objects without having a create a single new one.
    auto temp_table = MyHashtable(capacity, this->loadFactor);

    for (auto node : this->table) {
      while (node != nullptr) {
	      temp_table.set(node->key, node->value);
	        if (node->next == nullptr) break;
          node = node->next;
      }
    }
    //It is important to swap because we want the nodes in this and in
    //temp_table to be swapped so as to free the memory appropriately.
    std::swap(this->capacity, temp_table.capacity);
    std::swap(this->table, temp_table.table); 
  }

public:
  /**
   * Returns the node at key
   * @param key key of node to get
   * @return node of type Node at key
   */
  virtual V get(const K& key) const {
    std::size_t index = std::hash<K>{}(key) % this->capacity;
    index = index < 0 ? index + this->capacity : index;
    const Node<K,V>* node = this->table[index];

    while (node != nullptr) {
      if (node->key == key)
	      return node->value;
      node = node->next;
    }
    return V();
  }

  /**
   * sets the value of node at key with value
   * @param key key of node to be set
   * @param value new value of node
   */
  virtual void set(const K& key, const V& value) {
    std::size_t index = std::hash<K>{}(key) % this->capacity;
    index = index < 0 ? index + this->capacity : index;
    Node<K,V>* node = this->table[index];
    
    while (node != nullptr) {
      if (node->key == key) {
	      node->value = value;
	      return;
      }
      node = node->next;
    }

    //if we get here, then the key has not been found
    node = new Node<K,V>(key, value);
    node->next = this->table[index];
    this->table[index] = node;
    this->count++;
    if (((double)this->count)/this->capacity > this->loadFactor) {
      this->resize(this->capacity * 2);
    }
  }

  /**
   * deletes the node at given key
   * @param key key of node to be deleted
   */
  virtual void deleteKey(const K& key) {
  }

  MyHashtable(): MyHashtable(100000, 10.0) {}
  MyHashtable(int capacity): MyHashtable(capacity, 10.0) {}
  MyHashtable(int capacity, double loadFactor): capacity(capacity), count(0), loadFactor(loadFactor) {
    
    this->table.resize(capacity, nullptr);
  }

  virtual ~MyHashtable() {    
    for (auto p : table) {
      auto cur = p;
      while (cur != nullptr) {
	      auto n = cur->next;
	      delete cur;
	      cur = n;
      }
    }
  }

  virtual std::unique_ptr<dict_iter> realBegin() {
    return std::make_unique<hashtable_iter>(*this, 0, table[0]);
  }

  virtual std::unique_ptr<dict_iter> realEnd() {
    return std::make_unique<hashtable_iter>(*this, capacity, nullptr);
  }
};

#endif
