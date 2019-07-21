#if !defined(LIST_HEADER)
#define LIST_HEADER

#include "Node.hxx"
#include <assert.h>
#include <stdio.h>

template<typename T>
class Linked_List {
  private:
    Node<T>* Head;
    Node<T>* Tail;
    unsigned Length;
  public:
    // Constructor, destructor
    Linked_List(): Head(nullptr), Tail(nullptr), Length(0) {}
    ~Linked_List();

    // Remove the copy constructor and copy assignment operator
    Linked_List(const Linked_List<T>& ) = delete;
    Linked_List<T>& operator=(const Linked_List<T> &) = delete;

    // Insertion method
    void Append(T Item);
    void Prepend(T Item);

    // Searching/Access methods
    Node<T> const * Search(T Item) const;
    T operator[](unsigned index) const;

    // Remove methods
    void Remove(T Item);

    // Getter methods
    unsigned GetLength() const { return (*this).Length; }
}; // class List {


// Destructor
template <typename T>
Linked_List<T>::~Linked_List() {
  /* Before we can let the list go, we need to free each item in the list.
  We do this by starting at the head and work our way back. */
  Node<T>* Entry = Head;
  while(Entry != nullptr) {
    Node<T>* Next = Entry->GetNext();
    delete Entry;
    Entry = Next;
  } // while(Entry != nullptr) {
} // Linked_List<T>::~Linked_List() {



////////////////////////////////////////////////////////////////////////////////
// Insertion methods

template <typename T>
void Linked_List<T>::Append(T Item) {
  /* To append the item onto the list, we first create a new node to hold the
  new item and then make that node the new tail of the list.

  If the list is currently empty (Length == 0) then the new node is both the
  head and tail. */
  Node<T>* New_Tail = new Node<T>{Item};

  if((*this).Length == 0) {
    (*this).Tail = New_Tail;
    (*this).Head = New_Tail;
  } // if((*this).Length == 0) {
  else {
    (*this).Tail->SetNext(New_Tail);
    (*this).Tail = New_Tail;
  } // else {

  /* Increment length */
  (*this).Length++;
} // void Linked_List<T>::Append(T Item) {


template <typename T>
void Linked_List<T>::Prepend(T Item) {
  /* To Prepend the item onto the list, we first create a new node to hold the
  new item and then make that node the new head of the list.

  If the list is currently empty (Length == 0) then the new node is both the
  head and tail. */
  Node<T>* New_Head = new Node<T>{Item};

  if((*this).Length == 0) {
    (*this).Tail = New_Head;
    (*this).Head = New_Head;
  } // if((*this).Length == 0) {
  else {
    New_Head->SetNext((*this).Head);
    (*this).Head = New_Head;
  } // else {

  /* Increment length */
  (*this).Length++;
} // void Linked_List<T>::Prepend(T Item) {



////////////////////////////////////////////////////////////////////////////////
// Searching/Access methods

template <typename T>
Node<T> const * Linked_List<T>::Search(T Item) const {
  /* This method is used to find an item in the list. If there is a node in
  the list with the specified Item then we return the address of that node.
  If no such node can be found, nullptr is returned.

  The searching process works using a linear searching algorithm. This is the
  only option since we're using a linked list. Even if the data was sorted,
  there would be no way to implement a binary searching algorithm. */
  Node<T> const * Entry = (*this).Head;
  unsigned index = 0;
  while(Entry != nullptr) {
    /* Check if Entry's item matches the requested item. If so, return index.
    Otherwise, move onto the next item. */
    if(Entry->GetItem() == Item ) { return Entry; }
    else {
      index++;
      Entry = Entry->GetNext();
    } // else {
  } // while(Entry != nullptr){

  // If we got here then that means the item is not in the list. Return -1
  return nullptr;
} // Node<T> const * Linked_List<T>::Search(T Item) {


template <typename T>
T Linked_List<T>::operator[](unsigned requested_index ) const {
  // the requested index must be less than the length of the list
  assert(requested_index < (*this).Length );

  /* Cycle through the list until we get to the node with the requested index.
  Return its value */
  Node<T> const * Entry = (*this).Head;
  for(unsigned index = 0; index < requested_index; index++) { Entry = Entry->GetNext(); }
  return Entry->GetItem();
} // T& Linked_List<T>::operator[](unsigned requested_index ) {



////////////////////////////////////////////////////////////////////////////////
// Remove methods

template <typename T>
void Linked_List<T>::Remove(T Item) {
  /* This method will remove all items from the list whose items match Item.
  if no such items exist, then there are no changes. If one or more items match
  the specified item then all are removed. */

  Node<T>* Entry = (*this).Head;
  Node<T>* Prev = nullptr;
  while(Entry != nullptr) {
    // Check if the current entry's item matches the specified item.
    if(Entry->GetItem() == Item) {
      /* If so then we need to remove this node. If this node happens to be
      the head then we need to update the Head. Otherwise, bypass Entry.*/
      if(Entry == (*this).Head) {
        /* If this node also happens to be the tail, then both the head and the
        tail need to be set to nullptr. Otherwise, we just need to update Head */
        if(Entry == (*this).Tail) { (*this).Head = (*this).Tail = nullptr; }
        else { (*this).Head = (*this).Head->GetNext(); }
      } // if(Entry == (*this).Head) {
      else {
        /* If entry is also the tail (but not the head), then we need to update
        the tail. Otherise, bypass Entry. */
        if(Entry == (*this).Tail) {
          Prev->SetNext(nullptr);
          (*this).Tail = Prev;
        } // if(Entry == (*this).Tail) {
        else { Prev->SetNext(Entry->GetNext()); }
      } // else {

      /* In either case, delete Entry and update the List's length. Prev remains
      unchanged while Entry gets updated to the next item in the list.  */
      Node<T>* Next = Entry->GetNext();
      delete Entry;
      (*this).Length--;
      Entry = Next;
    } // if(Entry->GetItem() == Item) {
    else {
      /* If not, update Entry and Prev */
      Prev = Entry;
      Entry = Entry->GetNext();
    } // else {
  } // while(Entry != nullptr) {
} // void Linked_List<T>::Remove(T Item) {

#endif
