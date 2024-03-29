
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList
{
public:
   LinkedList();
   LinkedList(LinkedList &other);
   ~LinkedList();

   void add_front(Tile *tile);
   void add_back(Tile *tile);
   void remove_front();
   void remove_back();

   // input index of node
   // deletes node at that index
   // 0 = first, 1 = second, length - 1 = last
   void remove_at_index(int i);
   Node get(int index);
   Tile *get_tile_at_index(int i);
   Tile *get_first_inst(Letter letter);
   void remove_first_inst(Letter letter);

   bool contains(Letter Letter);
   int getSize();

   // get first letter in hand, thats

private:
   Node *head;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
