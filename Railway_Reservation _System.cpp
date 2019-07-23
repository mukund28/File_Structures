#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<iostream>
using namespace std;
static int p=0;
int no=0,days,train_fare;
char rec_ind[5],st_train[90];
int rec_flag=0;

struct record            
{
	char num[8],ind[5];
	char name[30];
	char source[50];
	char destination[10];
	char extra[100];;
}rec[20];

struct secind                       
{
	char name[20],num[8],ind[20];
}sec[20],found[10];

struct index                  
{
	char num[20],ind[20];
}in[20],temp;

void sort_index()          
{
	int i,j;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(in[j].num,in[j+1].num)>0)
	{
		temp=in[j];
		in[j]=in[j+1];
		in[j+1]=temp;
	}
} 

class railway
{
    int i;
	public:
	void main_menu();		
	void add();
	int Payment();			
	void display(); 		
	void search(char *st_name);	
	void update(char *st_name);			
	void delet(char *st_name);		
};

double TotalCharges (double baseCharges, double train_fare)
{
    return baseCharges + train_fare;
}


void sort_secindex()             
{
	int i,j;
	secind temp;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(sec[j].name,sec[j+1].name)>0) 
	{
		temp=sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
	else if(strcmp(sec[j].name,sec[j+1].name)==0)
	{
		 if(strcmp(sec[j].num,sec[j+1].num)>0)
		 {
		     temp=sec[j];
		     sec[j]=sec[j+1];
		     sec[j+1]=temp;
		 }
	}
}

int srch_train(char *num,int j)
{
int flag=0;
for(int i=0;i<j;i++)
if(strcmp(rec[i].num,num)==0)
{
flag=1;
}
if(flag)
return 1;
else
return -1;
}
void retrive_record(char *ind)
{
	int flag=0;
	for(int i=0;i<no;i++)
	{
		if(strcmp(rec[i].ind,ind)==0)
		{
			strcpy(rec_ind,ind);
			rec_flag=1;
			cout<<"\n\t\t Record found\n";
			cout<<"\n\t\t"<<rec[i].num<<"|"<<rec[i].name<<"|"<<rec[i].source<<"|"<<rec[i].destination<<"\n";
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"record search failed\n";
	}
}
void search_index(char *num)
{
	int flag=0;
	for(int	i=0;i<no;i++)
	{
		if(strcmp(in[i].num,num)==0)
		{
			retrive_record(in[i].ind);
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"index search failed\n";
	}
}



 void railway::main_menu()
{   
		fstream file1,file2,file3 ;
    	char st_name[30];
    file3.open("index.txt",ios::out);
	file1.open("record.txt",ios::out);
	file2.open("secindex.txt",ios::out);
	file3.close();
	file1.close();
	file2.close();
	
	int choice;
	while(choice!=6)
	{
		
		std::cout<<"\n\n\n\t\t\t\t* MAIN MENU *";
		std::cout<<"\n\n\n\t\t\t1.Book A Train";
		std::cout<<"\n\t\t\t2.Customer Record";
		std::cout<<"\n\t\t\t3.Search Record";
		std::cout<<"\n\t\t\t4.Delete Record";
     	std::cout<<"\n\t\t\t5.Update Record";
		std::cout<<"\n\t\t\t6.Exit";
		std::cout<<"\n\n\t\t Enter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1:	add();
				break;
			 case 2: display();
				break;
			case 3: search(st_name);
				break;
		    case 4:
				delet(st_name);
				break;
			case 5: update(st_name);
			        break;
			case 6: exit(0);
			break;
		    default:
				{
					std::cout<<"\n\n\t\t\tWrong choice.....!!!";
					std::cout<<"\n\t\t\tPress any key to continue....!!";
					getch();
				}
		}
	}
}

void railway::add()
{
	char flag;
	char num[8],ind[5];
	char name[30];
	char source[50];
	char destination[10];
	char extra[100];
	int i,n;
	
    fstream file1,file2,file3;
    file2.open("secindex.txt",ios::out);
	file1.open("record.txt",ios::app|ios::out);
	file3.open("index.txt",ios::out);

	cout<<"\n\t\t Enter Customer Details :";
	cout<<"\n\n\t\t Enter the number of customers: ";
	cin>>n;
                	for(i=no;i<no+n;i++)
				{
			  	 label:cout<<"\n\t\t Enter  "<<i+1<<"  passenger details:\n"; 
			  	    cout<<"\n\t\t Enter the Train number:";
			  	    cin>>rec[i].num;
			  	    int q=srch_train(rec[i].num,i);
					if(q==1)
					{
					cout<<"\n\t\t Train is already booked .Try with another Train no\n";
					goto label;
					}
					cout<<"\n\t\t Name:";
					cin>>rec[i].name;
					cout<<"\n\t\t Source:";
					cin>>rec[i].source;
					cout<<"\n\t\t Destination:";	
					cin>>rec[i].destination;			    
					file1<<i<<"|"<<rec[i].num<<"|"<<rec[i].name<<"|"<<rec[i].source<<"|"<<rec[i].destination<<"\n";
					Payment();
				    cout<<"\n\t\t Train is booked...!!!\n";
            }
				file1.close();
				no=no+n;
				file1.open("record.txt",ios::in);
				for(i=0;i<no;i++)
				{
					file1.getline(ind,5,'|');
					file1.getline(num,20,'|');
					file1.getline(name,30,'|');
					file1.getline(source,50,'|');
					file1.getline(destination,10,'\n');  
					strcpy(rec[i].ind,ind);
					strcpy(sec[i].ind,ind);
					strcpy(in[i].ind,ind);
					strcpy(sec[i].name,name);
					strcpy(sec[i].num,num);
					strcpy(in[i].num,num);
				}

				sort_index();
				sort_secindex();
				cout<<"\n\t\t After sorting index file contents are:\n";
				for(i=0;i<no;i++)
				cout<<"\n\t\t"<<in[i].num<<"|"<<in[i].ind<<endl;
				cout<<"\n\t\t After sorting secindex file contents are:\n";
				for(i=0;i<no;i++)
				cout<<"\n\t\t"<<sec[i].name<<"|"<<sec[i].num<<"|"<<sec[i].ind<<endl;
				
				for(i=0;i<no;i++)
				{
					file3<<in[i].num<<"|"<<in[i].ind<<"\n";
					file2<<sec[i].name<<"|"<<sec[i].num<<"|"<<sec[i].ind<<"\n";
					
				}
				file1.close();
				file2.close();
				file3.close();
	
		
	}
	int railway::Payment()
{
    
    int trainType ;
    do {
        cout << "\n\t\tPlease choose the compartment from the following options:\n"
                     "\t\tEnter 1 for the 1 AC.\n"
                     "\t\tEnter 2 for the 3 tier Ac.\n"
                     "\t\tEnter 3 for the Slepper Class.\n\t\t\n\t\t >> ";
        cin >>trainType;

        if (trainType < 1|| trainType > 3)
        {
            cout << "\n\t\t Please enter a valid number.\n";
        }
        else { 
		break; 
		}
    } while (trainType < 1 || 3 < trainType);
    

    switch (trainType)
    {
    case 1:
        train_fare = 2500;
        break;
    case 2:
        train_fare = 1500;
        break;
    case 3:
        train_fare = 750;
        break;
    default:
        cout << "\n\t\t Enter the correct compartment type\n";
        return 1;
    }
    
double TotalCharges (double FoodCost, double train_fare);
char Food ;
double FoodCost ;
    do {
        cout << "\n\t\t Does the customer wants food during his journey? ";
        cin >> Food;
        if (Food == 'Y' || Food == 'y')
        {
            FoodCost = 300;
            break;
        }
        else if (Food == 'N' || Food == 'n')
        {
            FoodCost = 0;
            break;
        }
        else
        {
            cout << "\n\t\t You entered an invalid answer.\n";
        }
    } while (   Food != 'Y' || Food != 'y' || Food != 'N' || Food != 'n');

    double totalCharges = TotalCharges(FoodCost,train_fare);
    cout << "\n\t\t The Total charges to be paid by the customer is Rs:" << totalCharges << " \n\n";
    return 0;
}

	void railway::display()
	{
				fstream file1;
				char num[8],ind[5];
	            char name[30];
	            char source[50];
	            char destination[10];
				file1.open("record.txt",ios::in);
			   cout<<"\n\t\t TRAIN\t NAME\t SOURCE\t DESTINATION\n";
				while(!file1.eof())
				{

					file1.getline(ind,5,'|');
					file1.getline(num,20,'|');
					file1.getline(name,30,'|');
					file1.getline(source,50,'|');
					file1.getline(destination,10,'\n');
			     cout<<"\t\t"<<num<<"\t"<<name<<"\t"<<source<<"\t"<<destination<<"\n";
			     }
			     file1.close();
				}


void railway::search(char *st_train)
{
	int flag1=0;
	int k=0,i;
	cout<<"\n\t\t Enter the name of the customer:";
	cin>>st_train;
	for(i=0;i<no;i++)
	{
		if(strcmp(sec[i].name,st_train)==0)
		{
			strcpy(found[k].num,sec[i].num);
			strcpy(found[k].name,sec[i].name);
			strcpy(found[k].ind,sec[i].ind);
			flag1=1;
			k++;
		}
	}
	if(!flag1)
	{
		cout<<"\n\t\t sec ind search failed\n";
		return;
	}
	cout<<"\n\t\t Records matching are:\n";
	for(i=0;i<k;i++)
	cout<<"\n\t\t"<<found[i].name<<" "<<found[i].num;
	cout<<"\n\t\t Choose a train number :";
	cin>>st_train;
	flag1=0;
	for(i=0;i<k;i++)
		if(strcmp(found[i].num,st_train)==0)
		{
			search_index(st_train);
			flag1=1;
		}
	if(!flag1)
	{
		cout<<"\n\t\t Wrong train no search failed\n";
	}
}
void railway:: delet(char *st_train)
{
	rec_flag=0;
	int fr=0;
	search(st_train);
	if(!rec_flag)
	{
		cout<<"\n\t\t Deletion failed record not found\n";
		return;
	}
	for(int i=0;i<no;i++)
	{
		if(strcmp(rec[i].ind,rec_ind)==0)
			{
			fr=i;
			break;
			}
	}
	for(int i=fr;i<no-1;i++)
	{
		rec[i]=rec[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(rec[i].ind,str);
	}
	no--;

	fstream f1,f2,f3;
	f1.open("record.txt",ios::out);
	f3.open("index.txt",ios::out);
	f2.open("secindex.txt",ios::out);
	for(int i=0;i<no;i++)
	{
	strcpy(sec[i].name,rec[i].name);
	strcpy(sec[i].num,rec[i].num);
	strcpy(in[i].num,rec[i].num);
	strcpy(sec[i].ind,rec[i].ind);
	strcpy(in[i].ind,rec[i].ind);

	}
	sort_index();
	sort_secindex();
	for(int i=0;i<no;i++)
	{
		f1<<rec[i].ind<<"|"<<rec[i].num<<"|"<<rec[i].name<<"|"<<rec[i].source<<"|"<<rec[i].destination<<"\n";
		f3<<in[i].num<<"|"<<in[i].ind<<"\n";
		f2<<sec[i].name<<"|"<<sec[i].num <<"|"<<sec[i].ind<<"\n";
	}

	f1.close();
	f2.close();
	f3.close();
	cout<<"\n\t\t Deletion Successfull\n";
}
void railway::update(char *st_name)
{
	rec_flag=0;
	int fr=0;
	search(st_name);
	if(!rec_flag)
	{
		cout<<"\n\t\t Failed record not found";
		return;
	}
	for(int i=0;i<no;i++)
	{
		if(strcmp(rec[i].ind,rec_ind)==0)
			{
			cout<<"\n\t\t The old values of the record  are ";
    cout<<"\n\t\t num  = "<<rec[i].num;
    cout<<"\n\t\t name   = "<<rec[i].name;
    cout<<"\n\t\t source   = "<<rec[i].source;
    cout<<"\n\t\t destination   = "<<rec[i].destination;


    cout<<"\n\n\n\t\t Enter the new values \n";
    cout<<"\n\t\t num  = ";  cin>>rec[i].num;
    cout<<"\n\t\t name   = ";  cin>>rec[i].name;
    cout<<"\n\t\t source  = ";  cin>>rec[i].source;
    cout<<"\n\t\t destination  = ";  cin>>rec[i].destination;
    break;
			}
	}

	fstream f1,f2,f3;
	f1.open("record.txt",ios::out);
	f3.open("index.txt",ios::out);
	f2.open("secindex.txt",ios::out);
	for(int i=0;i<no;i++)
	{
	strcpy(sec[i].name,rec[i].name);
	strcpy(sec[i].num,rec[i].num);
	strcpy(in[i].num,rec[i].num);
	strcpy(sec[i].ind,rec[i].ind);
	strcpy(in[i].ind,rec[i].ind);

	}
	sort_index();
	sort_secindex();
	for(int i=0;i<no;i++)
	{
		f1<<rec[i].ind<<"|"<<rec[i].num<<"|"<<rec[i].name<<"|"<<rec[i].source<<"|"<<rec[i].destination<<"\n";
		f3<<in[i].num<<"|"<<in[i].ind<<"\n";
		f2<<sec[i].name<<"|"<<sec[i].num <<"|"<<sec[i].ind<<"\n";
	}

	f1.close();
	f2.close();
	cout<<"\n\t\t Updation successful\n";
}
    

int main()
{
	railway h;
	
	std::cout<<"\n\t\t\t* RAILWAY RESERVATION SYSTEM *";
	
	
	h.main_menu();
}



