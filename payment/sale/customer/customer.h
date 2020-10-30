#ifndef H_CUSTOMER
#define H_CUSTOMER
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "structcustomer.h"

//Customers Management

Customer* createCustomer(int code, char *surname, char *firstname, char *phonenumber)
{
    Customer *customer;
    customer=(Customer*)malloc(sizeof(Customer));
    customer->code=code;
    customer->surname=surname;
    customer->firstname=firstname;
    customer->phonenumber=phonenumber;
    return customer;
}

CustomerElement* createCustomerElement(Customer* customer)
{
    CustomerElement *newElement;
    newElement=(CustomerElement*)malloc(sizeof(CustomerElement));
    newElement->customer=customer;
    newElement->next=NULL;
    return newElement;
}

CustomerElement* findsurAddressCustomer(CustomerElement *CustomersList)
{
    CustomerElement *surAddress;
    for(surAddress=CustomersList;surAddress->next!=NULL;surAddress=surAddress->next);
    return surAddress;
}

void addToCustomersList(CustomerElement **CustomersList, Customer *customer)
{
    CustomerElement *newElement;
    newElement=createCustomerElement(customer);

    if(*CustomersList==NULL)
    {
        *CustomersList=newElement;
        return;
    }

    CustomerElement *surAddress;
    surAddress=findsurAddressCustomer(*CustomersList);
    surAddress->next=newElement;
}

//addToCustomerssFile "customer.txt"
void addToCustomersFile(char *filename, Customer *customer)
{
    FILE *fp_customer;
    fp_customer=fopen(filename,"a");
    if(fp_customer==NULL)
    {
        printf("Could not open file %s", filename); 
        return;
    }
    fprintf(fp_customer,"\n%d %s %s %s",customer->code, customer->surname,customer->firstname,customer->phonenumber);
    fclose(fp_customer);
}

//count number of lines in a file
int countNBLinesFileCustomer(char *filename)
{
    FILE *fp_customer;
    char c;
    int count; count=0;
    fp_customer=fopen(filename,"r");
    if(fp_customer==NULL)
    {
        printf("Could not open file %s", filename); 
        exit(-1); 
    }

    for(c=fgetc(fp_customer);c!=EOF;c=fgetc(fp_customer))
    {
        if(c=='\n') count++;
    }
    fclose(fp_customer);
    return count;
}

//import data customer from file "customer.txt" to CustomersList
void initDataCustomers(CustomerElement **CustomersList, char *filename, int NBCustomer)
{
    FILE *fp_customer;
    fp_customer=fopen(filename,"r");
    int i=1;
    int code;
    char S[50], *surname, *firstname, *phonenumber;
    Customer *customer;

    if (fp_customer == NULL) 
    { 
        printf("Could not open file %s", filename); 
        exit(-1); 
    } 

    fseek(fp_customer, 25, SEEK_SET);
    
    while(i<=NBCustomer)
    {
        fscanf(fp_customer,"%d",&code);
        fscanf(fp_customer,"%s",S);
        surname=(char*)malloc(sizeof(char)*strlen(S));
        strcpy(surname,S);
        fscanf(fp_customer,"%s",S);
        firstname=(char*)malloc(sizeof(char)*strlen(S));
        strcpy(firstname,S);
        fscanf(fp_customer,"%s",S);
        phonenumber=(char*)malloc(sizeof(char)*strlen(S));
        strcpy(phonenumber,S);
    
        customer=createCustomer(code, surname, firstname, phonenumber);
        addToCustomersList(CustomersList,customer);
        i++;
    }
    
    fclose(fp_customer);
}

void displayCustomerDetail(Customer *customer)
{
    printf("\n-------Customer Detail-------\n");
    printf("Code of customer : %d\n",customer->code);
    printf("surname : %s\n",customer->surname);
    printf("firstname : %s\n",customer->firstname);
    printf("phonenumber : %s\n",customer->phonenumber);
}

void dispalyCustomersList(CustomerElement *CustomersList)
{
    CustomerElement *p;
    for(p=CustomersList;p!=NULL;p=p->next)
        displayCustomerDetail(p->customer);
}

Customer* getCustomer(CustomerElement *CustomersList, int code)
{
    CustomerElement *p;
    for(p=CustomersList;p!=NULL;p=p->next)
        if(p->customer->code==code) return p->customer;
    return NULL;
}

void deleteCustomer(CustomerElement **CustomersList, int code)
{
    if(*CustomersList==NULL)
    {
        printf("the list is empty\n");
        return;
    }

    Customer *customer;
    customer=getCustomer(*CustomersList,code);

    if(customer==NULL)
    {
        printf("This customer doesn't exist\n");
        return;
    }

    CustomerElement *tmp,*p;

    if((*CustomersList)->customer==customer)
    {
        tmp=*CustomersList;
        *CustomersList=(*CustomersList)->next;
        free(tmp);
        return;
    }

    tmp=*CustomersList;
    for(p=(*CustomersList)->next;p!=NULL;p=p->next)
    {
        if(p->customer==customer)
        {
            tmp->next=p->next;
            free(p);
            return;
        }
        tmp=p;
    }
}
#endif