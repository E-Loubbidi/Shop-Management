#ifndef H_STRUCTITEM
#define H_STRUCTITEM
#include "product/structproduct.h"
typedef struct
{
    int quantity;
    double subTotal;
    Product *product;
}Item;

typedef struct ItemElement
{
  Item *item;
  struct ItemElement *next;
}ItemElement;
#endif