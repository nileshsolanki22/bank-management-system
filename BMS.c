//Bank Management System
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

int acc_no=99;

//--------------------------------------------//
//            Structure for tree             //
//------------------------------------------//

struct node
 {
    int acc_no;
    long int amt;
    char ph_no[15];
    char acc_name[100];
    struct node *left;
    struct node *right;
 }*root=NULL;

//--------------------------------------------//
//            Structure for file             //
//------------------------------------------//

struct record
 {
    int acc_no;
    long int amt;
    char acc_name[100];
	char ph_no[15];
 }file;

int main()
 {
   int item,x,ch,s,acc_num;
   //loadmasterfile();//Loads Master Database
   do
 {
    printf("\n");
    printf("\t======================================================================\n");
    printf("\t\t\t\tBANK MANAGEMENT SYSTEM\n\n");
    printf("\t\t\t\t     MAIN MENU\n");
    printf("\t======================================================================\n\n");
    printf("\n\t1.NEW ACCOUNT\n");
    printf("\n\t2.DEPOSIT MONEY\n");
    printf("\n\t3.WITHDRAW MONEY\n");
    printf("\n\t4.BALANCE ENQUIRY\n");
    printf("\n\t5.BANK'S DATABASE\n");
    printf("\n\t6.CLOSE AN ACCOUNT\n");
    printf("\n\t7.EXIT\n");
    printf("\n\t----------------------------------------------------------------------\n");
    printf("\n\tEnter Your Choice <1-7> : ");
    scanf("%d",&x);
   switch(x)
   {
    case 1:
    acc_no++;
    insert(acc_no);
    break;
    case 2:
    deposit_money();
    break;
    case 3:
    withdrawal_money();
    break;
    case 4:
    balance_enquiry();
    break;
    case 5:
    printf("\n\t======================================================================\n\n");
    printf("\tA/c No.");
    printf("\t\tName");
    printf("\t\tContact No.");
    printf("\t\tBalance\t\n");
    printf("\n\t=====================================================================\n\n");
    loadmasterfile();//Loads Master Database
	traverse(root);
    break;
    case 6:
    printf("\n\tEnter Account Number : ");
    scanf("%d",&item);
    delete(item);
    break;
    case 7:
    exit(1);
    default:
    printf("\n\n\tWrong Choice! Try Again\n");
   }
  } while(ch!=7);
  return 0;
}

//--------------------------------------------//
//             New Node Function             //
//------------------------------------------//

struct node *getnode()
 {
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node));
    p->right=NULL;
    p->left=NULL;
    return(p);
 }

//--------------------------------------------//
//            Insert Function                //
//------------------------------------------//

insert(int item)
 {
    struct node *new,*loc,*par;
    search(item,&par,&loc);
    FILE *mfp;
    mfp=fopen("masterfile.txt","ab");

    new=getnode();
    new->acc_no=item;
    file.acc_no=new->acc_no;
    printf("\n\n\t\t---------------ACCOUNT OPENING FORM-----------------\n\n");
    printf("\n\t\tEnter Your Full Name : ");
    fflush(stdin);
    gets(new->acc_name);
    strcpy(file.acc_name,new->acc_name);
    fflush(stdin);
    printf("\n\t\tEnter Telephone No. : ");
    scanf("%s",&new->ph_no);
    strcpy(file.ph_no,new->ph_no);
    printf("\n\t\tEnter Initial Amount (min=500) : ");
    scanf("%ld",&new->amt);

    while(new->amt<500){
        printf("\n\t\tPlease Enter Initial Amount >=500 : ");
        scanf("%ld",&new->amt);
    }
    file.amt=new->amt;
    fwrite(&file,sizeof(struct record),1,mfp);
    printf("\n\n\t\tYour Account is created successfully....\n\n");

    if(par==NULL){
        root=new;
        return;
    }
    else if(item>par->acc_no){
        par->right=new;
    }
    else{
        par->left=new;
    }
    fclose(mfp);
 }

//--------------------------------------------//
//            Search Function                //
//------------------------------------------//

search(int item,struct node **par,struct node **loc)
{
   struct node *ptr,*save;
   if(root==NULL)
{
   *loc=NULL;
   *par=NULL;
   return;
}//If tree is empty
else if(item==root->acc_no)
{
   *loc=root;
   *par=NULL;
   return;
}//Tree has only one node
if(item<root->acc_no)
{
   ptr=root->left;
   save=root;
}//Item is smaller than root
else
{
   ptr=root->right;
   save=root;
}//Item is greater than root
while(ptr!=NULL)
{
if(item==ptr->acc_no)
{
   *loc=ptr;
   *par=save;
return;
}//If Item is found on ptr
else if(item>ptr->acc_no)
{
   save=ptr;
   ptr=ptr->right;
}//If Item is bigger than ptr
else
{
   save=ptr;
   ptr=ptr->left;
}//If Item is smaller than ptr
}
   *par=save;
   *loc=NULL;
}

//--------------------------------------------//
//          Money Deposit Function           //
//------------------------------------------//

deposit_money()
{
   struct node *par,*loc;
   long int sum;
   int acc_num;
   printf("\n\tEnter Account No.: ");
   scanf("%d",&acc_num);
   search(acc_num,&par,&loc);
   if(loc==NULL)
{
   printf("\t\tAccount does not exists...");
}
else
{
   printf("\n\tEnter Amount to be deposited: ");
   scanf("%ld",&sum);
   loc->amt+=sum;
   printf("\n\t\tYour Account is updated successfully....\n\n");
}
}

//--------------------------------------------//
//        Money Withdrawal Function          //
//------------------------------------------//

withdrawal_money()
{
   struct node *par,*loc;
   long int sum;
   int acc_num,bal;
   printf("\n\tEnter Account No.: ");
   scanf("%d",&acc_num);
   search(acc_num,&par,&loc);
if(loc==NULL)
{
   printf("\n\tAccount does not exists...\n\n");
}
else
{
do
{
   printf("\n\tEnter Amount to be withdrawn : ");
   scanf("%ld",&sum);
   bal=(loc->amt-sum);
   if(bal<500)
   printf("\n\tNot Enough Balance,\n\tYour current account balance would become <500\n");
if(bal>=500)
break;
}
while((loc->amt-sum)<=500);
   loc->amt-=sum;
   printf("\n\t\tYour Account is updated successfully....\n\n");
}

}

//--------------------------------------------//
//        Balance Enquiry Function           //
//------------------------------------------//

balance_enquiry()
{
   struct node *par,*loc;
   int acc_num,rem;
   printf("\n\tEnter Account No.: ");
   scanf("%d",&acc_num);
   printf("\n\n");

search(acc_num,&par,&loc);
if(loc==NULL)
{
   printf("\n\tAccount does not exists...\n\n");
}
else
{
    printf("\t\t--------------ACCOUNT STATUS--------------\n\n");
    printf("\n\t\tA/c No. : %d",loc->acc_no);
    printf("\n\t\tAccount Holder's Name : %s",loc->acc_name);
    printf("\n\t\tContact Number : %s",loc->ph_no);
    printf("\n\t\tBalance : %ld\n",loc->amt);
}
}

//--------------------------------------------//
//     Bank's Database Display Function      //
//------------------------------------------//

traverse(struct node *root)
{
 if(root==NULL)
    return;
traverse(root->left);
    printf("\t%d",root->acc_no);
    printf("\t%s",root->acc_name);
    printf("\t\t%s",root->ph_no);
    printf("\t\t    %ld\n",root->amt);
traverse(root->right);
}

//--------------------------------------------//
//             Delete Function               //
//------------------------------------------//

delete(int item)
{
    struct node *par,*loc;
    search(item,&par,&loc);

if(loc==NULL)
{
    printf("\n\tAccount does not exists\n");
}
else if(loc->left!=NULL&&loc->right!=NULL)
{
    caseb(&par,&loc);
}
else
{
    casea(&par,&loc);
    printf("\n\n\tThe Acoount is Closed Successfully ....");
    free(loc);
}
}

//---------------------------------------------//
// When node contains either 1 or 0 child     //
//-------------------------------------------//


casea(struct node **par,struct node **loc)
{
	struct node *child;
    if((*loc)->left==NULL&&(*loc)->right==NULL)
	child=NULL;//No child node
    else if((*loc)->left!=NULL)
	child=(*loc)->left;//child is in left subtree
    else
	child=(*loc)->right;//child is in right subtree
 if(*par!=NULL)
  {
   if((*loc)==(*par)->left)
   {
      (*par)->left=child;
   }
     else
        {
           (*par)->right=child;
        }
  }
     else
     root=child;//Tree contains only one node
}

//--------------------------------------------//
//      When node contains 2 children        //
//------------------------------------------//

caseb(struct node **par,struct node **loc)
{
        struct node *suc,*parsuc,*save,*ptr;
        ptr=(*loc)->right;
        save=*loc;
 while(ptr->left!=NULL)
 {
     save=ptr;
     ptr=ptr->left;
 }
         suc=ptr;
         parsuc=save;
         casea(&parsuc,&suc);
if((*par)!=NULL)
 {
if((*par)->left==*loc)
      (*par)->left=suc;
else
      (*par)->right=suc;
 }
       root=suc;
       suc->left=(*loc)->left;
       suc->right=(*loc)->right;
       //printf("The node deleted is caseb = %d",suc);
}

//--------------------------------------------//
//      Master File Loading Fuction          //
//------------------------------------------//

loadmasterfile()
 {
       FILE *fp;
       int x;
       fp=fopen("masterfile.txt","rb");
  while(!feof(fp))
  {
  	   if(fp==NULL)
  	   break;

       x=fread(&file,sizeof(struct record),1,fp);
       acc_no++;
       if(x==1)
       {

            printf("\t%d",file.acc_no);
            printf("\t");
            printf("\t%s\t",file.acc_name);
			printf("\t%s  ",file.ph_no);
            printf("\t%ld\n",file.amt);
       }
  }
 fclose(fp);
}




