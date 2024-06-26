#ifndef MAP_HPP
#define MAP_HPP
/* Map.hpp
 *
 * Abstract data type representing a map of key-value pairs with
 * unique keys. A subset of the std::map interface
 * http://www.cplusplus.com/reference/map/map/
 *
 * By Andrew DeOrio <awdeorio@umich.edu>
 *    Amir Kamil    <akamil@umich.edu>
 *    James Juett   <jjuett@umich.edu>
 * Updated
 *   2016-11-23
 *
 * DO NOT modify the public interface. Modify anything else you need to.
 */

#include "BinarySearchTree.hpp"
#include <cassert>  //assert
#include <utility>  //pair
using namespace std;

template <typename Key_type, typename Value_type,
          typename Key_compare=std::less<Key_type> // default argument
         >
class Map {

private:
  // Type alias for an element, the combination of a key and mapped
  // value stored in a std::pair.
  // See http://www.cplusplus.com/reference/utility/pair/
  using Pair_type = std::pair<Key_type, Value_type>;

  // A custom comparator
  class PairComp {
    private:
    Key_compare kcomp;
    public:
    bool operator()(Pair_type p1, Pair_type p2) const{
      return kcomp(p1.first,p2.first);
    }
  };

public:

  // OVERVIEW: Maps are associative containers that store elements
  // formed by a combination of a key value and a mapped value,
  // following a specific order.
  //
  // NOTE: This Map should be represented using a BinarySearchTree that
  //       stores (key, value) pairs. See Pair_type above. You will
  //       also need to define an appropriate comparator type (PairComp) for the
  //       BinarySearchTree to use in comparing elements, so that they
  //       are compared based on the key stored in the first member of
  //       the pair, rather than the built-in behavior that compares the
  //       both the key and the value stored in first/second of the pair.

  // Type alias for iterator type. It is sufficient to use the Iterator
  // from BinarySearchTree<Pair_type> since it will yield elements of Pair_type
  // in the appropriate order for the Map.
  using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;

  // EFFECTS : Returns whether this Map is empty.
  bool empty() const{
    return bst.empty();
  }

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
  size_t size() const{
    return _size;
  }

  // EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  // HINT: Since Map is implemented using a BinarySearchTree that stores
  //       (key, value) pairs, you'll need to construct a dummy value
  //       using "Value_type()".
  Iterator find(const Key_type& k) const{
    Pair_type pr;
    pr.first = k;
    pr.second = Value_type();
    return bst.find(pr);
  }

  // MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //
  // HINT:     In the case the key was not found, and you must insert a
  //           new element, use the expression {k, Value_type()} to create
  //           that element. This ensures the proper value-initialization is done.
  //
  // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
  Value_type& operator[](const Key_type& k){
    Iterator it1 = find(k);
    if(it1 != bst.end()){
      return (*it1).second;
    }
    else{
      Pair_type pr;
      pr.first = k;
      pr.second = Value_type();
      _size++;
      it1 = bst.insert(pr);
      return (*it1).second;
    }
  }

  // MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
  std::pair<Iterator, bool> insert(const Pair_type &val){
    if(bst.find(val) == bst.end()){
      _size++;
      pair<Iterator, bool> p;
      p.first = bst.insert(val);
      p.second = true;
      return p;
    }
    else{
      pair<Iterator, bool> p;
      p.first = bst.find(val);
      p.second = false;
      return p;
    }
  }

  // EFFECTS : Returns an iterator to the first key-value pair in this Map.
  Iterator begin() const{
    return bst.begin();
  }

  // EFFECTS : Returns an iterator to "past-the-end".
  Iterator end() const{
    return bst.end();
  }

private:
  BinarySearchTree<Pair_type, PairComp> bst;
  size_t _size;
};

#endif // DO NOT REMOVE!!!
