#ifndef H_PRODUCT
#define H_PRODUCT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structproduct.h"

//Products Mangement
//createProduct
Product* createProduct(int code, char *designation, double price)
{
    Product *product;
    product=(Product*)malloc(sizeof(Product));
    product->code=code;
    product->designation=designation;
    product->price=price;
    return product;
}
//createProductElement
ProductElement* createProductElement(Product* product)
{
    ProductElement *newElement;
    newElement=(ProductElement*)malloc(sizeof(ProductElement));
    newElement->product=product;
    newElement->next=NULL;
    return newElement;
}
//findLastAddressProduct
ProductElement *findLastAddressProduct(ProductElement* ProductsList)
{
    ProductElement* lastAddress;
    for(lastAddress=ProductsList;lastAddress->next!=NULL;lastAddress=lastAddress->next);
    return lastAddress;
}
//addToProductsList
void addToProductsList(ProductElement **ProductsList, Product *product)
{
    ProductElement *newElement;
    newElement=createProductElement(product);
    if(*ProductsList==NULL) 
    {
        *ProductsList=newElement;
        return;
    } 

    ProductElement *lastAddress;
    lastAddress=findLastAddressProduct(*ProductsList);
    lastAddress->next=newElement;
}
//addToProductsFile "product.txt"
void addToProductsFile(char *filename, Product *product)
{
    FILE *fp_product;
    fp_product=fopen(filename,"a");
    if(fp_product==NULL)
    {
        printf("Could not open file %s", filename); 
        return;
    }
    fprintf(fp_product,"\n%d %s %.2lf",product->code, product->designation,product->price);
    fclose(fp_product);
}

//count number of lines in a file
int countNBLinesFileProduct(char *filename)
{
    FILE *fp_product;
    char c;
    int count; count=0;
    fp_product=fopen(filename,"r");
    if(fp_product==NULL)
    {
        printf("Could not open file %s", filename); 
        exit(-1); 
    }

    for(c=fgetc(fp_product);c!=EOF;c=fgetc(fp_product))
    {
        if(c=='\n') count++;
    }
    fclose(fp_product);
    return count;
}

//import data product from file "product.txt" to ProductsList
void initDataProducts(ProductElement **ProductsList, char *filename, int NBProduct)
{
    FILE *fp_product;
    fp_product=fopen(filename,"r");
    int i=1;
    int code;
    char S[50], *designation; designation=NULL;
    double price;
    Product *product;

    if (fp_product == NULL) 
    { 
        printf("Could not open file %s", filename); 
        exit(-1); 
    } 

    fseek(fp_product, 22, SEEK_SET);
    
    while(i<=NBProduct)
    {
        fscanf(fp_product,"%d",&code);
        fscanf(fp_product,"%s",S);
        designation=(char*)malloc(sizeof(char)*strlen(S));
        strcpy(designation,S);
        fscanf(fp_product,"%lf",&price);
    
        product=createProduct(code, designation, price);
        addToProductsList(ProductsList,product);
        i++;
    }
    
    fclose(fp_product);
}
//displayProductDetail
void displayProductDetail(Product* product)
{
    printf("Code of product : %d\n",product->code);
    printf("Designation : %s\n",product->designation);
    printf("Price : %.2lf\n",product->price);
}
//dispalyProductsList
void dispalyProductsList(ProductElement *ProductsList)
{
    ProductElement* p;
    printf("\n-------Products List-------\n");
    for(p=ProductsList;p!=NULL;p=p->next)
        displayProductDetail(p->product);
}
//getProduct
Product* getProduct(ProductElement *ProductsList, int code)
{
    ProductElement* p;
    for(p=ProductsList;p!=NULL;p=p->next)
        if(p->product->code==code) return p->product;
    return NULL;
}

void deleteProduct(ProductElement** ProductsList, int code)
{
    if(*ProductsList==NULL)
    {
        printf("the list is empty\n");
        return;
    }

    Product *product;
    product=getProduct(*ProductsList,code);

    if(product==NULL)
    {
        printf("This product doesn't exist\n");
        return;
    }

    ProductElement *tmp,*p;

    if((*ProductsList)->product==product)
    {
        tmp=*ProductsList;
        *ProductsList=(*ProductsList)->next;
        free(tmp);
        return;
    }

    tmp=*ProductsList;
    for(p=(*ProductsList)->next;p!=NULL;p=p->next)
    {
        if(p->product==product)
        {
            tmp->next=p->next;
            free(p);
            return;
        }
        tmp=p;
    }
}

#endif