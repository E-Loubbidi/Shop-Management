#ifndef H_ITEM
#define H_ITEM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product/product.h"
#include "structitem.h"

Item* createItem(Product *product, int quantity)
{
    Item *item;
    item=(Item*)malloc(sizeof(Item));
    item->product=product;
    item->quantity=quantity;
    item->subTotal=product->price*quantity;
    return item;
}

ItemElement *createItemElement(Item *item)
{
    ItemElement *newElement;
    newElement=(ItemElement*)malloc(sizeof(ItemElement));
    newElement->item=item;
    newElement->next=NULL;
    return newElement;
}

ItemElement *findLastAddressItem(ItemElement *ItemsList)
{
    ItemElement *lastAddress;
    for(lastAddress=ItemsList;lastAddress->next!=NULL;lastAddress=lastAddress->next);
    return lastAddress;
}

void addToItemsList(ItemElement **ItemsList, Item *item)
{
    ItemElement *newElement;
    newElement=createItemElement(item);
    if(*ItemsList==NULL)
    {
        *ItemsList=newElement;
        return;
    }
    ItemElement *lastAddress;
    lastAddress=findLastAddressItem(*ItemsList);
    lastAddress->next=newElement;
}

void displayItemDetail(Item *item)
{
    //displayProductDetail(item->product);
    printf("%d %d %.2lf %.2lf\n",item->product->code,item->quantity,item->subTotal,(item->subTotal)+(item->subTotal*0.2));
    //printf("quantity : %d\n",item->quantity);
    //printf("SubTotal : %.2lf\n",item->subTotal);
}

//addToItemsFile "item.txt"
void addToItemsFile(char *filename, Item *item, int codeSale)
{
    FILE *fp_item;
    fp_item=fopen(filename,"a");
    if(fp_item==NULL)
    {
        printf("Could not open file %s", filename);
        return;
    }
    fprintf(fp_item,"\n%d %d %d %.2lf",codeSale, item->product->code, item->quantity,item->subTotal);
    fclose(fp_item);
}

//count number of lines in a file
int countNBLinesFileItem(char *filename)
{
    FILE *fp_item;
    char c;
    int count; count=0;
    fp_item=fopen(filename,"r");
    if(fp_item==NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    for(c=fgetc(fp_item);c!=EOF;c=fgetc(fp_item))
    {
        if(c=='\n') count++;
    }
    fclose(fp_item);
    return count;
}


//import data item to ItemsList
void initDataItems(ItemElement **ItemsList, ProductElement *ProductsList,int codeProduct, int quantity, int subtotal)
{

    Product *product;
    Item *item;

        product=getProduct(ProductsList, codeProduct);
        item=createItem(product, quantity);
        item->subTotal=subtotal;
        addToItemsList(ItemsList,item);

}

void displayItemsList(ItemElement *ItemsList)
{
    ItemElement* p;
    printf("\n-------Items List-------\n");
    for(p=ItemsList;p!=NULL;p=p->next)
        displayItemDetail(p->item);
}

Item* getItem(ItemElement *ItemsList, int code)
{
    ItemElement *p;
    for(p=ItemsList;p!=NULL;p=p->next)
        if(p->item->product->code==code) return p->item;
    return NULL;
}

void deleteItem(ItemElement **ItemsList, int code)
{
    if(*ItemsList==NULL)
    {
        printf("the list is empty\n");
        return;
    }

    Item *item;
    item=getItem(*ItemsList,code);

    ItemElement *tmp,*p;

    if((*ItemsList)->item==item)
    {
        tmp=*ItemsList;
        *ItemsList=(*ItemsList)->next;
        free(tmp);
        return;
    }

    tmp=*ItemsList;
    for(p=(*ItemsList)->next;p!=NULL;p=p->next)
    {
        if(p->item==item)
        {
            tmp->next=p->next;
            free(p);
            return;
        }
        tmp=p;
    }
}
#endif
