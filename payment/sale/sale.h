#ifndef H_SALE
#define H_SALE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structpayment.h"

//Sale Management

Sale* createSale(int SaleCode, Date date, Customer* customer)
{
    Sale* sale;
    sale=(Sale*)malloc(sizeof(Sale));
    sale->saleCode=SaleCode;
    sale->date=date;
    sale->itemList=NULL;
    sale->customer=customer;
    sale->total=0;
    sale->PaymentsList=NULL;
    return sale;
}

double calculateTotalSale(ItemElement* ItemsList)
{
    ItemElement *p;
    double total=0;
    for(p=ItemsList;p!=NULL;p=p->next)
        total+=p->item->subTotal;
    return total;
}

SaleElement* createSaleElement(Sale *sale)
{
    SaleElement *newElement;
    newElement=(SaleElement*)malloc(sizeof(SaleElement));
    newElement->sale=sale;
    newElement->next=NULL;
    return newElement;
}

SaleElement* findLastAddressSale(SaleElement *SalesList)
{
    SaleElement *lastAddress;
    for(lastAddress=SalesList;lastAddress->next!=NULL;lastAddress=lastAddress->next);
    return lastAddress;
}

void addToSalesList(SaleElement **SalesList,Sale *sale)
{
    SaleElement *newElement;
    newElement=createSaleElement(sale);

    if(*SalesList==NULL)
    {
        *SalesList=newElement;
        return;
    }

    SaleElement *lastAddress;
    lastAddress=findLastAddressSale(*SalesList);
    lastAddress->next=newElement;
}

//addToSalssFile "sale.txt"
void addToSalesFile(char *filename, Sale *sale)
{
    FILE *fp_sale;
    fp_sale=fopen(filename,"a");
    if(fp_sale==NULL)
    {
        printf("Could not open file %s", filename);
        return;
    }
    fprintf(fp_sale,"\n%d %d %d %d %.2lf",sale->saleCode, sale->date.day,sale->date.month,sale->date.year,sale->total);
    fclose(fp_sale);
}

//count number of lines in a file
int countNBLinesFileSale(char *filename)
{
    FILE *fp_sale;
    char c;
    int count; count=0;
    fp_sale=fopen(filename,"r");
    if(fp_sale==NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    for(c=fgetc(fp_sale);c!=EOF;c=fgetc(fp_sale))
    {
        if(c=='\n') count++;
    }
    fclose(fp_sale);
    return count;
}

//import data sale from file "sale.txt" to SalesList
void initDataSales(SaleElement **SalesList, CustomerElement *customersList, char *filename, int NBsale)
{
    FILE *fp_sale;
    fp_sale=fopen(filename,"r");
    int i=1;
    int codeSale,codeCustomer;
    Date date;
    double total;
    Customer *customer;
    Sale *sale;

    if (fp_sale == NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    fseek(fp_sale, 32, SEEK_SET);

    while(i<=NBsale)
    {
        fscanf(fp_sale,"%d",&codeSale);
        fscanf(fp_sale,"%d",&date.day);
        fscanf(fp_sale,"%d",&date.month);
        fscanf(fp_sale,"%d",&date.year);
        fscanf(fp_sale,"%lf",&total);
        fscanf(fp_sale,"%d",&codeCustomer);
        customer=getCustomer(customersList,codeCustomer);
        sale=createSale(codeSale, date, customer);
        sale->total=total;
        addToSalesList(SalesList, sale);
        i++;
    }

    fclose(fp_sale);
}

void displaySaleDetail(Sale *sale)
{
    //printf("\n-------Sale Detail------\n");
    printf("\n\nCode of Sale : %d\n",sale->saleCode);
    //printf("Date : %d/%d/%d\n",sale->date.day,sale->date.month,sale->date.year);
    displayItemsList(sale->itemList);
    //printf("\n--------------Total : %.2lf\n",sale->total);
    //displayCustomerDetail(sale->customer);
}

void displaySalesList(SaleElement *SalesList)
{
    if(SalesList==NULL)
    {
        printf("The Sales List is empty\n");
        return;
    }
    SaleElement *p;
    printf("\n-------Sales List-------\n");
    for(p=SalesList;p!=NULL;p=p->next)
        displaySaleDetail(p->sale);
}

Sale* getSale(SaleElement *SalesList, int saleCode)
{
    SaleElement *p;
    for(p=SalesList;p!=NULL;p=p->next)
        if(p->sale->saleCode==saleCode) return p->sale;
    return NULL;
}

void deleteSale(SaleElement **SalesList, int saleCode)
{
    if(*SalesList==NULL)
    {
        printf("the list is empty\n");
        return;
    }

    Sale *sale;
    sale=getSale(*SalesList,saleCode);

    if(sale==NULL)
    {
        printf("This sale doesn't exist\n");
        return;
    }

    SaleElement *tmp,*p;

    if((*SalesList)->sale==sale)
    {
        tmp=*SalesList;
        *SalesList=(*SalesList)->next;
        free(tmp);
        return;
    }

    tmp=*SalesList;
    for(p=(*SalesList)->next;p!=NULL;p=p->next)
    {
        if(p->sale==sale)
        {
            tmp->next=p->next;
            free(p);
            return;
        }
     tmp=p;
    }
}
#endif
