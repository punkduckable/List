#if !defined(NODE_HEADER)
#define NODE_HEADER

#include "Forward_Declarations.hxx"

template <typename T>
class Node {
  friend class Linked_List<T>;

  private:
    T Item;
    Node<T>* Next;
    Node<T>* Prev;
  public:
    // Constructor, destricutor
    Node(T Item): Item(Item), Next(nullptr), Prev(nullptr) {}
    ~Node() {}

    // Getter methods
    T GetItem() const { return Item; }
    Node<T>* GetNext() const { return Next; }
    Node<T>* GetPrev() const { return Prev; }
}; // class Node {

#endif
