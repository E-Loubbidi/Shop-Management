#include <stdio.h>
#include <conio.h>
#include "payment/sale/item/product/product.h"
#include "payment/sale/customer/customer.h"
#include "payment/sale/item/item.h"
#include "payment/sale/sale.h"
#include "payment/payment.h"

char* returnString()
{
    char S[100], *str;
    scanf("%s",S);
    str=(char*)malloc(sizeof(char)*strlen(S));
    strcpy(str,S);
    return str;
}

char* createString(char *S)
{
    char *str;
    str=(char*)malloc(sizeof(char)*strlen(S));
    strcpy(str,S);
    return str;
}

Sale* returnSale(CustomerElement **CustomersList)
{
    Sale* sale;
    int saleCode, Customercode;
    Date date;
    Customer *customer;
    printf("Enter the code of sale : ");
    scanf("%d",&saleCode);
    printf("Enter the date d/m/y\n");
    printf("Day : ");
    scanf("%d",&date.day);
    printf("Month : ");
    scanf("%d",&date.month);
    printf("Year : ");
    scanf("%d",&date.year);
    printf("Code  of Customer : ");
    scanf("%d",&Customercode);
    customer=getCustomer(*CustomersList, Customercode);
    if(customer==NULL)
    {
        customer=createCustomer(Customercode,NULL,NULL,NULL);
        printf("surname : ");
        customer->surname=returnString();
        printf("First Name : ");
        customer->firstname=returnString();
        printf("Phone Number : ");
        customer->phonenumber=returnString();
        addToCustomersFile("payment/sale/customer/customer.txt", customer);
        addToCustomersList(CustomersList,customer);
    }
    displayCustomerDetail(customer);
    sale=createSale(saleCode, date, customer);
    return sale;
}

Item* returnItem(ProductElement **ProductsList, int code)
{
    Product *product;
    Item *item;
    int quantity;
    double price;
    product=getProduct(*ProductsList,code);
    if(product==NULL)
    {
        printf("This product doesn't exist\nAdd a product :\n");
        printf("Enter the price : ");
        scanf("%lf",&price);
        product=createProduct(code,NULL,price);
        printf("Enter the designation : ");
        product->designation=returnString();
        addToProductsFile("payment/sale/item/product/product.txt",product);
    addToProductsList(ProductsList,product);
    }
    displayProductDetail(product);
    printf("Enter the quantity : ");
    scanf("%d",&quantity);
    item=createItem(product,quantity);
    return item;
}

int ifProductexist(Sale *sale, int code)
{
    ItemElement *p;
    for(p=sale->itemList;p!=NULL;p=p->next)
        if(p->item->product->code==code) return 1;
    return 0;
}

void getSaleForCustomer(SaleElement *SalesList,SaleElement **SaleForCustomer, int codeCustomer)
{
    SaleElement *p;
    for(p=SalesList;p!=NULL;p=p->next)
        if(p->sale->customer->code==codeCustomer) addToSalesList(SaleForCustomer,p->sale);
}

Payment* returnPayment(Sale *sale, double Sumamount)
{
    Payment* payment;
    int PaymentCode,type;
    double amount;
    Date date;
    printf("Enter the code of payment : ");
    scanf("%d",&PaymentCode);
    do
    {
        printf("Amount : ");
        scanf("%lf",&amount);
        if(amount>sale->total-Sumamount) printf("The amount which you have enter is bigger than the rest of payment\n");
    }while(amount>sale->total-Sumamount);
    printf("Enter the date of payment : \n");
    printf("Day : ");
    scanf("%d",&date.day);
    printf("Month : ");
    scanf("%d",&date.month);
    printf("Year : ");
    scanf("%d",&date.year);
    payment=createPayment(PaymentCode, amount, NULL, date, sale);
    printf("---Type---\n");
    printf("1.Cash payment\n");
    printf("2.Payment by check\n");
    printf("3.Online payment\n");
    printf("4.Payment by drafts\n");
    printf("Type : ");
    scanf("%d",&type);
    switch(type)
    {
        case 1 : payment->type=createString("Cash payment"); break;
        case 2 : payment->type=createString("Payment by check");
                 payment->cheque=createCheque(date,payment->sale->customer); break;
        case 3 : payment->type=createString("Online payment");
                 payment->enligne=createEnLigne(date,payment->sale->customer); break;
        case 4 : payment->type=createString("Payment by drafts");
                 payment->traite=createTraite(date,payment->sale->customer);
    }
    return payment;
}

//Menu principal************************

void menuProduct(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList);
void menuCustomer(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList);
void menuSale(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList);
void menuPayment(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList);

void menu(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList)
{
    int choice;
    system("cls");
    printf("\n\n");
    printf("\t\t*********************************************************\n");
    printf("\t\t*\t                                        \t*\n");
    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t*            SHOP MANAGEMENT           *\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t                                        \t*\n");
    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t*          1.Product Management        *\t*\n");
    printf("\t\t*\t*                                      *\t*\n");

    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t*          2.Customer Management       *\t*\n");
    printf("\t\t*\t*                                      *\t*\n");

    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t*          3.Sale Management           *\t*\n");
    printf("\t\t*\t*                                      *\t*\n");

    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t*          4.Payment Management        *\t*\n");
    printf("\t\t*\t*                                      *\t*\n");
    printf("\t\t*\t****************************************\t*\n");
    printf("\t\t*\t                                        \t*\n");
    printf("\t\t*********************************************************\n\n");

    printf("Enter your choice :\n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1 : menuProduct(ProductsList,CustomersList,SalesList); break;
        case 2 : menuCustomer(ProductsList,CustomersList,SalesList); break;
        case 3 : menuSale(ProductsList,CustomersList,SalesList); break;
        case 4 : menuPayment(ProductsList,CustomersList,SalesList); break;
        case 0 : exit(0);
        default :
                    menu(ProductsList,CustomersList,SalesList);  break;
    }
}

//Menu des Produits******************************
void menuProduct(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList)
{
        int code;
    double price;
    Product *product;

    char rep;
    int choix;

//
//    int NBProduct=countNBLinesFileProduct("product.txt");
//    initDataProducts(&ProductsList, "product.txt", NBProduct);
    //dispalyProductsList(ProductsList);

    do
    {system("cls");
            //-------Menu-------
    printf("\n\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n");
    printf("\t*    -------Menu Product-------   *\n");
    printf("\t*                                 *\n");
    printf("\t*       1. Add Product            *\n");
    printf("\t*       2.Display all Products    *\n");
    printf("\t*       3.Display one Product     *\n");
    printf("\t*       4.Delete Product          *\n");
    printf("\t*       0.Return                  *\n");
    printf("\t*                                 *\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n\n");


        printf("Enter your choice : ");
        scanf("%d",&choix);

        switch(choix)
        {
            case 1 : printf("Enter the code of product : ");
                     scanf("%d",&code);
                     printf("Enter the price : ");
                     scanf("%lf",&price);
                     product = createProduct(code,NULL,price);
                     printf("Designation : ");
                     product->designation=returnString();
                     addToProductsList(ProductsList,product);
                     addToProductsFile("payment/sale/item/product/product.txt",product);
                     break;

            case 2 : dispalyProductsList(*ProductsList);
                     break;

            case 3 : printf("Enter the code of product to display : ");
                     scanf("%d",&code);
                     product = getProduct(*ProductsList, code);
                     if(product == NULL)
                     {
                        printf("This product doesn't exist\n");
                        break;
                     }
                     displayProductDetail(product);
                     break;

            case 4 : printf("Enter the code of product to delete : ");
                     scanf("%d",&code);
                     deleteProduct(ProductsList, code);
                     break;

            case 0 : menu(ProductsList,CustomersList,SalesList); break;

            default : printf("This coice is incorrect\n");
                      break;

        }

        getchar();
        printf("Enter y to add a new choice or n to quit\n");
        scanf("%c",&rep);

    }while(rep == 'y' || rep == 'Y');
    menu(ProductsList,CustomersList,SalesList);
}

//Menu des consomateurs**************************
void menuCustomer(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList)
{

    int code;
    Customer *customer;

    char rep;
    int choix;


//      int NBCustomer=countNBLinesFileCustomer("customer.txt");
//    initDataCustomers(&CustomersList, "customer.txt", NBCustomer);
//    dispalyCustomersList(CustomersList);

    do
    {system("cls");

          //-------Menu-------
    printf("\n\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n");
    printf("\t*    -------Menu Customer-------   *\n");
    printf("\t*                                 *\n");
    printf("\t*       1. Add Customer           *\n");
    printf("\t*       2.Display all Customers   *\n");
    printf("\t*       3.Display one Product     *\n");
    printf("\t*       4.Display Customer        *\n");
    printf("\t*       0.Return                  *\n");
    printf("\t*                                 *\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n\n");

        printf("Entrez votre choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
            case 1 : printf("Entrez le code : ");
                     scanf("%d",&code);
                     customer = createCustomer(code,NULL,NULL,NULL);
                     printf("Entrer le nom : ");
                     customer->surname = returnString();
                     printf("Entrer le prenom : ");
                     customer->firstname = returnString();
                     printf("Entrer le numero de telephone : ");
                     customer->phonenumber = returnString();
                     addToCustomersFile("payment/sale/customer/customer.txt", customer);
                     addToCustomersList(CustomersList ,customer);
                     break;

            case 2 : dispalyCustomersList(*CustomersList);
                     break;

            case 3 : printf("Enter the code of customer to display : ");
                     scanf("%d",&code);
                     customer = getCustomer(*CustomersList, code);
                     if(customer == NULL)
                     {
                        printf("This customer doesn't exist\n");
                        break;
                     }
                     displayCustomerDetail(customer);
                     break;

            case 4 : printf("Enter the code of customer to delete : ");
                     scanf("%d",&code);
                     deleteCustomer(CustomersList, code);
                     break;
            case 0 : menu(ProductsList,CustomersList,SalesList); break;

            default : printf("This coice is incorrect\n");
                      break;

        }

        getchar();
        printf("Enter y to add a new choice or n to quit\n");
        scanf("%c",&rep);

    }while(rep == 'y' || rep == 'Y');
    menu(ProductsList,CustomersList,SalesList);
}

//Menu de vente**********************************
void menuSale(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList)
{
    int choix, code;
    char ans;
    Item *item,*existItem;


    do
    {system("cls");
        //-------Menu-------
    printf("\t* * * * * * * * * * * * * * * * * *\n");
    printf("\t       --------Menu Sale--------        \n");
    printf("\t*                                 *\n");
    printf("\t*       1.Create Sale             *\n");
    printf("\t*       2.Display Sale            *\n");
    printf("\t*       3.Display Sales List      *\n");
    printf("\t*       4.Delete item             *\n");
    printf("\t*       5.Delete Sale             *\n");
    printf("\t*       0.Return                  *\n");
    printf("\t*                                 *\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n");
        //dispalyProductsList(*ProductsList);
        printf("Enter your choice\n");
        scanf("%d",&choix);
        Sale *sale;
        switch(choix)
        {
            case 1 : sale=returnSale(CustomersList);
                     do
                     {
                        printf("Enter the code of product : ");
                        scanf("%d",&code);
                        item=returnItem(ProductsList, code);
                        if(ifProductexist(sale,code)==0)
                            addToItemsList(&sale->itemList,item);
                    else
                        {
                            existItem=getItem(sale->itemList,item->product->code);
                            existItem->quantity+=item->quantity;
                            existItem->subTotal+=item->subTotal;
                        }
                        addToItemsFile("payment/sale/item/item.txt",item,sale->saleCode);
                        getchar();
                         printf("Enter y to add a new item or n to quit\n");
                         scanf("%c",&ans);
                     } while(ans=='y' || ans=='Y');
                     sale->total=calculateTotalSale(sale->itemList);
                     addToSalesFile("payment/sale/sale.txt", sale);
                     addToSalesList(SalesList,sale);
                     break;

            case 2 : printf("Enter the code of sale which you want to dispaly\n");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     if(sale==NULL)
                     {
                         printf("This sale doesn't exist\n");
                         break;
                     }
                     displaySaleDetail(sale);
                     break;

            case 3 : displaySalesList(*SalesList);
                     break;

            case 4:  printf("Enter the code of sale where the item exist : ");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     printf("Enter the code of item which you want to delete : ");
                     scanf("%d",&code);
                     deleteItem(&sale->itemList,code);
                     break;

            case 5 : printf("Enter the code of sale which you want to delete\n");
                     scanf("%d",&code);
                     deleteSale(SalesList,code);
                     break;
            case 0 : menu(ProductsList,CustomersList,SalesList); break;

            default : printf("This choice is incorrect\n");
                      break;
        }

        getchar();
        printf("Enter y to add a new choice or n to quit\n");
        scanf("%c",&ans);

    } while(ans=='y' || ans=='y');
    menu(ProductsList,CustomersList,SalesList);
}

//Menu de Payment********************************
void menuPayment(ProductElement **ProductsList,CustomerElement **CustomersList,SaleElement **SalesList)
{
        //SaleElement *SaleForCustomer; SaleForCustomer=NULL;
        double Sumamount;
        Sale *sale; sale=NULL;
        //int codeCustomer;
        Item* item,*existItem;
        int choix, code;
        Payment *payment;
        char ans;

    do
    {system("cls");
        //-------Menu-------
    printf("\n\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n");
    printf("\t*    -------Menu Payment-------   *\n");
    printf("\t*                                 *\n");
    printf("\t*       1.Create Payment          *\n");
    printf("\t*       2.Display Payment         *\n");
    printf("\t*       3.Display Payments List   *\n");
    printf("\t*       4.Delete Payment          *\n");
    printf("\t*       0.Return                  *\n");
    printf("\t*                                 *\n");
    printf("\t* * * * * * * * * * * * * * * * * *\n\n");
        printf("Enter your choice\n");
        scanf("%d",&choix);
        switch(choix)
        {
                     case 1 :

//                    printf("Enter the code of customer : ");
//        scanf("%d",&codeCustomer);
//        getSaleForCustomer(*SalesList,&SaleForCustomer,codeCustomer);
//        if(SaleForCustomer==NULL) printf("You have not a sale in this store, Create a sale firstly\n\n");
//        else
//        {
//            printf("\n------------- Your sale : -------------\n");
//            displaySalesList(SaleForCustomer);
//        }

                     printf("Enter the code of sale corresponding to this payment : ");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     if(sale==NULL)
                     {
                         printf("You have not create this sale\n");
                         sale=returnSale(CustomersList);
                     do
                     {
                        printf("Enter the code of product : ");
                        scanf("%d",&code);
                        item=returnItem(ProductsList, code);
                        if(ifProductexist(sale,code)==0)
                            addToItemsList(&sale->itemList,item);
                    else
                        {
                            existItem=getItem(sale->itemList,item->product->code);
                            existItem->quantity+=item->quantity;
                            existItem->subTotal+=item->subTotal;
                        }
                        addToItemsFile("payment/sale/item/item.txt",item,sale->saleCode);
                        getchar();
                         printf("Enter y to add a new item or n to quit\n");
                         scanf("%c",&ans);
                     } while(ans=='y' || ans=='Y');
                     sale->total=calculateTotalSale(sale->itemList);
                     addToSalesFile("payment/sale/sale.txt", sale);
                     addToSalesList(SalesList,sale);
                         //break;
                     }
                        Sumamount=SumAmount(sale->PaymentsList);
                        if(Sumamount==sale->total)
                        {
                            printf("The sale's total was paid\n");
                            break;
                        }
                        printf("The rest is %.2lf\n",sale->total-Sumamount);
                        payment=returnPayment(sale,Sumamount);
                        addToPaymentsFile("payment/payment.txt",payment);
                        addToPaymentsList(&sale->PaymentsList,payment);
                     break;
            case 2 : printf("Enter the code of Sale corresponding to this payment : ");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     if(sale==NULL)
                     {
                         printf("This sale doesn't exist\n");
                         break;
                     }
                     printf("Enter the code of payment which you want to display : ");
                     scanf("%d",&code);
                     payment=getPayment(sale->PaymentsList,code);
                     if(payment==NULL)
                     {
                         printf("This payment doesn't exist\n");
                         break;
                     }
                     displayPaymentDetail(payment);
                     break;
             case 3 : printf("Enter the code of sale corresponding to this payment : ");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     if(sale==NULL)
                     {
                         printf("This sale doesn't exist\n");
                         break;
                     }
                     if(sale->PaymentsList==NULL) {printf("The Payments List is empty\n");break;}
                     dispalyPaymentsList(sale->PaymentsList);
                     break;
            case 4 : printf("Enter the code of sale corresponding to this payment : ");
                     scanf("%d",&code);
                     sale=getSale(*SalesList,code);
                     if(sale==NULL)
                     {
                         printf("This sale doesn't exist\n");
                         break;
                     }
                     printf("Enter the code of payment which you want to delete : ");
                     scanf("%d",&code);
                     deletePayment(&sale->PaymentsList,code);
                     break;

            case 0 : menu(ProductsList,CustomersList,SalesList); break;

            default : printf("This choice is incorrect\n");
                      break;
        }

        getchar();
        printf("Enter y to add a new choice or n to quit\n");
        scanf("%c",&ans);

    } while(ans=='y' || ans=='y');
    menu(ProductsList,CustomersList,SalesList);
}

int main()
{
    SaleElement *SalesList; SalesList=NULL;
//    int choice; code;
//    char ans;
//    Item *item,*existItem;
//    int codeCustomer;
//    Payment* payment; payment=NULL;
//    double Sumamount;
//    Sale *sale; sale=NULL;

    //**********DataProducts**************
    ProductElement *ProductsList; ProductsList=NULL;
    int NBProduct;
    NBProduct=countNBLinesFileProduct("payment/sale/item/product/product.txt");
    initDataProducts(&ProductsList,"payment/sale/item/product/product.txt",NBProduct);
    // dispalyProductsList(ProductsList);
    // ***********************************

     //**********DataCustomers**************
    CustomerElement *CustomersList; CustomersList=NULL;
    int NBCustomer;
    NBCustomer=countNBLinesFileCustomer("payment/sale/customer/customer.txt");
    initDataCustomers(&CustomersList,"payment/sale/customer/customer.txt",NBCustomer);
    //dispalyCustomersList(CustomersList);
    // ***********************************

    //**********DataSales**************
    int NBSale, NBItem, i, j;
    NBItem=countNBLinesFileItem("payment/sale/item/item.txt");
    NBSale=countNBLinesFileSale("payment/sale/sale.txt");
    initDataSales(&SalesList,CustomersList,"payment/sale/sale.txt",NBSale);
    SaleElement *p; p=SalesList;
    int codeSale, codeProduct, quantity;
    double subtotal;
    FILE *fp_item;
    fp_item=fopen("payment/sale/item/item.txt","r");
    for(i=0;i<NBSale;i++)
    {
        fseek(fp_item, 0, SEEK_SET);
        fseek(fp_item, 39, SEEK_SET);
        for(j=0;j<NBItem;j++)
        {
            fscanf(fp_item,"%d", &codeSale);
            fscanf(fp_item,"%d",&codeProduct);
            fscanf(fp_item,"%d",&quantity);
            fscanf(fp_item,"%lf",&subtotal);
            if(p->sale->saleCode==codeSale)
            {
                initDataItems(&p->sale->itemList, ProductsList, codeProduct, quantity, subtotal);
            }
        }
        p=p->next;

    }
    fclose(fp_item);
    // displaySalesList(SalesList);
    // ***********************************

    menu(&ProductsList,&CustomersList,&SalesList);

    return 0;
}
