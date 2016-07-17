#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream.h>
void destination();
class train
{
  protected : int seat_1,seat_2,seat_3;
	      int block_1,block_2,block_3;
  public : int tot_cust;
	   class customer
	   {
	     char name[30];
	     char id;
	     int age;
	     char gender;
	     public : int class_reserve;
		      int seats;
		      double cost;
		      customer(){id=0;class_reserve=0;seats=0;cost=0;}
		      void get_data();
		      void put_data();
		      char get_id(){return id;}
		      int get_age(){return age;}
	    };
	    customer cust[5];
	    train()
	    {
	     seat_1 =20 ;
	     seat_2 =30;
	     seat_3 =50;
	     block_1=0;
	     block_2=0;
	     block_3=0;
	     tot_cust=0;
	    }
};
class reserve_cancel : public train
{
  protected : int train_no;
  public : reserve_cancel(int i){train_no=i;}
	   void reserve();
	   void cancel();
	   void display();
	   void display2();
	   void init_train_no(int i){train_no=i;}
	   int get_train_no(){return train_no;}
};
reserve_cancel ob(0),rc[3]={101,102,103};
void train :: customer :: get_data()
{
  cout<<"\nCUSTOMER DETAILS :";
  cout<<"\n Enter the name :";
  gets(name);
  cout<<"\n Enter the id :";
  cin>>id;
  cout<<"\n Enter the age :";
  cin>>age;
  cout<<"\n Enter the gender (f/m) :";
  cin>>gender;
}
void train :: customer :: put_data()
{
 cout<<"\n\n DETAILS OF PERSON :";
 cout<<"\n\n Name : "<<name<<"\n Id : "<<id<<"\n Age : "<<age<<"\n Gender : "<<gender;
 cout<<"\n Class booked :"<<class_reserve<<"\n Seats booked :"<<seats<<"\n"<<"\n Total Cost :"<<cost;
}
void reserve_cancel :: reserve()
{
  int i,pos,num;
  fstream f("railway_reservation.dat",ios::out|ios::in);
  while(!f.eof())
  {
   pos=f.tellg();
   f.read((char*)&ob,sizeof(reserve_cancel));
   if(ob.get_train_no()==train_no)
   {
     if(ob.tot_cust<5)
     {
       ob.cust[tot_cust].get_data();
       ob.tot_cust++;
       cout<<"\n Enter in which class you wish to reserve :";
       cin>>ob.cust[tot_cust].class_reserve;
       cout<<"\n Enter the number of seats :";
       cin>>num;
       if(ob.cust[tot_cust].class_reserve==1)
       {
	 if(ob.block_1+num<=ob.seat_1)
	 {
		 ob.block_1+=num;
		 if(ob.cust[tot_cust].get_age()<60) ob.cust[tot_cust].cost=num*50;
		 else
		 {
		  cout<<"\n Customer is a SENIOR citizen.You get 25 % concession !!";
		  ob.cust[tot_cust].cost=(0.25*50)+(num-1)*50;
		 }
		 ob.cust[tot_cust].seats=num;
		 cout<<"\n Reservation Successful";
		 cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[tot_cust].cost;
		 ob.display();

	 }
	  else
	  {
	    cout<<"\n Reservation not possible";
	    ob.tot_cust--;
	  }
       }
       else if(ob.cust[tot_cust].class_reserve==2)
       {
	  if(ob.block_2+num<=ob.seat_2)
	  {
		 ob.block_2+=num;
		 if(ob.cust[tot_cust].get_age()<60) ob.cust[tot_cust].cost=num*40;
		 else
		 {
		  cout<<"\n Customer is a SENIOR citizen.You get 25 % concession !!";
		  ob.cust[tot_cust].cost=(0.25*40)+(num-1)*40;
		 }
		 ob.cust[tot_cust].seats=num;
		 cout<<"\n Reservation Successful";
		 cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[tot_cust].cost;
		 ob.display();
	  }
	  else
	  {
	      cout<<"\n Reservation not possible";
	      ob.tot_cust--;
	  }
	}
	else if(ob.cust[tot_cust].class_reserve==3)
	{
	  if(ob.block_3+num<=ob.seat_3)
	  {
		 ob.block_3+=num;
		 if(ob.cust[tot_cust].get_age()<60) ob.cust[tot_cust].cost=num*30;
		 else
		 {
		  cout<<"\n Customer is a SENIOR citizen.You get 25 % concession !!";
		  ob.cust[tot_cust].cost=(0.25*30)+(num-1)*30;
		 }
		 ob.cust[tot_cust].seats=num;
		 cout<<"\n Reservation Successful";
		 cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[tot_cust].cost;
		 ob.display();
	   }
	   else
	   {
	     cout<<"\n Reservation not possible";
	     ob.tot_cust--;
	   }
	}
	else cout<<"\n Invalid class";
     }
     else cout<<"\n Fully booked";
     f.seekg(pos);
     f.write((char*)&ob,sizeof(reserve_cancel));
     break;
   }
 }
}
void reserve_cancel :: cancel()
{
  int i,class_reserve,num,pos,j,found=0;
  fstream f("railway_reservation.dat",ios::in|ios::out);
  char cust_id;
  while(!f.eof())
  {
   pos=f.tellg();
   f.read((char*)&ob,sizeof(reserve_cancel));
   if(ob.get_train_no()==train_no)
   {
       cout<<"\n Enter the customer id :";
       cin>>cust_id;
       for(i=0;i<ob.tot_cust;i++)
       {
	 if(ob.cust[i].get_id()==cust_id)
	 {
	    found=1;
	    ob.cust[i].put_data();
	    cout<<"\n Enter the number of seats you wish to cancel :";
	    cin>>num;
	    if(ob.cust[i].class_reserve==1)
	    {
	       if(num<=ob.cust[i].seats)
		  {
			   if(num==ob.cust[i].seats)
			   {
			     ob.tot_cust--;
			     ob.cust[i].cost=0;
			    }
			    else ob.cust[i].cost-=num*50;
			    ob.block_1-=num;
			   ob.cust[i].seats-=num;
			   cout<<"\n Cancellation Successful";
			   cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[i].cost;
			   ob.display();
			   break;
		  }
		  else cout<<"\n Cancellation NOT succesful.";
	    }
	    else if(ob.cust[i].class_reserve==2)
	    {
		if(num<=ob.cust[i].seats)
		{
			   if(num==ob.cust[i].seats)
			   {
			     ob.tot_cust--;
			     ob.cust[i].cost=0.0;
			   }
			   else ob.cust[i].cost-=num*40;
			   ob.block_2-=num;
			   ob.cust[i].seats-=num;
			   cout<<"\n Cancellation Successful";
			   cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[i].cost;
			   ob.display();
			   break;

		}
		else cout<<"\n Cancellation NOT succesful.";
	    }
	    else if(ob.cust[i].class_reserve==3)
	    {
		  if(num<=ob.cust[i].seats)
		  {
			   if(num==ob.cust[i].seats)
			   {
			     ob.tot_cust--;
			     ob.cust[i].cost=0;
			    }
			    else ob.cust[i].cost-=num*30;
			   ob.block_3-=num;
			   ob.cust[i].seats-=num;
			   cout<<"\n Cancellation Successful";
			   cout<<"\n\nTotal cost for customer is Rs."<<ob.cust[i].cost;
			   ob.display();
			   break;
		  }
		  else cout<<"\n Cancellation NOT succesful.";
	    }//end else if
	    break;
	 } //if id
       }//for i
       if(found==0) cout<<"\n Invalid customer id";
       f.seekg(pos);
       f.write((char*)&ob,sizeof(reserve_cancel));
   }//if train number
  }
}
void reserve_cancel :: display()
{
   cout<<"\n\n ***********************NET BOOKING STATUS********************************\n";
   cout<<"\nTRAIN NO.:"<<train_no<<"\n";
   cout<<"\n--------------------------------------------------------------------------------";
   cout<<"\n  SECTION   *   Total   *   Reserved   *   Remaining   *   Rate per ticket \n";
   cout<<"\n--------------------------------------------------------------------------------\n";
   cout<<"\n 1st CLASS       "<<seat_1<<"            "<<block_1<<" \t      "<<seat_1-block_1<<"         \t  Rs.50";
   cout<<"\n 2nd CLASS       "<<seat_2<<"            "<<block_2<<" \t      "<<seat_2-block_2<<"         \t  Rs.40";
   cout<<"\n 3rd CLASS       "<<seat_3<<"            "<<block_3<<" \t      "<<seat_3-block_3<<"         \t  Rs.30";
   cout<<"\n\n-------------------------------------------------------------------------------";
}
void reserve_cancel :: display2()
{
   ifstream f("railway_reservation.dat");
   char cust_id;
   int i;
   while(!f.eof())
   {
     f.read((char*)&ob,sizeof(reserve_cancel));
     if(ob.get_train_no()==train_no)
     {

       cout<<"\n Enter the customer id :";
       cin>>cust_id;
       for(i=0;i<ob.tot_cust;i++)
       {
	 if(ob.cust[i].get_id()==cust_id)
	 {
	    ob.cust[i].put_data();
	    break;
	  }
       }
       cout<<"\n\n ***********************NET BOOKING STATUS********************************\n";
       cout<<"\nTRAIN NO.:"<<train_no<<"\n";
       cout<<"\n--------------------------------------------------------------------------------";
       cout<<"\n  SECTION   *   Total   *   Reserved   *   Remaining   *   Rate per ticket \n";
       cout<<"\n--------------------------------------------------------------------------------\n";
       cout<<"\n 1st CLASS       "<<ob.seat_1<<"            "<<ob.block_1<<" \t      "<<ob.seat_1-ob.block_1<<"         \t  Rs.50";
       cout<<"\n 2nd CLASS       "<<ob.seat_2<<"            "<<ob.block_2<<" \t      "<<ob.seat_2-ob.block_2<<"         \t  Rs.40";
       cout<<"\n 3rd CLASS       "<<ob.seat_3<<"            "<<ob.block_3<<" \t      "<<ob.seat_3-ob.block_3<<"         \t  Rs.30";
       cout<<"\n\n-------------------------------------------------------------------------------";
       break;
    }
   }

}
void destination()
{
 cout<<"\n\n                     DESTINATIONS ";
 cout<<"\n---------------------------------------------------------------";
 cout<<"\n Sl.no\t\t  From\t\t  To\t\tTrain number";
 cout<<"\n---------------------------------------------------------------";
 cout<<"\n\n (1)\t\t Bangalore\t Delhi\t\t\t101";
 cout<<"\n (2)\t\t Delhi\t\t Mumbai\t\t\t102";
 cout<<"\n (3)\t\t Mumbai\t\t Bangalore\t\t103\n";
 cout<<"\n---------------------------------------------------------------";
}

void main()
{
  int choice,train_no,i,found=0;
  char c;
  reserve_cancel rc[3]={101,102,103};
  clrscr();
  do{
    found=0;
    cout<<"\n\n   WELCOME TO ONLINE RAILWAY RESERVATION \n\n";
    cout<<"\n What do you wish to do ?";
    cout<<"\n (1) Reservation.\n (2) Cancellation\n (3) Display\n (4) Exit";
    cout<<"\n Enter the choice :";
    cin>>choice;
    switch(choice)
    {
       case 1 : destination();
		cout<<"\n Enter the train number :";
		cin>>train_no;
		for(i=101;i<104;i++)
		{
		 if(train_no==i)
		 {
		   rc[i-101].reserve();
		   found=1;
		   break;
		 }
		}
		if(found==0) cout<<"\n Invalid option.";
		break;
       case 2 : destination();
		cout<<"\n Enter the train number :";
		cin>>train_no;
		for(i=101;i<104;i++)
		{
		 if(train_no==i)
		 {
		  rc[i-101].cancel();
		  found=1;
		  break;
		 }
		}
		if(found==0) cout<<"\n Invalid option.";
		break;
       case 3 : destination();
		cout<<"\n Enter the train number for which the details you wish to view : ";
		cin>>train_no;

		for(i=101;i<104;i++)
		{
		 if(train_no==i)
		 {
		  rc[i-101].display2();
		  found=1;
		  break;
		 }
		}
		if(found==0) cout<<"\n Invalid option.";
		break;
       case 4 : exit(0);
       default :cout<<"\n Invalid Choice!!! ";
    }
    cout<<"\n Do you wish to continue ? (y/n) :";
    cin>>c;
   }while(c=='y'||c=='Y');
   getch();
}
