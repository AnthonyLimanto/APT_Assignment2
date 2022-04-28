
#include "Node.h"

Node::Node(Tile *tile, Node *next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node &other)
{
   tile = new Tile(*other.tile);
   next = other.next;
}

Node::~Node()
{
   delete tile;
   next = nullptr;
}
