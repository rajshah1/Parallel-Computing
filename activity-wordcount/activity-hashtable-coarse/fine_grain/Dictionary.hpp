#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <memory>

template<class K, class V>
class Dictionary {
protected:
  struct dict_iter {
    virtual bool operator==(dict_iter& it) = 0;
    virtual bool operator!=(dict_iter& it) = 0;
    virtual dict_iter& operator++() = 0;
    virtual std::pair<K,V> operator*() = 0;
    virtual ~dict_iter() = default;
  };

  
  virtual std::unique_ptr<dict_iter> realBegin() = 0;
  virtual std::unique_ptr<dict_iter> realEnd() = 0;
  
public:
  class iterator {
    std::unique_ptr<dict_iter> ptr;
  public:
    iterator(std::unique_ptr<dict_iter> pt) {
      this->ptr = std::move(pt);
    }      

    bool operator==(const iterator&i) {
      return this->ptr->operator==(*(i.ptr));
    }

    bool operator!=(const iterator&i) {
      return this->ptr->operator!=(*(i.ptr));
    }
    
    iterator& operator++() {
      this->ptr->operator++();
      return *this;
    }
    
    std::pair<K,V> operator*() {
      return ptr->operator*();
    }
  };
  
  /**
   * Returns the value stored for key
   * @param key key of node to get
   * @return value stored for key
   */
  virtual V get (const K& key) const = 0;

  /**
   * sets the value of node at key with value
   * @param key key of node to be set
   * @param value new value of node
   */
  virtual void set(const K& key, const V& value) = 0;

  /**
   * deletes the node at given key
   * @param key key of node to be deleted
   */
  virtual void deleteKey(const K& key) = 0;

  /**
   * @return an iteration to any dictionary
   */
  iterator begin() {
    return iterator(realBegin());
  }

  /**
   * @return an iteration to any dictionary
   */
  iterator end() {
    return iterator(realEnd());
  }  
  
  virtual ~Dictionary() = default;
};

#endif
