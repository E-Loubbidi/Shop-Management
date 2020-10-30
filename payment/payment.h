#ifndef H_PAYMENT
#define H_PAYMENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sale/structpayment.h"

//Payment Management

Payment* createPayment(int paymentCode, double amount, char *type, Date date, Sale *sale)
{
    Payment *payment;
    payment=(Payment*)malloc(sizeof(Payment));
    payment->paymentCode=paymentCode;
    payment->amount=amount;
    payment->type=type;
    payment->date=date;
    payment->sale=sale;
    return payment;
}

PaymentElement* createPaymentElement(Payment* payment)
{
    PaymentElement *newElement;
    newElement=(PaymentElement*)malloc(sizeof(PaymentElement));
    newElement->payment=payment;
    newElement->next=NULL;
    return newElement;
}

PaymentElement* findLastAddressPayment(PaymentElement *PaymentsList)
{
    PaymentElement *lastAddress;
    for(lastAddress=PaymentsList;lastAddress->next!=NULL;lastAddress=lastAddress->next);
    return lastAddress;
}

void addToPaymentsList(PaymentElement **PaymentsList, Payment *payment)
{
    PaymentElement *newElement;
    newElement=createPaymentElement(payment);

    if(*PaymentsList==NULL)
    {
        *PaymentsList=newElement;
        return;
    }

    PaymentElement *lastAddress;
    lastAddress=findLastAddressPayment(*PaymentsList);
    lastAddress->next=newElement;
}

//addToPaymentsFile "payment.txt"
void addToPaymentsFile(char *filename, Payment *payment)
{
    FILE *fp_payment;
    fp_payment=fopen(filename,"a");
    if(fp_payment==NULL)
    {
        printf("Could not open file %s", filename);
        return;
    }
    fprintf(fp_payment,"\n%d %.2lf %s %d %d %d",payment->paymentCode, payment->amount, payment->type,payment->date.day,payment->date.month,payment->date.year);
    fclose(fp_payment);
}

//count number of lines in a file
int countNBLinesFilePayment(char *filename)
{
    FILE *fp_payment;
    char c;
    int count; count=0;
    fp_payment=fopen(filename,"r");
    if(fp_payment==NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    for(c=fgetc(fp_payment);c!=EOF;c=fgetc(fp_payment))
    {
        if(c=='\n') count++;
    }
    fclose(fp_payment);
    return count;
}

//import data payment from file "payment.txt" to SalesList
void initDataPayments(PaymentElement **PaymentsList, char *filename, int NBPayment)
{
    FILE *fp_payment;
    fp_payment=fopen(filename,"r");
    int i=1;
    int codePayment;
    Date date;
    double amount;
    char S[50],*type;
    Payment *payment;

    if (fp_payment == NULL)
    {
        printf("Could not open file %s", filename);
        exit(-1);
    }

    fseek(fp_payment, 28, SEEK_SET);

    while(i<=NBPayment)
    {
        fscanf(fp_payment,"%d",&codePayment);
        fscanf(fp_payment,"%lf",&amount);
        fscanf(fp_payment,"%s",S);
        type=(char*)malloc(sizeof(char)*strlen(S));
        strcpy(type,S);
        fscanf(fp_payment,"%d",&date.day);
        fscanf(fp_payment,"%d",&date.month);
        fscanf(fp_payment,"%d",&date.year);

        payment=createPayment(codePayment, amount, type, date, NULL);
        addToPaymentsList(PaymentsList, payment);
        i++;
    }

    fclose(fp_payment);
}

void displayPaymentDetail(Payment *payment)
{
    printf("\n------Detail Payment-------\n");
    printf("Code of Payment : %d\n",payment->paymentCode);
    printf("Date : %d/%d/%d\n",payment->date.day,payment->date.month,payment->date.year);
    printf("Type : %s\n",payment->type);
    printf("Amount : %.2lf\n",payment->amount);
    //displaySaleDetail(payment->sale);
}

void dispalyPaymentsList(PaymentElement *PaymentsList)
{
    PaymentElement *p;
    for(p=PaymentsList;p!=NULL;p=p->next)
        displayPaymentDetail(p->payment);
}

Payment* getPayment(PaymentElement* PaymentsList, int code)
{
    PaymentElement *p;
    for(p=PaymentsList;p!=NULL;p=p->next)
        if(p->payment->paymentCode==code) return p->payment;
    return NULL;
}

void deletePayment(PaymentElement **PaymentsList, int code)
{
    if(PaymentsList==NULL)
    {
        printf("The payments list is empty\n");
        return;
    }

    Payment *payment;
    payment=getPayment(*PaymentsList,code);

    if(payment==NULL)
    {
        printf("This payment doesn't exist\n");
        return;
    }

    PaymentElement *tmp,*p;

    if((*PaymentsList)->payment==payment)
    {
        tmp=*PaymentsList;
        *PaymentsList=(*PaymentsList)->next;
        free(tmp);
        return;
    }

    tmp=*PaymentsList;
    for(p=(*PaymentsList)->next;p!=NULL;p=p->next)
    {
        if(p->payment==payment)
        {
            tmp->next=p->next;
            free(p);
            return;
        }
        tmp=p;
    }
}

//SumAmount
double SumAmount(PaymentElement *PaymentsList)
{
    double Sumamount; Sumamount=0;
    PaymentElement* p;
    for(p=PaymentsList;p!=NULL;p=p->next)
        Sumamount+=p->payment->amount;
    return Sumamount;
}
#endif
