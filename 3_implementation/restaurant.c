#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
    char item[20];
    float total_price;
    int quantity;
};

struct orders
{
    char customer[50];
    char date[50];
    int noofItems;
    struct items itm[50];
};
// Functions to generate bills
void generateBilltop(char name[50], char date[30]){
    printf("\n");
    printf("\t   RSH Restaurant");
    printf("\n\t  ---------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("quantity\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}
void generatemainbill(char item[10], int quantity, float total_price)
{
    printf("%s\t",item);
    printf("%d\t",quantity);
    printf("%.2f\t",quantity * total_price);
    printf("\n");
    printf("\n");
}
void generateBillbottom(float total)
{
   printf("\n");
    float dis = 0.3*total;
    float netTotal=total-dis;
    float cgst=0.25*netTotal,grandTotal=netTotal + 3*cgst;
    printf("---------------------------------------\n");
    printf(" Total_price\t\t%.2f",total);
    printf("\nDiscount is about 30%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST is about 2.5%s\t\t\t%.2f","%",cgst);
    printf("\nSGST is about 2.5%s\t\t\t%.2f","%",cgst);
    printf("\n-----------------------------------");
    printf("\nUpdated_price \t\t\t%.2f",grandTotal);
    printf("\n------------------------------------\n");
}
int main(){
    float total;
    int option,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag ='y';
    char name[50];
    FILE *fp;
    
while(contFlag == 'y')
{
system("cls");
float total = 0;
int invoiceFound = 0;
printf("\t=============RSH-RESTAURANT=============");
printf("\n\nselect your preferences:\t");
printf("\n 1.Production of Invoice");
printf("\n 2.Show all Invoices");
printf("\n 3.Search of all the Invoice");
printf("\n 4.Exit : No preffered options");
printf("\n\n  Your choice of preference:\n");
scanf("%d",&option);
fgetc(stdin);
switch(option){
    case 1:
    system("cls");
    printf("\nPlease enter the name of the customer:\t");
    fgets(ord.customer,50,stdin);
    ord.customer[strlen(ord.customer)-1] = 0;
    strcpy(ord.date,__DATE__);
    printf("\nPlease enter the number of items:\t");
    scanf("%d",&n);
    ord.noofItems = n;
    for(int i=0;i<n;i++){
        fgetc(stdin);
        printf("\n\n");
        printf("Please enter the item %d:\t",i+1);
        fgets(ord.itm[i].item,20,stdin);
        ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
        printf("\nPlease enter the quantity:\t");
        scanf("%d",&ord.itm[i].quantity);
        printf("\nPlease enter the unit price:\t");
        scanf("%f",&ord.itm[i].total_price);
        total += ord.itm[i].quantity * ord.itm[i].total_price;
}

generateBilltop(ord.customer,ord.date);
for(int i=0;i<ord.noofItems;i++)
{
generatemainbill(ord.itm[i].item,ord.itm[i].quantity,ord.itm[i].total_price);
}
generateBillbottom(total);
printf("\nDo you want to save the invoice [y/n]:\t");
scanf("%s",&saveBill);
if(saveBill == 'y'){
    fp = fopen("RestaurantBill.dat","a+");
    fwrite(&ord,sizeof(struct orders),1,fp);
    if(fwrite != 0)
    printf("\nSuccessfully saved");
    else
    printf("\nError saving");
    fclose(fp);
}
break;
case 2:
system("cls");
fp = fopen("RestaurantBill.dat","r");
printf("\n  *****Your Previous Invoices*****\n");
while(fread(&order,sizeof(struct orders),1,fp)){
    float tot = 0;
    generateBilltop(order.customer,order.date);
    for(int i=0;i<order.noofItems;i++){
        generatemainbill(order.itm[i].item,order.itm[i].quantity,order.itm[i].total_price);
        tot+=order.itm[i].quantity * order.itm[i].total_price;
    }
    generateBillbottom(tot);
    }
fclose(fp);
break;

case 3:
printf("\nEnter the name of the customer:\t");
//fgetc(stdin);
fgets(name,50,stdin);
name[strlen(name)-1] = 0;
system("cls");
fp = fopen("RestaurantBill.dat","r");
printf("\t______Invoice of %s______",name);
while(fread(&order,sizeof(struct orders),1,fp))
{
    float total = 0;
    if(!strcmp(order.customer,name)){
generateBilltop(order.customer,order.date);
    for(int i=0;i<order.noofItems;i++){
        generatemainbill(order.itm[i].item,order.itm[i].quantity,order.itm[i].total_price);
        total =total+order.itm[i].quantity * order.itm[i].total_price;
    }
    generateBillbottom(total);
    invoiceFound = 1;
    }
    
    }
    if(invoiceFound==0){
        printf(" The invoice for %s does not exists",name);
    }
fclose(fp);
break;

case 4:
printf("\n\t\t OK Thankyou :)\n\n");
exit(0);
break;
 default:
 printf("Sorry invalid option");
 break;
}
printf("\nAre you intrested in any other operation?[y/n]:\t");
scanf("%s",&contFlag);
}
printf("\n thank you :)\n\n");
printf("\n\n");
return 0;
}
