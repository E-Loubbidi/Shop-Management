#ifndef H_REGLEMENT
#define H_REGLEMENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer/customer.h"
#include "date.h"

typedef struct Cheque
{
    int numcheque;
    Date date;
    Customer *proprietaire;
}Cheque;

typedef struct EnLigne
{
    int numEnLigne;
    Date date;
    int codeCarteVisa;
    Customer *proprietaire;
}EnLigne;

typedef struct Traite
{
    int numTraite;
    Date date;
    int numCodeCompteBancaire;
    Customer *proprietaire;
}Traite;

Cheque* createCheque(Date date, Customer *proprietaire)
{
    Cheque* cheque;
    cheque=(Cheque*)malloc(sizeof(Cheque));
    printf("Cheque Number : ");
    scanf("%d",&cheque->numcheque);
    cheque->date=date;
    cheque->proprietaire=proprietaire;
    return cheque;
}

EnLigne* createEnLigne(Date date, Customer *proprietaire)
{
    EnLigne* enLigne;
    enLigne=(EnLigne*)malloc(sizeof(EnLigne));
    printf("Online Number : ");
    scanf("%d",&enLigne->numEnLigne);
    printf("code Carte Visa : ");
    scanf("%d",&enLigne->codeCarteVisa);
    enLigne->date=date;
    enLigne->proprietaire=proprietaire;
    return enLigne;
}

Traite* createTraite(Date date, Customer *proprietaire)
{
    Traite* traite;
    traite=(Traite*)malloc(sizeof(Traite));
    printf("Draft Number : ");
    scanf("%d",&traite->numTraite);
    printf("Code Compte Bancaire : ");
    scanf("%d",&traite->numCodeCompteBancaire);
    traite->date=date;
    traite->proprietaire=proprietaire;
    return traite;
}

#endif
