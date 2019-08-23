#ifndef SINGLYLINKEDLISTS_H_INCLUDED
#define SINGLYLINKEDLISTS_H_INCLUDED
#define TYPE int

typedef struct node node;/*defining node because we will use it's pointer nested in it*/
typedef struct node{
TYPE data;
node* next;
}node;

typedef struct{
node* listHead;
node* listTail;
int sizeOfList;
}singlyLinked;


node* newNode(TYPE data);
singlyLinked* newSinglyList();
void addAtHead(TYPE data,singlyLinked* List);
void addAtTail(TYPE data,singlyLinked* List);
TYPE deleteHead(singlyLinked* List);
TYPE deleteTail(singlyLinked* List);
node* getHead(singlyLinked* List);
node* getTail(singlyLinked* List);
TYPE getAtIndex(int index,singlyLinked* List);
node* getNodeAtIndex(int index,singlyLinked* List);
node* searchNode(singlyLinked* List,TYPE data);
void insertAtIndex(TYPE data,int index,singlyLinked*List);
TYPE deleteAtIndexOf(int index,singlyLinked* List);
int getSize(singlyLinked* List);
int isEmpty(singlyLinked* List);
void printList(singlyLinked* List);
#endif // SINGLYLINKEDLISTS_H_INCLUDED
