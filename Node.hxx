#if !defined(NODE_HEADER)
#define NODE_HEADER

template <typename T>
class Node {
  private:
    T Item;
    Node<T>* Next;
  public:
    // Constructor, destricutor
    Node(T Item): Item(Item), Next(nullptr) {}
    ~Node() {}

    // Getter and setter methods
    void SetItem(T New_Item) { Item = New_Item; };
    T GetItem() const { return Item; }
    void SetNext(Node<T>* Next) { (*this).Next = Next; }
    Node<T>* GetNext() const { return Next; }
}; // class Node {

#endif
