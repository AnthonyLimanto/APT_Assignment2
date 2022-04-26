
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"


class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void add_front(Tile*);
   void add_back(Tile* tile);


   void remove_front();
   void remove_back();

   // input index of node
   // deletes node at that index
   // 0 = first, 1 = second, length - 1 = last
   void remove_at_index(int i);
   Tile* get_tile_at_index(int i);

   int getSize();

   // get first letter in hand, thats

private:
   Node* head;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
