#include<iostream>
#include<fstream>
#include<string.h>
#include<dir.h>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
using namespace std;
float total=0.0;
class Shopping
{
    public:
    int id,counter=0;
    char product_name[20];
    float price;
    Shopping()
    {
        mkdir("C:/morphious");
    }
    void get_data()
    {
        cout<<"enter id:";
        cin>>id;
        cout<<"enter product name:";
        cin.ignore();
        cin.getline(product_name,19);
        cout<<"enter price:";
        cin>>price;
    }
    void show_data()
    {
        cout<<endl<<id<<setw(25)<<product_name<<setw(25)<<price;
    }
    int insert_data()
    {
        if(id==0&&price==0)
        {
            cout<<"data empty";
            return (0);
        }
        else
        {
            ofstream obj("C:/morphious/shopping.dat",ios::app|ios::binary);
            obj.write((char*)this,sizeof(*this));
            obj.close();
            return (1);
        }
    }
    void viewall_content(void);
    void search_data(char*);
    void delete_data(char*);
    void update_data(char*);
    void shop(void);
};
void Shopping::update_data(char* t)
{
       fstream file;
       file.open("C:/morphious/shopping.dat",ios::in|ios::binary|ios::out|ios::ate);
       file.seekg(0);
       file.read((char*)this,sizeof(*this));
       while(!file.eof())
       {
           if(!strcmp(t,product_name))
           {
               get_data();
               file.seekp(file.tellp()-sizeof(*this));
               file.write((char*)this,sizeof(*this));
           }
           file.read((char*)this,sizeof(*this));
       }
}
void Shopping::delete_data(char* t)
{
    ifstream obj("C:/morphious/shopping.dat",ios::in|ios::binary);
        if(!obj)
            cout<<"file doesn't exit";
        else
        {
            ofstream fout("C:/morphious/temp.dat",ios::out|ios::binary);
            obj.read((char*)this,sizeof(*this));
            while(!obj.eof())
            {
                if(strcmp(t,product_name))
                      fout.write((char*)this,sizeof(*this));
                else
                    counter++;
                obj.read((char*)this,sizeof(*this));
            }
            if(counter==0)
                cout<<"this data is not in file";
            else
                cout<<"deleted data successful";
            fout.close();
        }
        obj.close();
        remove("C:/morphious/shopping.dat");
        rename("C:/morphious/temp.dat","C:/morphious/shopping.dat");
}
void Shopping::search_data(char* t)
{
    ifstream obj("C:/morphious/shopping.dat",ios::in|ios::binary);
    if(!obj)
        cout<<"file doesn't exit";
    else
    {
        obj.read((char*)this,sizeof(*this));
        while(!obj.eof())
        {
            if(!strcmp(strlwr(t),strlwr(product_name)))
                {
                    counter++;
                    show_data();
                }
            obj.read((char*)this,sizeof(*this));
        }
        if(counter==0)
            cout<<"this data is not in file";
    }
    obj.close();
}
void Shopping::viewall_content()
{
    ifstream obj1("C:/morphious/shopping.dat",ios::in|ios::binary);
    if(!obj1)
        cout<<"file not found";
    else
    {
        cout<<"id"<<setw(25)<<"product name"<<setw(25)<<"price\n";
        obj1.read((char*)this,sizeof(*this));
        while(!obj1.eof())
        {
            show_data();
            obj1.read((char*)this,sizeof(*this));
        }
    }
}
int menu()
{
    int choice;
    cout<<"================                         ===================\n";
    cout<<"                  SHOPPING  MANAGEMENT\n\n";
    cout<<"************************************************************\n";
    cout<<"                  1=> MENU\n";
    cout<<"                  2=> ADD\n";
    cout<<"                  3=> UPDATE\n";
    cout<<"                  4=> SEARCH\n";
    cout<<"                  5=> DELETE\n";
    cout<<"                  6=> EXIT\n";
    cout<<"************************************************************\n";
    cout<<"Enter choice:";
    cin>>choice;
    system("cls");
    return(choice);
}
class password
{
    char user[20],passwd[20]={0};
public:
    void get()
    {
        cout<<"username:";
        cin.ignore();
        cin.getline(user,19);
        cout<<"password:";
       for(int i=0;i<20;i++)
       {
           passwd[i]=_getch();
           if(passwd[i]==13)
            break;
           cout<<"*";
       }
    }
void password_register()
{
    get();
    ofstream obj("C:/morphious/password.dat");
    obj.write((char*)this,sizeof(*this));
    obj.close();
}
int login(char* u,char* p)
{
    ifstream fin("C:/morphious/password.dat");
    if(!fin)
        return(2);
    fin.read((char*)this,sizeof(*this));
    if(!strcmp(u,user) && !strcmp(p,passwd))
            return(1);
    else
        return(0);
    fin.close();
}
};
int password_menu()
{
    cout<<"************************************************************************\n";
    cout<<"                                  1=>REGISTER\n";
    cout<<"                                  2=>LOGIN\n";
    cout<<"************************************************************************\n";
    int choice;
    cout<<"Enter choice:";
    cin>>choice;
    return (choice);
}
class user:public Shopping
{
     public:
        void shop(void);
};
void user::shop()
{
       char product[20],ch;
       viewall_content();
       cout<<"\n========================================================================";
       do{
       cout<<"\nEnter product name which you want to buy: ";
       cin.ignore();
       cin.getline(product,19);
       ifstream fin("C:/morphious/shopping.dat");
       if(!fin)
          cout<<"File not found";
      else
      {
               fin.read((char*)this,sizeof(*this));
               while(!fin.eof())
               {
                   if(!strcmp(strlwr(product),strlwr(product_name)))
                          total+=price;
                   fin.read((char*)this,sizeof(*this));
               }fin.close();
      }cout<<"if you want to purchase anything else press y: ";
               cin>>ch;}while(ch=='y' || ch=='Y');
      cout<<"\nTotal: "<<total;
}
int user_menu()
{
    int num;
    cout<<"************************************************************************\n";
    cout<<"                                  1=>  ADMIN\n";
    cout<<"                                  2=>  USER\n";
    cout<<"************************************************************************\n";
    cout<<"Enter your choice: ";
    cin>>num;
    return(num);
}
int main()
{
    user uobj;
    Shopping obj;
    char ch,user[20],passwd[20]={0},str[20];
    switch(user_menu())
    {
    case 1:
        {
    int num;
     password pobj;
     switch(password_menu())
     {
     case 1:
        pobj.password_register();
        break;
     case 2:
         cout<<"username:";
         cin.ignore();
         cin.getline(user,19);
         cout<<"password:";
         for(int i=0;i<20;i++)
        {
            passwd[i]=_getch();
            if(passwd[i]==13)
                break;
            cout<<"*";
        }
        num=pobj.login(user,passwd);
         if(num==1)
     {
         system("cls");
        do{
        switch(menu())
       {
     case 1:
        obj.viewall_content();
        break;
     case 2:
        obj.get_data();
        obj.insert_data();
        break;
      case 3:
         cout<<"enter product name which you want to update:";
         cin.ignore();
        cin.getline(str,19);
        obj.update_data(str);
        break;
      case 4:
         cout<<"Enter product name which you want to search:";
         cin.ignore();
        cin.getline(str,19);
        obj.search_data(str);
        break;
      case 5:
         cout<<"Enter product name which you want to delete:";
         cin.ignore();
        cin.getline(str,19);
        obj.delete_data(str);
        break;
      case 6:
        exit(0);
      default:
        {
            system("cls");
            cout<<"Invalid enter, try again:";;
            menu();
        }
     }
     cout<<"\nPress y for to do more operation press another key to exit: ";
     cin>>ch;
     system("cls");
     }while(ch=='y'||ch=='Y');
     }
     else if(num==2)
        cout<<"\nYou need to register it first";
     else
         cout<<"\nincorrect user and password";
        break;
      default:
        cout<<"wrong choice:";
     }
        }
     break;
      case 2:
       uobj.shop();
        break;
    default:
    cout<<"wrong choice:";
}
     getch();
     return 0;
}
