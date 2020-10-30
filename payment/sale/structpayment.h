#ifndef H_STRUCTPAYMENT 
#define H_STRUCTPAYMENT
#include "item/structitem.h"
#include "customer/structcustomer.h"
#include "date.h"
#include "reglement.h"

typedef struct PaymentElement PaymentElement;

typedef struct
{
    int saleCode;
    double total;
    Date date;
    ItemElement *itemList;
    Customer *customer;
    PaymentElement *PaymentsList;
}Sale;

typedef struct SaleElement
{
    Sale *sale;
    struct SaleElement *next;
}SaleElement;

typedef struct
{
    int paymentCode;
    double amount;
    char *type;
    Cheque *cheque;
    EnLigne *enligne;
    Traite *traite;
    Date date;
    Sale *sale;
}Payment;

typedef struct PaymentElement
{
    Payment *payment;
    struct PaymentElement *next;
}PaymentElement;

#endif