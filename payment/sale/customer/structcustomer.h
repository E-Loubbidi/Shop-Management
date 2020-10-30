#ifndef H_STRUCTCUSTOMER
#define H_STRUCTCUSTOMER

typedef struct
{
    int code;
    char *surname;
    char *firstname;
    char *phonenumber;
}Customer;

typedef struct CustomerElement
{
    Customer* customer;
    struct CustomerElement *next;
}CustomerElement;
#endif