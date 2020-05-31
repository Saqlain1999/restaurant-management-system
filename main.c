#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int sum=0;

int food_id_generator();
int admin_login();
void admin_view();
void admin_edit();
void admin_insert();
void admin_delete();
void ask_again();
void cancel_order();
void choose_menu();
void print_menu();
void edit_order();
void print_order_list();
int ask_for_edit();
void read_list();
void select_order();
void view();
void select_order_basket();
void select_order_bill(char *order);
void select_order_idprinting();
void admin_menu();
int admin_login();
void view_customers();
void insert_customer();
void delete_customer();

struct manager{
char name[50];
char password[15];
}admin;
struct customer{
char name[20];
char email[40];
int phone_no;
int bill;
char pmethod[10];
}c;
struct order{
    int id;
}neworder={1};

int main ()
{
    system("cls");
    print_menu();
    choose_menu();
    return 0;
}
void print_order_list()
{
    FILE *food;
    food=fopen("food.txt","r");
    char filefood[50];
    while(!feof(food))
    {
        fgets(filefood,50,food);
        puts(filefood);
    }
    fclose(food);
}
void view()//also associate price with the product
{
    printf("\n\nToday's menu consists of these items: \n\n");
    print_order_list();
    ask_again();
}
void search_order()//COME BACK HERE!
{
    FILE *orderfile,*billfile;
    char showorders[100],c;
    int searchid,bill,billid=0,showid=0;
    printf("\n\nEnter the order ID you want to search for: ");
    scanf("%d",&searchid);
    orderfile=fopen("oldorders.txt","r");
    while (!feof(orderfile))//ID is being read here
    {
        c=fgetc(orderfile);
        if (c==':')
        {
            showid++;
        }
        if (showid==searchid)
        {
            break;
        }
    }
    fgets(showorders,500,orderfile);
    printf("\nOrder no %d Contains:\n",searchid);
    while(!feof(orderfile))
    {
        fgets(showorders,500,orderfile);
        if (strnicmp(showorders,"ID:",3)==0)
        {
            showid++;
        }
        if (showid==searchid+1)
        {
            break;
        }
        puts(showorders);
    }
    fclose(orderfile);
    billfile=fopen("bill.txt","r");
    while (!feof(billfile))//ID is being read here
    {
        c=fgetc(billfile);
        if (c==':')
        {
            billid++;
        }
        if (billid==searchid)
        {
            break;
        }
    }
    fscanf(billfile,"%d",&bill);
    fclose(billfile);
    printf("\nTotal Bill: $%d\n",bill);
    ask_again();
}
void print_menu()
{
    printf("\t\t\t\t\t\tWelcome to the main menu\n\nPlease choose what you would like to do: ");
    printf("\n1. Manager Panel\n");
    printf("2. Customer Panel\n");
    printf("3. View the menu: \n");
    printf("4. Place your order: \n");
    printf("5. Edit your order: \n");
    printf("6. Cancel your order: \n");
    printf("7. Search for an order: \n");
    printf("8. Exit\n");
}
void choose_menu()
{
    int menu_option;
    menu_option=getche();
    system("cls");
    switch (menu_option)
    {
    case '1':
        admin_menu();
        break;
    case '2':
        customer_menu();
        break;
    case '3':
        view();
        break;
    case '4':
        select_order();
        break;
    case '5':
        edit_order();
        break;
    case '6':
        cancel_order();
        break;
    case '7':
        search_order();
        break;
    case '8':
        exit;
        break;
    default: printf("Incorrect option has been chosen");main();
    }

}
void select_order()
{
    int total_items=0,selection,j=0,i=0,redo,addmore,pricevar;
    char ch,confirm,order[100];
    FILE *of,*orderf, *billfile,*ffood;
    orderf=fopen("bill.txt","a+");
    fseek(orderf,0,SEEK_SET);
    neworder.id=1;
    while(!feof(orderf))
    {
        fscanf(orderf,"%c",&ch);
        if(ch==':')
        {
            neworder.id++;
        }
    }
    fclose(orderf);
    if (neworder.id==1)
    {
        select_order_idprinting();
        neworder.id++;
    }
    do//selection of items  +  total bill  +  what the order contains
    {
        system("cls");
        print_order_list();
        addmore=0;
        of=fopen("torders.txt","a+");
        redo=0;
        ffood=fopen("food.txt","r");//close file at the end of do while loop (parent loop)
        for (i=0,j=0;i<=j;i++)//for error in selecting order
        {
            int lineno=0;
            fflush(stdin);
            printf("\nWhat you would like to order?\n");
            scanf(" %d",&selection);
            while(!feof(ffood))
            {
                fgets(order,100,ffood);
                lineno++;
                if(lineno==(selection))
                {
                    break;
                }
            }
            if (feof(ffood))
            {
                printf("\nInvalid Selection\n");
                j++;
                rewind(ffood);
                continue;
            }
            fseek(ffood,3,SEEK_CUR);
            fscanf(ffood,"%s",order);
            fputs("\n",of);
            fputs(order,of);
            printf("\n%s ",order);
            fscanf(ffood,"%d",&pricevar);
            printf(" $%d",pricevar);
            sum+=pricevar;
        }
        fclose(ffood);
        total_items++;
        fclose(of);
        select_order_bill(order);//prints bill
        for (i=0,j=0;i<=j;i++)//for error in addmore items
        {
            fflush(stdin);
            printf("Would you like to order more items?\n");
            confirm=getch();
            if (confirm=='y'||confirm=='Y')
            {
                addmore++;
                break;
            }
            else if (confirm=='n'||confirm=='N')
            {
                system("cls");
                break;
            }
            else
            {
                printf("\nIncorrect option chosen, please try again\n");
                j++;
            }
        }
    }
    while (addmore==1);
    select_order_bill(order);
    for (i=0,j=0;i<=j;i++)//for error in confirming final order
    {
        fflush(stdin);
        printf("\nAre you confirm you want to place your order?");
        confirm=getch();
        if (confirm=='y'||confirm=='Y')
        {
            billfile=fopen("bill.txt","a+");
            fprintf(billfile,"%d",sum);
            fclose(billfile);
            FILE *orderf,*of;
            orderf=fopen("oldorders.txt","a");
            of=fopen("torders.txt","r");
            while ((ch = fgetc(of)) != EOF)//reads character by character till eof
                fputc(ch, orderf);
            fclose(of);
            fclose(orderf);
            remove("torders.txt");
            printf("\n\nYour order ID is %d.\n",neworder.id-1);
            sum=0;
            select_order_idprinting();
            break;
        }
        else if (confirm=='n'||confirm=='N')
        {
            remove("torders.txt");
            sum=0;
            break;
        }
        else
        {
            printf("Incorrect option chosen, please try again\n");
            j++;
        }
    }
    ask_again();
}
void edit_order()
{
    FILE *editof,*ffood;
    FILE *billfile;
    char altdata[500];
    int i,j;
    char selection;
    int bill;
    int proice;
    int orderid=0;
    int productno=0;
    int billid=0;
    int editid,curposition,newposition;
    char c,foundproduct[30];
    printf("Enter the order ID which you like to edit: ");
    scanf("%d",&editid);
    editof=fopen("oldorders.txt","r+");
    billfile=fopen("bill.txt","r");
    while (!feof(billfile))//ID is being read here
    {
        c=fgetc(billfile);
        if (c==':')
        {
            billid++;
        }
        if (billid==editid)
        {
            break;
        }
    }
    fscanf(billfile,"%d",&bill);
    fclose(billfile);
    sum=bill;
    while (!feof(editof))//ID is being read here
    {
        c=fgetc(editof);
        if(c==':')
        {
            orderid++;
        }
        if(orderid==editid)
        {
            break;
        }
    }
    fseek(editof,4,SEEK_CUR);
    while (!feof(editof))
    {
        curposition=ftell(editof);
        fgets(altdata,500,editof);
        newposition=ftell(editof);
        if (strstr(altdata,"ID:")==0)
        {
            if (productno==0)
            {
                printf("\nProduct: ");
                productno++;
            }
            else
                printf("\nNext Product: ");

            puts(altdata);
            printf("\nTotal Bill: %d\n",sum);
            if (ask_for_edit()==1)//come back here for checking error
            {
                ffood=fopen("food.txt","r");
                while(!feof(ffood))
                {
                    fscanf(ffood,"%s",foundproduct);
                    if(strnicmp(altdata,foundproduct,4)==0)
                    {
                        fscanf(ffood,"%d",&proice);
                        sum-=proice;
                        printf("\nPrice of %s is %d",foundproduct,proice);
                        break;
                    }
                }
                printf("\n");
                print_order_list();
                printf("\n");
                fseek(editof,(curposition-newposition),SEEK_CUR);
                rewind(ffood);
                //can be made into a function
                char order[100];
                int pricevar;
                for (i=0,j=0;i<=j;i++)//for error in selecting order
                {
                    int lineno=0;
                    fflush(stdin);
                    printf("\nWhat you would like to replace your order with?\n");
                    scanf(" %d",&selection);
                    while(!feof(ffood))
                    {
                        fgets(order,100,ffood);
                        lineno++;
                        if(lineno==(selection))
                        {
                            break;
                        }
                    }
                    if (feof(ffood))
                    {
                        printf("\nInvalid Selection\n");
                        j++;
                        rewind(ffood);
                        continue;
                    }
                    fseek(ffood,3,SEEK_CUR);
                    fscanf(ffood,"%s",order);
                    strcat(order,"\0");
                    fputs(order,editof);
                    printf("\n%s ",order);
                    fscanf(ffood,"%d",&pricevar);
                    printf(" $%d",pricevar);
                    sum+=pricevar;
                }
                fputs("\n",editof);
                curposition=fseek(editof,0,SEEK_CUR);
            }
        }
        else
        {
            if (sum>0)
                printf("\nYou owe us $%d",sum);
            else if (sum==0)
                printf("\nYour bill has been adjusted");
            else if (sum<0)
                printf("We owe you $%d ",sum);
            break;
        }
    }
    billfile=fopen("bill.txt","r+");
    int var=0;
    char ch;
    while (!feof(billfile))//ID is being read here
    {
        ch=fgetc(billfile);
        if (ch==':')
        {
            var++;
        }
        if (var==editid)
        {
            fseek(billfile,1,SEEK_CUR);
            fprintf(billfile,"%d",sum);
            break;
        }
    }
    fclose(billfile);
    ask_again();
}
void cancel_order()
{
    FILE *oldofile,*billfile,*newofile;
    char movingdata[500],c,cha[50],showorders[100],confirmdelete;
    int deleteid,bill,billid=0,orderid=0,showid=0;
    printf("\n\nEnter the order ID you want to delete: ");
    scanf("%d",&deleteid);
    printf("Am working");
    oldofile=fopen("oldorders.txt","r");
    while (!feof(oldofile))//ID is being read here
    {
        c=fgetc(oldofile);
        if (c==':')
        {
            showid++;
        }
        if (showid==deleteid)
        {
            break;
        }
    }
    fgets(showorders,500,oldofile);
    printf("\nYour Order Contained:\n");
    while(!feof(oldofile))
    {
        fgets(showorders,500,oldofile);
        if (strnicmp(showorders,"ID:",3)==0)
        {
            showid++;
        }
        if (showid==deleteid+1)
        {
            break;
        }
        puts(showorders);
    }
    fclose(oldofile);
    billfile=fopen("bill.txt","r");
    while (!feof(billfile))//ID is being read here
    {
        c=fgetc(billfile);
        if (c==':')
        {
            billid++;
        }
        if (billid==deleteid)
        {
            break;
        }
    }
    fscanf(billfile,"%d",&bill);
    fclose(billfile);
    printf("\nYour bill used to be $%d",bill);
    printf("\nAre you sure you want to delete this order? (Y or n)\n");
    confirmdelete=getch();
    if(confirmdelete=='y' || confirmdelete=='Y')
    {
        oldofile=fopen("oldorders.txt","r+");
        newofile=fopen("temp.txt","w+");
        movingdata[0]=NULL;
        while (!feof(oldofile))//ID is being read here
        {
            //fscanf(oldofile,"%s",cha);
            fgets(cha,500,oldofile);
            strcat(movingdata,cha);
            if (strnicmp(cha,"ID:",3)==0)
            {
                orderid++;
            }
            if (orderid==deleteid)
            {
                break;
            }
        }
        //fseek(oldofile,5,SEEK_CUR);
        while(!feof(oldofile))
        {
            fgets(cha,500,oldofile);
            //fscanf(oldofile,"%s",cha);
            if (strnicmp(cha,"ID:",3)==0)
            {
                orderid++;
            }
            if (orderid==deleteid+1)
            {
                fseek(oldofile,-7,SEEK_CUR);
                break;
            }
        }
        while (!feof(oldofile))//ID is being read here
        {
            fgets(cha,500,oldofile);
            //fscanf(oldofile,"%s",cha);
            strcat(movingdata,cha);
        }
        fputs(movingdata,newofile);
        fclose(oldofile);
        fclose(newofile);
        remove ("oldorders.txt");
        rename("temp.txt","oldorders.txt");
    }
    ask_again();
}
void ask_again()
{
    fflush(stdin);
    char option;
    printf("\nWould you like to return to the main menu? (Y/N)\n");
    option=getche();
    if (option=='Y'||option=='y')
    {
        system("cls");
        main();
    }
    else if (option=='N'||option=='n')
    {
        exit;
    }
    else
    {
        printf("Incorrect Option Chosen\n");
        ask_again();
    }
}
void select_order_bill(char *order)
{
    FILE *tempfpoint;
    tempfpoint=fopen("torders.txt","r");
    //puts(order);
    printf("\nYour Order Contains: ");
    //read from the same file
    fseek(tempfpoint,0,SEEK_SET);
    int currentnumber=0;
    while(!feof(tempfpoint))
    {
        fgets(order,100,tempfpoint);
        if (currentnumber>0)
        printf("%d. ",currentnumber);
        printf("%s",order);
        currentnumber++;
    }
    printf("\nYour Bill: $%d\n\n",sum);
    fclose(tempfpoint);
}

void select_order_idprinting()
{
    FILE *orderfile,*billfile;
    orderfile=fopen("oldorders.txt","a");
    billfile=fopen("bill.txt","a");
    fputc('\n',orderfile);
    fputc('\n',billfile);
    fprintf(billfile,"ID %d: ",neworder.id);
    fprintf(orderfile,"ID: %d",neworder.id);
    fclose(orderfile);
    fclose(billfile);
}
int ask_for_edit()
{
    char sel;
    printf("\nWould you like to edit this product?");
    sel=getch();
    if (sel=='y'||sel=='Y')
        return 1;
    else if (sel=='n'||sel=='N')
        return 0;
    else
    {
        printf("\nPlease type in correct option");
        ask_for_edit();
    }
}
int food_id_generator()
{
    FILE *ffile;
    int foodid=0;
    char movingdata[200];
    ffile=fopen("food.txt","r");
    while (!feof(ffile))//ID is being read here
    {
        fgets(movingdata,200,ffile);
        foodid++;
    }
    fclose(ffile);
    return foodid;
}
void admin_view()
{
    print_order_list();

}
void admin_edit() // SWAP EQUAL CHARACTER FOOD's
{
    FILE *ffood;
    int i,j,selection;
    char order[50],newfood[50];
    //char pricevar[50];
    int pricevar;
    ffood=fopen("food.txt","r+");//close file at the end of do while loop (parent loop)
    for (i=0,j=0;i<=j;i++)//for error in selecting order
    {
        int lineno=0,length;
        fflush(stdin);
        print_order_list();
        printf("\nWhich Product you would like to edit?\n");
        scanf(" %d",&selection);
        while(!feof(ffood))
        {
            fgets(order,50,ffood);
            lineno++;
            if(lineno==(selection))
            {
                break;
            }
        }
        if (feof(ffood))
        {
            printf("\nInvalid Selection\n");
            j++;
            rewind(ffood);
            continue;
        }
        fseek(ffood,4,SEEK_CUR);
        fscanf(ffood,"%s",order);
        length=strlen(order);
        fseek(ffood,-strlen(order),SEEK_CUR);
        for (i=0,j=length;i<=length;i++)
        {
            fprintf(ffood," ");
        }
        fseek(ffood,(-strlen(order)-1),SEEK_CUR);
        printf("Enter the new food name: ");
        fflush(stdin);
        gets(newfood);
        fputs(newfood,ffood);
        fseek(ffood,0,SEEK_CUR);
        fscanf(ffood,"%d",&pricevar);
        fseek(ffood,-3,SEEK_CUR);
        printf("Enter the new price for %s :",newfood);
        fflush(stdin);
        scanf("%d",&pricevar);
        if (pricevar<10)
        fprintf(ffood,"\t0%d",pricevar);
        else
        fprintf(ffood,"\t%d",pricevar);
    }
    fclose(ffood);
}
void admin_insert()
{
    FILE *ffood;
    ffood=fopen("food.txt","a+");
    char addfood[50];
    int addprice,foodid;
    print_order_list();
    printf("Enter the Food name you want to add: ");
    fflush(stdin);
    gets(addfood);
    printf("Enter the Price for new product :");
    fflush(stdin);
    scanf("%d",&addprice);
    foodid=food_id_generator();
    fputc('\n',ffood);
    fprintf(ffood,"%d. ",foodid);
    fputs(addfood,ffood);
    if (addprice<10)
    fprintf(ffood,"\t0%d",addprice);
    else
    fprintf(ffood,"\t%d",addprice);
    fclose(ffood);
}
void admin_delete()
{
    //print_order_list();
    FILE *ffood,*ftemp;
    int i,j,selection;
    char order[50];
    //char pricevar[50];
    int pricevar;
    ftemp=fopen("tdelfood.txt","w");//creates temp file which stores all non deleted data
    ffood=fopen("food.txt","r");//close file at the end of do while loop (parent loop)
    for (i=0,j=0;i<=j;i++)//for error in selecting order
    {
        int lineno=0;
        fflush(stdin);
        print_order_list();
        printf("\nWhich Product you would like to delete?\n");
        scanf(" %d",&selection);
        while(!feof(ffood))
        {
            fgets(order,50,ffood);
            fputs(order,ftemp);
            lineno++;
            if(lineno==(selection))
            {
                break;
            }
        }
        if (feof(ffood))
        {
            printf("\nInvalid Selection\n");
            j++;
            rewind(ffood);
            continue;
        }
        fgets(order,50,ffood);

        printf("\nThis line is being deleted\n%s\n",order);
        i=0;
        int fplocation,fpnewlocation;
        while(!feof(ffood))//does not replace id (selection has current ID)
        {
            fscanf(ffood," %s",order);//taking id and . and wasting it
            fplocation=ftell(ftemp);
            if (i!=0)
               fprintf(ftemp,"\n");
            fprintf(ftemp,"%d. ",selection+i);//placing new id
            fpnewlocation=ftell(ftemp);//
            fseek(ftemp,fplocation-fpnewlocation,SEEK_CUR);//moving cursor back
            fseek(ftemp,6,SEEK_CUR);//moving cursor to where food should be placed
            if (i==0)
                fseek(ftemp,-2,SEEK_CUR);
            fscanf(ffood,"%s",order);//gets food's first name
            fprintf(ftemp,"%s",order);//stores food's first name
            fscanf(ffood," %d",&pricevar);
            if (pricevar<10)
            fprintf(ftemp,"\t0%d",pricevar);
            else
            fprintf(ftemp,"\t%d",pricevar);
            i++;
        }
        fclose(ffood);
        fclose(ftemp);
        remove("food.txt");
        rename("tdelfood.txt","food.txt");
        print_order_list();
    }
    ask_again();
}
int admin_login()
{
    int password;
    FILE *fpass;
    char pass[50],storedpass[50];
    fpass=fopen("adminpass.txt","r");
    fgets(storedpass,50,fpass);
    //password thingy, returns a value thingy.
    printf("Enter your password: ");
    gets(pass);
    password=strnicmp(pass,storedpass,strlen(storedpass));
    fclose(fpass);
    return password;
}
void admin_menu()
{
    int i,wp,gg,successful;
    for (i=0,wp=0;i<=wp;i++)
    {
        successful=admin_login();
        if (successful==0)
        {
            printf("\n\t\tManager Menu\n");
            printf("\n1. View Menu");
            printf("\n2. Insert Item");
            printf("\n3. Edit Item");
            printf("\n4. Delete Item");
            printf("\n\nWhich action would you like to perform?\n");
            scanf("%d",&gg);
            if (gg==1)
                admin_view();
            else if (gg==2)
                admin_insert();
            else if (gg==3)
                admin_edit();
            else if(gg==4)
                admin_delete();
            else if(gg<1 || gg>4)
            {
                printf("Error in value");
                admin_menu();
            }
        }
        else if (wp==3)
        {
            printf("\nSorry, too many tries.");
            break;
        }
        else if (wp<4)
        {
            printf("\nWrong password has been entered, please try again.\n");
            wp++;
        }
    }
    ask_again();
}
void customer_menu()
{
    char todo;
    printf("\n1. View Customers\n");
    printf("2. Insert Customer\n");
    printf("3. Delete Customer\n");
    printf("4. Edit Customer\n");
    printf("5. Return to main menu\n");
    printf("What would you like to do? \n");
    todo=getche();
    if (todo=='1')
        view_customers();
    else if (todo=='2')
        insert_customer();
    else if (todo=='3')
        delete_customer();
    else if (todo=='4')
        edit_customer();
    else if (todo=='5')
        main();
    else if(todo<'1' || todo>'5')
    {
        system("cls");
        customer_menu();
    }
}
void view_customers()
{
    FILE *custo;
    custo=fopen("customers.txt","r");
    char *var_name,*var_email,storage[500],*var_number,*var_method,*var_bill,*c;
    int id=1;
    while(!feof(custo))
    {
        fgets(storage,500,custo);
        c=strtok(storage,",");
        var_name=c;
        printf("\nID: %d",id);
        printf("\nName: %s",var_name);
        c=strtok(NULL,",");
        var_email=c;
        printf("\nEmail: %s",var_email);
        c=strtok(NULL,",");
        var_number=c;
        printf("\nNumber: %s",var_number);
        c=strtok(NULL,",");
        var_method=c;
        printf("\nPayment Method: %s",var_method);
        c=strtok(NULL,",");
        var_bill=c;
        printf("\nBill: %s",var_bill);
        c=strtok(NULL,",");
        printf("\n\n");
        id++;
    }
      fclose(custo);
      ask_again();
}
void insert_customer()
{
    FILE *customers;
    customers=fopen("customers.txt","a+");
    printf("\nEnter your full name: ");
    fflush(stdin);
    gets(c.name);
    printf("\nEnter your Email: ");
    gets(c.email);
    fflush(stdin);
    printf("\nEnter your Phone no: ");
    scanf("%d",&c.phone_no);
    fflush(stdin);
    printf("How you will pay your bill (Cash Or Credit/Debit)");
    gets(c.pmethod);
    fflush(stdin);
    printf("Your total Bill: ");
    scanf("%d",&c.bill);
    fputs("\n",customers);
    fprintf(customers,"%s,%s,%d,%s,%d",c.name,c.email,c.phone_no,c.pmethod,c.bill);
    fclose(customers);
    ask_again();
}
void delete_customer()
{
    FILE *customers,*tempcust;
    FILE *custo;
    int deleteid,counter=1;
    char deleteline[500],datatomove[500];
    customers=fopen("customers.txt","r");
    tempcust=fopen("tempcust.txt","w+");
    custo=fopen("customers.txt","r");
    char *var_name,*var_email,storage[500],*var_number,*var_method,*var_bill,*c;
    int id=1;
    while(!feof(custo))
    {
        fgets(storage,500,custo);
        c=strtok(storage,",");
        var_name=c;
        printf("\nID: %d",id);
        printf("\nName: %s",var_name);
        c=strtok(NULL,",");
        var_email=c;
        printf("\nEmail: %s",var_email);
        c=strtok(NULL,",");
        var_number=c;
        printf("\nNumber: %s",var_number);
        c=strtok(NULL,",");
        var_method=c;
        printf("\nPayment Method: %s",var_method);
        c=strtok(NULL,",");
        var_bill=c;
        printf("\nBill: %s",var_bill);
        c=strtok(NULL,",");
        printf("\n\n");
        id++;
    }
    fclose(custo);
    printf("Enter the customer ID you want to delete");
    fflush(stdin);
    scanf("%d",&deleteid);
    while (!feof(customers))
    {
        fgets(datatomove,500,customers);
        fputs(datatomove,tempcust);
        counter++;
        if(counter==deleteid)
        {
            fgets(deleteline,500,customers);
            printf("The Deleted Customer: \n");
            puts(deleteline);
        }
    }
    fclose(customers);
    fclose(tempcust);
    remove("customers.txt");
    rename ("tempcust.txt","customers.txt");
    ask_again();
}
void edit_customer()
{
    FILE *customers;
    int editid,findid=1,oldlocation,newlocation,id=1;
    char filedata[500],*c,storage[500];
    char *var_name,*var_email,*var_number,*var_method,*var_bill;
    char name[50],email[50],pmethod[50];
    int phone_no,bill;
    FILE *custo;
    custo=fopen("customers.txt","r");
    while(!feof(custo))
    {
        fgets(storage,500,custo);
        c=strtok(storage,",");
        var_name=c;
        printf("\nID: %d",id);
        printf("\nName: %s",var_name);
        c=strtok(NULL,",");
        var_email=c;
        printf("\nEmail: %s",var_email);
        c=strtok(NULL,",");
        var_number=c;
        printf("\nNumber: %s",var_number);
        c=strtok(NULL,",");
        var_method=c;
        printf("\nPayment Method: %s",var_method);
        c=strtok(NULL,",");
        var_bill=c;
        printf("\nBill: %s",var_bill);
        c=strtok(NULL,",");
        printf("\n\n");
        id++;
    }
    fclose(custo);
    customers=fopen("customers.txt","r+");
    printf("Enter the Customer ID you want to Edit: ");
    scanf("%d",&editid);
    while (!feof(customers))
    {
        fgets(filedata,500,customers);
        findid++;
        if (findid==editid)
        {
            oldlocation=ftell(customers);
            fgets(storage,500,customers);
            c=strtok(storage,",");
            var_name=c;
            printf("\nName: %s",var_name);
            c=strtok(NULL,",");
            var_email=c;
            printf("\nEmail: %s",var_email);
            c=strtok(NULL,",");
            var_number=c;
            printf("\nNumber: %s",var_number);
            c=strtok(NULL,",");
            var_method=c;
            printf("\nPayment Method: %s",var_method);
            c=strtok(NULL,",");
            var_bill=c;
            printf("\nBill: %s",var_bill);
            newlocation=ftell(customers);
            break;
        }
    }
    fseek(customers,(oldlocation-newlocation),SEEK_CUR);
    printf("\nEnter new full name: ");
    fflush(stdin);
    gets(name);
    printf("\nEnter new Email: ");
    gets(email);
    fflush(stdin);
    printf("\nEnter new Phone no: ");
    scanf("%d",&phone_no);
    fflush(stdin);
    printf("\nPayment Method(Cash Or Credit/Debit)");
    gets(pmethod);
    fflush(stdin);
    printf("Your total Bill: ");
    fflush(stdin);
    scanf("%d",&bill);
    fprintf(customers,"%s,%s,%d,%s,%d",name,email,phone_no,pmethod,bill);
    fputs("\n",customers);
    fclose(customers);
    ask_again();
}
