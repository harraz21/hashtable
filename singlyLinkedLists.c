#include "singlyLinkedLists.h"
#include <stdlib.h>
#include <stdio.h>

node* newNode(TYPE data)
{
    node* newNode=malloc(sizeof(node));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}


singlyLinked* newSinglyList()
{
    singlyLinked* newList=malloc(sizeof(singlyLinked));
    newList->listHead=NULL;
    newList->listTail=NULL;
    newList->sizeOfList=-1;
    return newList;
}


void addAtHead(TYPE data,singlyLinked* List)
{
    node* Node= newNode(data);
    if(isEmpty(List))
    {
        List->listHead=Node;
        List->listTail=Node;
        List->sizeOfList++;
    }
    else
    {
        Node->next=List->listHead;
        List->listHead=Node;
        List->sizeOfList++;
    }
}
void addAtTail(TYPE data,singlyLinked* List)
{
    node* Node=newNode(data);
    if(isEmpty(List))
    {
        List->listHead=Node;
        List->listTail=Node;
        List->sizeOfList++;
    }
    else
    {
        Node->next=NULL;
        List->listTail->next=Node;
        List->listTail=Node;
        List->sizeOfList++;
    }
}
node* getHead(singlyLinked* List)
{
    return List->listHead;
}
node* getTail(singlyLinked* List)
{
    return List->listTail;
}
int isEmpty(singlyLinked* List)
{
    if(List->listHead==NULL&&List->sizeOfList==-1)
        return 1;
    else
        return 0;
}
TYPE getAtIndex(int index,singlyLinked* List)
{
    int i;
    node* temp=List->listHead;
    int stop=getSize(List)-index;
    if(!isEmpty(List)&& !(index<0) && !(getSize(List)<index))
    {
        for(i=0; i<stop; i++)
        {
            temp=temp->next;
        }
        return temp->data;
    }
    else
        exit(1);
}
node* getNodeAtIndex(int index,singlyLinked* List)
{
    int i;
    node* temp=List->listHead;
    int stop=getSize(List)-index;
    if(!isEmpty(List)&& (index >= 0) && (getSize(List)>=index))
    {
        for(i=0; i<stop; i++)
        {
            temp=temp->next;
        }
        return temp;
    }
    else
        exit(5555);
}
TYPE deleteHead(singlyLinked* List)
{
    if(isEmpty(List))
        exit(1);
    TYPE data=List->listHead->data;
    node* deleteed=List->listHead;
    List->listHead=List->listHead->next;
    List->sizeOfList--;
    free(deleteed);
    return data;
}
TYPE deleteTail(singlyLinked* List)
{
    if(isEmpty(List))
        exit(111);
    node* temp;
    if(getSize(List)==0)
    {
        temp=getNodeAtIndex(0,List);
        TYPE data=temp->data;
        List->listHead=NULL;
        List->listTail=NULL;
        List->sizeOfList--;
        return data;
    }
    temp=getNodeAtIndex(1,List);
    TYPE data=temp->next->data;
    temp->next=NULL;
    List->listTail=temp;
    List->sizeOfList--;
    return data;
}
TYPE deleteAtIndexOf(int index,singlyLinked* List)
{
    if(isEmpty(List))
        exit(1);
    if(index<0 || index>getSize(List))
        exit(1);
    if(index==0)
    {
        return deleteTail(List);
    }
    else if(index==getSize(List))
    {
        return deleteHead(List);
    }
    else
    {
        node* deleted=getNodeAtIndex(index,List);
        TYPE data=deleted->data;
        node* beforeDeleted=getNodeAtIndex(index+1,List);
        beforeDeleted->next=deleted->next;
        List->sizeOfList--;
        return data;
    }
}
int getSize(singlyLinked* List)
{
    return List->sizeOfList;
}

void printList(singlyLinked* List)
{
    int i;
    int length=getSize(List)+1;
    for(i=0; i<length; i++)
    {
        printf("(%d).%d\n",i,getAtIndex(i,List));
    }
}

void insertAtIndex(TYPE data,int index,singlyLinked* List)
{

    if(index>(getSize(List)+1))
        exit(1);
    if(index<0)
        exit(1);
    if(index==0)
    {
        addAtHead(data,List);
    }
    else if(index==(getSize(List)+1))
    {
        addAtTail(data,List);
    }
    else
    {
        node* Node=newNode(data);
        node* temp=List->listHead;
        int stop=getSize(List)-index;
        int i;
        for(i=0; i<stop; i++)
        {
            temp=temp->next;
        }
        Node->next=temp->next;
        temp->next=Node;
        List->sizeOfList++;
    }
}

node* searchNode(singlyLinked* List,TYPE data)
{
    if(isEmpty(List))
        exit(1);
    node*temp=List->listHead;
    while(temp)
    {
        if(temp->data!=data)
        {
            temp=temp->next;
        }
        else if(temp->data==data)
        {
            return temp;
        }
    }
    return NULL;
}
