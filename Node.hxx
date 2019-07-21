#if !defined(NODE_HEADER)
#define NODE_HEADER

#include "Forward_Declarations.hxx"

template <typename T>
class Node {
  friend class Linked_List<T>;
  
  private:
    T Item;
    Node<T>* Next;
  public:
    // Constructor, destricutor
    Node(T Item): Item(Item), Next(nullptr) {}
    ~Node() {}

    // Getter and setter methods
    T GetItem() const { return Item; }
    Node<T>* GetNext() const { return Next; }
}; // class Node {

#endif
