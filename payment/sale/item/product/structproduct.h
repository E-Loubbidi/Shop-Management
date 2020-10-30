#ifndef H_STRUCTPRODUCT
#define H_STRUCTPRODUCT
//Product Struct
typedef struct
{
    int code;
    char *designation;
    double price;
}Product;

typedef struct ProductElement
{
    Product *product;
    struct ProductElement *next;
}ProductElement;
#endif