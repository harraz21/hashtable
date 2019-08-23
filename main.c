#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct
{
    int img[784];
    int ID;
} image;
/************************************************struct for hash table linear probing based*****************************************/
typedef struct
{
    image* images;
    int sizeOfTable;
} hashTable;
/**************************************************struct for separate hashing*************************************************/
typedef struct node node;/*defining node because we will use it's pointer nested in it*/
typedef struct node
{
    image* img;
    node* next;
} node;
typedef struct
{
    node* nodes[1000];
    int sizeOfImages;
} hashChainig;
/************************hash function************************/
int hashFunction(image img);
/*******************separate chaining functions***************/
int getImageChaining(image img);
int putImageChaining(image img,int key);
int removeChaining(image img);
/****************linear probing functions*********************/
int getImageProping(image img);
int putImageProb(image img,int key);
int removeProb(image img);
/***********images is table based on linear probing***********/
int collision;
int numberOfcheckings;
hashTable Table;
/*****************************chain*****************************/
hashChainig* hashTableChain;
int collisionChain;
image* images;
/**********************testImage for testing and printing and function print is for printing image******************************/
void printImage(image img);
image testImage;
int main()
{

    collision=0;
    collisionChain=0;
    Table.sizeOfTable=0;
    hashTableChain=(hashChainig*)malloc(sizeof(hashChainig));
    images=(image*)malloc(sizeof(image)*1000);
    Table.images=images;
    FILE* fptr=fopen("MNIST-data(datastructures_assignment3).txt","r");
    image imageReader;
    int i,j,k,h=0;
    struct timeval stop, start;
    for(i=0; i<1000; i++)
        hashTableChain->nodes[i]=NULL;
    hashTableChain->sizeOfImages=0;
    for(i=0; i<1000; i++)
    {
        Table.images[i].ID=-1;
    }
    int ID;
    k=0;
    if(fptr!= NULL)
    {
        int counter=0;
        gettimeofday(&start, NULL);
        while(!feof(fptr))
        {
            for(j=0; j<784; j++)
            {

                fscanf(fptr,"%d\t",&imageReader.img[h]);
                h++;
            }
            fscanf(fptr,"%d\n",&ID);
            imageReader.ID=ID;
            ID=putImageProb(imageReader,imageReader.ID);
           ID=putImageChaining(imageReader,imageReader.ID);
            k++;
            h=0;
        }
        gettimeofday(&stop, NULL);
        fclose(fptr);
    }
    else
        printf("error");
    /***************************************
    size of hash table by chaining :1000
    chain collisions=378

    size of hash table by linear probing=1000
    numbers of collisions in linear probing=(499)****************/
    printf("linear probing took %lu  milliseconds\n", stop.tv_usec - start.tv_usec);
    FILE* reader;
    printf("\n please enter the directory for the file you want to read: \n ");
    char fileName[150];
    gets(fileName);
     fflush(stdin);
    printf("\nloading images....................\n");
    reader=fopen(fileName,"r");
    image imagesTestContainer[5];
    if(reader!=NULL)
    {
        int readingCount=0;
        while(!feof(reader))
        {
            for(i=0; i<784; i++)
            {
                fscanf(reader,"%d ",&imagesTestContainer[readingCount].img[i]);
            }
            imagesTestContainer[readingCount].ID=0;
            printImage(imagesTestContainer[readingCount]);
            readingCount++;
        }
    }
    else
    {
        printf("error opening the file!");
    }
    char option;
    int loop=1;
    while(loop){
    printf("\nplease choose 1 for searching hash table by linear probing and 2 for removing picture!\n1-search for image.\n2-remove image.\n");
    fflush(stdin);
    scanf("%c",&option);
    fflush(stdin);
    switch(option)
    {
    case '1':
        for(i=0; i<5; i++)
        {
            getImageProping(imagesTestContainer[i]);
        }
        break;
    case '2':
        for(i=0; i<5; i++)
        {
            removeProb(imagesTestContainer[i]);
        }
        break;
    default:
        printf("/ninvalid choice! please next time enter the right number!\n");
        break;
    }
    printf("\nplease choose 1 for searching hash table by separate chaining and 2 for removing picture!\n1-search for image.\n2-remove image.");
    scanf("%c",&option);
     fflush(stdin);
    switch(option)
    {
    case '1':
        for(i=0; i<5; i++)
        {
            getImageChaining(imagesTestContainer[i]);
        }
        break;
    case '2':
        for(i=0; i<5; i++)
        {
            removeChaining(imagesTestContainer[i]);
        }
        break;
    default:
        printf("\ninvalid choice! please next time enter the right number!\n");
        break;
    }
    printf("\nto exit press 0 to repeate press any other key!\n");
    scanf("%d",&loop);
    }
    return 0;
}
/***********************************************************************hash function*********************************************************/
int hashFunction(image img)
{
    int i,j,h=0;
    int* hashCode=(int*)malloc(sizeof(int)*28);
    int* sumHashCode=(int*)malloc(sizeof(int));
    for(i=0; i<28; i++)
        hashCode[i]=0;

    for(j=1; j<29; j++)
    {
        for(i=1; i<29; i++)
        {
            hashCode[j-1]=hashCode[j-1]+img.img[h];
            h++;
        }
        hashCode[j-1]=hashCode[j-1]*j;
    }
    sumHashCode[0]=0;
    for(i=0; i<28; i++)
    {
        sumHashCode[0]=sumHashCode[0]+hashCode[i];
    }
    return (sumHashCode[0]%1000);
}
/***************************************************************put linear probing*************************************************************/
int putImageProb(image img,int key)
{
    if(Table.sizeOfTable==1000)
    {
        // printf("table is full");
        exit(-1111);
    }
    else
    {
        int index=hashFunction(img);
        //printf("inserting image (%d)\n",img.ID);
        if(Table.images[index].ID!=-1&&Table.images[index].ID!=-2)
        {
            collision++;
            // printf("collision no.(%d) in index [%d] it has element (%d)\n",collision,index,Table.images[index].ID);
        }
        while(Table.images[index].ID!=-1&&Table.images[index].ID!=-2)
        {

            // printf("collision in index(%d) it has (%d)\n",index,Table.images[index].ID);
            index=(index+1)%1000;/**so that if index 999 has collision it gets back to index 0**/
            numberOfcheckings++;
        }
        int i=0;
        //printf("inserting (%d) successfully in index[%d]\n",img.ID,index);
        for(i=0; i<784; i++)
        {
            Table.images[index].img[i]=img.img[i];
        }
        Table.images[index].ID=key;
        Table.sizeOfTable++;
        return Table.images[index].ID;
    }
}
/**********************************************************get linear probing*******************************************************/
int getImageProping(image img)
{
    int index=hashFunction(img);
    int count=0;
    while(Table.images[index].ID!=-1&&count!=1000)
    {
        int i,flag=0;
        for(i=0; i<784; i++)
        {
            if(img.img[i]!=Table.images[index].img[i])
            {
                flag =0;
                break;
            }
            flag=1;
        }
        if(flag==1)
        {
            printf("\n image %3d found!\n",Table.images[index].ID);
            return img.ID;
        }
        count++;
        index=(index+1)%1000;
    }
    printf("\nimage not found!\n");
    return -1;
}
/***************************************************Remove linear probing***************************************************/
int removeProb(image img)
{
    int index=hashFunction(img);
    int count=0;
    int flag=1;
    int i;
    while(Table.images[index].ID!=-1&&count!=1000)
    {
        flag=0;
        for(i=0; i<784; i++)
        {

            if(img.img[i]!=Table.images[index].img[i])
            {
                flag=0;
                break;
            }
            flag=1;
        }
        if(flag==1)
        {
            int key=Table.images[index].ID;
            int i;
            for(i=0; i<784; i++)
            {
                Table.images[index].img[i]=0;
            }
            Table.images[index].ID=-2;
            printf("\n deleted image:%3d\n",key);
            Table.sizeOfTable--;
            return key;
        }
        else
        {
            count++;
            index=(index+1)%1000;
        }
    }
    printf("\nimage not found!\n");
    return -1;
}
/****************************************************************printing any image***************************************************************/
void printImage(image img)
{
    int i,j,h=0;
    int* hashCode=(int*)malloc(sizeof(int)*28);
    for(i=0; i<28; i++)
        hashCode[i]=0;
    printf("\t\t\t\t****ID:%d****\n\t\t-----------------------------------------------------------------------------\n",img.ID);
    printf("                 ");
    for(i=1; i<29; i++)
        printf("%3d ",i);
    printf("\n");
    for(j=1; j<29; j++)
    {
        printf("(%2d):\t\t ",(j));
        for(i=1; i<29; i++)
        {
            if(img.img[h]==0)
                printf("    ");
            else
                printf("%3d ",img.img[h]);
            hashCode[j-1]=hashCode[j-1]+img.img[h];
            h++;
        }
        hashCode[j-1]=hashCode[j-1]*j;
        printf("\nsumFactor: %d\n",hashCode[j-1]);
    }
}
/*************************************************put separate chaining*************************************************************/
int putImageChaining(image img,int key)
{
    hashTableChain->sizeOfImages++;
    int index=hashFunction(img);
    if(hashTableChain->nodes[index]==NULL)
    {
        hashTableChain->nodes[index]=malloc(sizeof(node));
        hashTableChain->nodes[index]->img=(image*)malloc(sizeof(image));
        int i;
        for(i=0; i<784; i++)
        {
            hashTableChain->nodes[index]->img->img[i]=img.img[i];
        }
        hashTableChain->nodes[index]->img->ID=key;
        hashTableChain->nodes[index]->next=NULL;
        //printf("***********%3d**********in index[%3d]\n",key,index);
        return hashTableChain->nodes[index]->img->ID;
    }
    else
    {
        collisionChain++;
        // printf("collision! number %3d at index[%3d]\n",collisionChain,index);
        node* node=hashTableChain->nodes[index];
        while(node->next!=NULL&&node->next->img->ID!=-2)
        {
            node=node->next;
        }
        node->next=malloc(sizeof(node));
        node->next->img=(image*)malloc(sizeof(image));
        int i;
        for(i=0; i<784; i++)
        {
            node->next->img->img[i]=img.img[i];
        }
        node->next->img->ID=key;
        return key;
    }
}
/*********************************************get image by chaining*****************************/
int getImageChaining(image img)
{
    int flag=0;
    int i;
    node* node;
    int index=hashFunction(img);
    node=hashTableChain->nodes[index];
    if(hashTableChain->nodes[index]==NULL)
    {
        printf("\nimage not found!\n");
        return -1;
    }
    else
    {
        while(node!=NULL)
        {
            flag=0;
            for(i=0; i<784; i++)
            {
                if(img.img[i]!=node->img->img[i])
                {
                    flag=0;
                    break;
                }
                flag=1;
            }
            if(flag==1)
            {
                int key=node->img->ID;
                printf("\nimage %3d found!\n",key);
                return key;
            }
            node=node->next;
        }
    }
    printf("\nimage not found!\n");
    return -1;
}
/***************************************************remove chaining*********************************/
int removeChaining(image img)
{
    int flag=0;
    int i;
    node* node;
    int index=hashFunction(img);
    node=hashTableChain->nodes[index];
    if(hashTableChain->nodes[index]==NULL)
    {
        printf("\nimage not found!\n");
        return -1;
    }
    else
    {
        while(node!=NULL)
        {
            flag=0;
            for(i=0; i<784; i++)
            {
                if(img.img[i]!=node->img->img[i])
                {
                    flag=0;
                    break;
                }
                flag=1;
            }
            if(flag==1)
            {
                int key=node->img->ID;
                printf("\nimage %3d deleted\n",key);
                node->img->ID=-2;
                for(i=0; i<784; i++)
                {
                    node->img->img[i]=0;
                }
                hashTableChain->sizeOfImages=hashTableChain->sizeOfImages-1;
                return key;
            }
            node=node->next;
        }
    }
    printf("\nimage not found!\n");
    return -1;
}




















