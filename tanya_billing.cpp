#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

//declaring global variables
int r=0,option=0,m=10;

COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

struct date
{
    int month,day,year;
};

ofstream fout;
ifstream fin;

class item
{
    int item_no;
    char item_name[25];
    date d;
public:
    void add()
    {
        cout<<"\n\n\tItem No: ";
        cin>>item_no;
        cout<<"\n\n\tName of the item: ";
        cin>>item_name;
//gets(name);
        cout<<"\n\n\tManufacturing Date(dd-mm-yyyy): ";
        cin>>d.month>>d.day>>d.year;
    }
    void show()
    {
        cout<<"\n\tItem No: ";
        cout<<item_no;
        cout<<"\n\n\tName of the item: ";
        cout<<item_name;
        cout<<"\n\n\tDate : ";
        cout<<d.month<<"-"<<d.day<<"-"<<d.year;
    }
    void report()
    {
        gotoxy(6,m);
        cout<<item_no;
        gotoxy(16,m);
        puts(item_name);
    }

    int return_no()
    {
        return(item_no);

    }

};

class amount: public item
{
    float price,quantity,tax,gross,discount,net_amount;
public:
    void add_price();
    void show_amount();
    void report();
    void calculate_price();
    void pay();
    float return_net_amount()
    {
        return(net_amount);
    }
} amt;

void amount::add_price()
{
    item::add();
    cout<<"\n\n\tPrice: ";
    cin>>price;
    cout<<"\n\n\tQuantity: ";
    cin>>quantity;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>discount;
    calculate_price();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate_price()
{
    gross=price+(price*(tax/100));
    net_amount=quantity*(gross-(gross*(discount/100)));
}
void amount::show_amount()
{
    fin.open("store_information.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\tNet amount: ";
    cout<<net_amount;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,m);
    cout<<price;
    gotoxy(33,m);
    cout<<quantity;
    gotoxy(44,m);
    cout<<tax;
    gotoxy(52,m);
    cout<<discount;
    gotoxy(64,m);
    cout<<net_amount;
    m=m+1;
    if(m==50)
    {
        gotoxy(25,50);
        cout<<"======PRESS ANY KEY TO CONTINUE======";
        getch();
        m=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tPRICE                     :"<<price;
    cout<<"\n\n\t\tQUANTITY                  :"<<quantity;
    cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<discount;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<net_amount;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"*************TANYA'S SUPERMARKET BILLING COUNTER*****************";
    gotoxy(25,3);

    cout<<"\n\t\t1.Bill Report\n\n";
    cout<<"\t\t2.Add/Remove/Edit Item\n\n";
    cout<<"\t\t3.Show Item Details\n\n";
    cout<<"\t\t4.Exit\n\n";
    cout<<"\t\t===PLEASE ENTER THE REQUIRED OPTION===";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Details";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\t===PLEASE ENTER THE REQUIRED OPTION===";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("store_information.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\n===FILE NOT FOUND===";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.return_net_amount();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,m);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"TANYA'S BILLING SYSTEM";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("store_information.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\t====ITEM ADDED SUCCESSFULY===";
            getch();
            goto db;

        case 2:
            int ino;
            option=0;
            cout<<"\n\n\t===ENTER NUMBER TO BE EDITED===";
            cin>>ino;
            fin.open("store_information.dat",ios::binary);
            fout.open("store_information.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\n===FILE NOT FOUND==";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::return_no();
                    if(x==ino)
                    {
                        option=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\tCurrent Details are\n";
                        amt.show();
                        cout<<"\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout<<"\n\t\tItem Details editted";
                    }
                }
                r++;
            }
            if(option==0)
            {
                cout<<"\n\t\t====ITEM DOEST NOT EXIST===TRY AGAIN===";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            option=0;
            cout<<"\n\n\t====ENTER ITEM TO BE DELETED====";
            cin>>ino;
            fin.open("store_information.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\n===FILE NOT FOUND===";
                goto menu;
            }

            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::return_no();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    option=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("store_information.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(option==1)
                cout<<"\n\t\t===ITEM SUCCESSFULY DELETED===";
            else if (option==0)
                cout<<"\n\t\t====ITEM DOES NOT EXIST===PLEASE TRY AGAIN====";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\t====WRONG CHOICE===TR AGAIN====";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        option=0;
        int item_no;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>item_no;
        fin.open("store_information.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\n===file not found===\n===Program Terminated===";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::return_no();
            if(x==item_no)
            {
                amt.pay();
                option=1;
                break;
            }
        }
        if(option==0)
            cout<<"\n\t\t=====ITEM DOES NOT EXIST====TRY AGAIN=====";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"=====ARE YOU SURE, YOU WANT TO EXIT (Y/N)?======";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\t==WRONG CHOICE=========Try again==";
        getch();
        goto menu;
    }
    return 0;
}
