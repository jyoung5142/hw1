#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

/**
  * Adds a new value to the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::push_back(const std::string& val)
{
  if(tail_ == NULL)
  {
    Item* temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    head_ = temp;
    tail_ = temp;
  }
  else if (tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  else {
    Item* temp = new Item();
    temp->val[0] = val;
    temp->first = 0;
    temp->last = 1;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
  size_++;
}

  
/**
  * Removes a value from the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_back()
{
  if(tail_ == NULL){
    return;
  }
  //I guess tail only needs to be reassigned if it's empty now
  tail_->last--;
  if(tail_->first == tail_->last){
    Item* value = tail_;
    //If it's the last node
    tail_ = tail_->prev;
    if(tail_ == NULL){
      head_ = NULL;
    }
    else{
      tail_->next = NULL;
    }
    delete(value);
  }
  size_--;
}

/**
  * Adds a new value to the front of the list.
  * If there is room before the 'first' value in
  * the head node add it there, otherwise, 
  * allocate a new head node.
  *   - MUST RUN in O(1)
  */
void ULListStr::push_front(const std::string& val){
   if(head_ == NULL)
    {
      Item* temp = new Item();
      temp->val[0] = val;
      temp->first = 0;
      temp->last = 1;
      head_ = temp;
      tail_ = temp;
    }
    else if (head_->first > 0) {
      head_->first--;
      head_->val[head_->first] = val;
    }
    else {
      Item* temp = new Item();
      temp->val[0] = val;
      temp->first = 0;
      temp->last = 1;
      temp->next = head_;
      head_->prev = temp;
      head_ = temp;
    }
  size_++; 
}
/**
  * Removes a value from the front of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_front(){
  if(head_ == NULL){
    return;
  }
  head_->first++;
  if(head_->first == head_->last){
    Item* value = head_;
    //If it's the last node
    head_ = head_->next;
    if(head_ == NULL){
      tail_ = NULL;
    }
    else{
      head_->prev = NULL;
    }
    delete(value);
  }
  size_--;
}

/**
  * Returns a const reference to the back element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::back() const{
  if(tail_ == NULL){
    return NULL;
  }
  return tail_->val[tail_->last-1];
}

/**
  * Returns a const reference to the front element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::front() const{
  if(head_ == NULL){
    return NULL;
  }
  return head_->val[0];
}

/** 
  * Returns a pointer to the item at index, loc,
  *  if loc is valid and NULL otherwise
  *   - MUST RUN in O(n) 
  */
std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc >= size_){
    return NULL;
  }
  Item* curr = head_;
  while(curr != NULL){
    size_t len = curr->last - curr->first;
    if(len > loc){
      return &(curr->val[curr->first + loc]);
    }
    loc -= len;
    curr = curr->next;
  }
  return NULL;
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
