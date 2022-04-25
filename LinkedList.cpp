
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() {
   head = nullptr;
   length = 0;

   // TODO
}

LinkedList::~LinkedList() {
}

void LinkedList::add_front(Tile* tile) {
   Node* node = new Node(tile, head);
   head = node;
   length = length + 1;

}

void LinkedList::add_back(Tile* tile) {
   Node* node = new Node(tile, nullptr);
   
   if (head == nullptr) {
      add_front(tile);
   }
   else {
      Node* curr_node = head;
      while (curr_node->next != nullptr) {

         curr_node = curr_node->next;
         
      }
      curr_node->next = node;
      length = length + 1;
   }
}

void LinkedList::remove_front() {

   if (head == nullptr) {
      // do nothing
   }
   else if (head->next == nullptr) {
         head = nullptr;
         length -= 1;
      }
   else {
      Node* toDel = head;
      head = head->next;

      delete toDel;
      length -= 1;

   }
}

void LinkedList::remove_back() {
   if (head != nullptr) {
      Node* curr_node = head;
      if (head->next == nullptr) {
         delete head;
         head = nullptr;
         length -= 1;
      }
      while (curr_node->next->next != nullptr) {
         curr_node = curr_node->next;
      }
      delete curr_node->next;

      length -= 1;
   }
}

Tile* LinkedList::get_tile_at_index(int index) {
   if (head == nullptr) {
      throw std::runtime_error("Empty list");
   }
   else if (index < length){
      Node* curr_node = head;

      for (int i = index + 1; i < length; ++i) {
         curr_node = curr_node->next;
      }
      return curr_node->tile;
   }
}

void LinkedList::remove_at_index(int index) {
   if (head == nullptr) {
      throw std::runtime_error("Empty list");
   }
   if (index == 0) {
      remove_front();
   }
   else if (index < length){
      Node* curr_node = head;
      Node* prev_node = nullptr;

      for (int i = index + 1; i < length; ++i) {
         curr_node = curr_node->next;
         prev_node = curr_node;
      }
      prev_node->next = curr_node->next;
      delete curr_node;
      length -= 1;
   }
}
}