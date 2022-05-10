
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList()
{
   head = nullptr;
   length = 0;

   // TODO
}
LinkedList::LinkedList(LinkedList &other)
{
   head = nullptr;
   for (int i = 0; i < other.length; ++i)
   {
      Tile *tile = new Tile(*other.get_tile_at_index(i));
      add_back(tile);
   }
}

LinkedList::~LinkedList()
{
   length = 0;
   Node *nodePtr = head;
   while (nodePtr != nullptr)
   {
      Node *next = nodePtr->next;
      delete nodePtr;
      nodePtr = next;
   }
   head = nullptr;
}

void LinkedList::add_front(Tile *tile)
{
   Node *node = new Node(tile, head);
   head = node;
   length = length + 1;
}

void LinkedList::add_back(Tile *tile)
{
   Node *node = new Node(tile, nullptr);

   if (head == nullptr)
   {
      head = node;
   }
   else
   {
      Node *curr_node = head;
      while (curr_node->next != nullptr)
      {

         curr_node = curr_node->next;
      }
      curr_node->next = node;
      length = length + 1;
   }
}

void LinkedList::remove_front()
{

   if (head == nullptr)
   {
      // do nothing
   }
   else
   {
      Node *toDel = head;
      head = head->next;

      delete toDel;
      length -= 1;
   }
}

void LinkedList::remove_back()
{
   if (head != nullptr)
   {
      Node *curr_node = head;
      if (head->next == nullptr)
      {
         delete head;
         head = nullptr;
         length -= 1;
      }
      while (curr_node->next->next != nullptr)
      {
         curr_node = curr_node->next;
      }
      delete curr_node->next;

      length -= 1;
   }
}

Tile *LinkedList::get_tile_at_index(int index)
{
   Tile *retTile = nullptr;
   if (head == nullptr)
   {
      throw std::runtime_error("Empty list");
   }
   else if (index < length)
   {
      Node *curr_node = head;

      for (int i = 0; i < index; ++i)
      {
         curr_node = curr_node->next;
      }
      retTile = curr_node->tile;
   }
   return retTile;
}

void LinkedList::remove_at_index(int index)
{
   if (head == nullptr)
   {
      throw std::runtime_error("Empty list");
   }
   if (index == 0)
   {
      remove_front();
   }
   else if (index < length)
   {
      Node *curr_node = head;
      Node *prev_node = nullptr;

      for (int i = 0; i < index; ++i)
      {
         prev_node = curr_node;
         curr_node = curr_node->next;
      }
      prev_node->next = curr_node->next;
      delete curr_node;
      length -= 1;
   }
}

int LinkedList::getSize()
{
   return length;
}

Tile *LinkedList::get_first_inst(Letter letter)
{
   bool found = false;
   Tile *retTile = nullptr;
   if (head == nullptr)
   {
      throw std::runtime_error("Empty list");
   }
   else
   {
      Node *curr_node = head;

      for (int i = 0; i < length && !found; ++i)
      {
         if (curr_node->tile->getLetter() == letter && !found)
         {
            retTile = curr_node->tile;
            found = true;
         }
         curr_node = curr_node->next;
      }
   }
   return retTile;
}

void LinkedList::remove_first_inst(Letter letter)
{
   bool found = false;
   Node *prev_node = nullptr;
   Node *cur_node = head;
   if (head->tile->getLetter() == letter)
   {
      head = head->next;
      delete cur_node;
   }
   else
   {
      while (cur_node != nullptr && !found)
      {
         if (cur_node->tile->getLetter() == letter)
         {
            prev_node->next = cur_node->next;
            delete cur_node;
            found = true;
         }
         prev_node = cur_node;
         cur_node = cur_node->next;
      }
   }
   length--;
}
bool LinkedList::contains(Letter letter)
{
   bool ret = false;
   if (get_first_inst(letter) != nullptr)
   {
      ret = true;
   }
   return ret;
}
