#if !defined(LIST_HEADER)
#define LIST_HEADER

#include "Node.hxx"
#include "Forward_Declarations.hxx"
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
    Node<T>* Search(T Item) const;
    Node<T>* operator[](unsigned requested_index ) const;

    // Remove methods
    void Remove(T Item);
    void Remove(Node<T>* CurrentNode);

    // Getter methods
    unsigned GetLength() const { return (*this).Length; }
}; // class List {


// Destructor
template <typename T>
Linked_List<T>::~Linked_List() {
  /* Before we can let the list go, we need to free each item in the list.
  We do this by starting at the head and work our way back. */
  Node<T>* CurrentNode = Head;
  while(CurrentNode != nullptr) {
    Node<T>* Next = CurrentNode->GetNext();
    delete CurrentNode;
    CurrentNode = Next;
  } // while(CurrentNode != nullptr) {
} // Linked_List<T>::~Linked_List() {



////////////////////////////////////////////////////////////////////////////////
// Insertion methods

template <typename T>
void Linked_List<T>::Append(T Item) {
  /* To append the item onto the list, we first create a new node to hold the
  new item and then make that node the new tail of the list. */

  Node<T>* New_Tail = new Node<T>{Item};

  /* If the list is currently empty (Length == 0) then the new node is both the
  head and tail. Otherwise, it is just the new head */
  if((*this).Length == 0) {
    (*this).Tail = New_Tail;
    (*this).Head = New_Tail;
  } // if((*this).Length == 0) {
  else {
    New_Tail->Prev = (*this).Tail;
    (*this).Tail->Next = New_Tail;
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
    New_Head->Next = (*this).Head;
    (*this).Head->Prev = New_Head;
    (*this).Head = New_Head;
  } // else {

  /* Increment length */
  (*this).Length++;
} // void Linked_List<T>::Prepend(T Item) {



////////////////////////////////////////////////////////////////////////////////
// Searching/Access methods

template <typename T>
Node<T>* Linked_List<T>::Search(T Item) const {
  /* This method is used to find an item in the list. If there is a node in
  the list with the specified Item then we return the address of that node.
  If no such node can be found, nullptr is returned.

  The searching process works using a linear searching algorithm. This is the
  only option since we're using a linked list. Even if the data was sorted,
  there would be no way to implement a binary searching algorithm. */
  Node<T>* CurrentNode = (*this).Head;
  while(CurrentNode != nullptr) {
    /* Check if the current nodes's item matches the requested item. If so,
    return the current nodes's address. */
    if(CurrentNode->GetItem() == Item ) { return CurrentNode; }
    else { CurrentNode = CurrentNode->GetNext(); }
  } // while(CurrentNode != nullptr){

  // If we got here then that means the item is not in the list. Return -1
  return nullptr;
} // Node<T>* Linked_List<T>::Search(T Item) {


template <typename T>
Node<T>* Linked_List<T>::operator[](unsigned requested_index ) const {
  // the requested index must be less than the length of the list
  assert(requested_index < (*this).Length );

  /* Cycle through the list until we get to the node with the requested index.
  Return its value */
  Node<T>* CurrentNode = (*this).Head;
  for(unsigned index = 0; index < requested_index; index++) { CurrentNode = CurrentNode->GetNext(); }
  return CurrentNode;
} // T& Linked_List<T>::operator[](unsigned requested_index ) {



////////////////////////////////////////////////////////////////////////////////
// Remove methods

template <typename T>
void Linked_List<T>::Remove(T Item) {
  /* This method will remove all items from the list whose items match Item.
  if no such items exist, then there are no changes. If one or more items match
  the specified item then all are removed. */

  Node<T>* CurrentNode = (*this).Head;
  while(CurrentNode != nullptr) {
    // Check if the current node's item matches the specified item.
    if(CurrentNode->GetItem() == Item) {
      /* If so then we need to remove this node. If this node happens to be the
      head then we need to update the Head. Otherwise, bypass the current node. */
      if(CurrentNode == (*this).Head) {
        /* If this node also happens to be the tail, then both the head and the
        tail need to be set to nullptr. Otherwise, we just need to update Head */
        if(CurrentNode == (*this).Tail) { (*this).Head = (*this).Tail = nullptr; }
        else {
          Node<T>* NextNode = (*this).Head->GetNext();
          (*this).Head = NextNode;
          NextNode->Prev = nullptr;
        } // else {
      } // if(CurrentNode == (*this).Head) {
      else {
        Node<T>* PrevNode = CurrentNode->GetPrev();

        /* If the current node is also the tail (but not the head), then we need
        to update the tail. Otherise, bypass the current node. */
        if(CurrentNode == (*this).Tail) {
          PrevNode->Next = nullptr;
          (*this).Tail = PrevNode;
        } // if(CurrentNode == (*this).Tail) {
        else {
          Node<T>* NextNode = CurrentNode->GetNext();
          PrevNode->Next = NextNode;
          NextNode->Prev = PrevNode;
        } // else {
      } // else {

      /* In either case, delete current node and update the List's length.
      Then, updated current node to the next node in the list. */
      Node<T>* NextNode = CurrentNode->GetNext();
      delete CurrentNode;
      (*this).Length--;
      CurrentNode = NextNode;
    } // if(CurrentNode->GetItem() == Item) {
    else { CurrentNode = CurrentNode->GetNext(); }
  } // while(CurrentNode != nullptr) {
} // void Linked_List<T>::Remove(T Item) {


template <typename T>
void Linked_List<T>::Remove(Node<T>* CurrentNode) {
  /* This method removes the specified node from the list. */
  Node<T>* NextNode = CurrentNode->Next;
  Node<T>* PrevNode = CurrentNode->Prev;

  /* First, if the to-be-removed node has a next node then have it point to the
  previous node (rather than the current node). Likewise, if to-be-removed node
  has a previous node then make it point to the Next node (rather than the
  current node) */
  if(NextNode != nullptr) { NextNode->Prev = PrevNode; }
  if(PrevNode != nullptr) { PrevNode->Next = NextNode; }

  /* Now, check if the current node is the Head or Tail. If it's the head then
  make the head point to the next node. If it's the tail then make the tail
  point to the previous node.

  Note: If it exists, the next node's prev pointer has already been set to null
  Likewise, if it exists, the previous node's next point has already been set to
  null. Thus, the next (prev) pointer is ready to be the new head (tail) */
  if((*this).Head == CurrentNode) { (*this).Head = NextNode; }
  if((*this).Tail == CurrentNode) { (*this).Tail = PrevNode; }

  /* Now, delete the current node */
  delete CurrentNode;
  (*this).Length--;
} // void Linked_List<T>::Remove(Node<T>* CurrentNode) {

#endif
