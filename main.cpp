#include<iostream>
#include<windows.h>
#include<conio.h>
#include<mysql.h>
#include<sstream>
#include<stdlib.h>


using namespace std;


const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "kiprime";
unsigned int port = 3306 ;
const char* unixsocket =NULL ;
unsigned long clientflag = 0;

MYSQL* connectdatabase()
{
    MYSQL*conn;
    conn= mysql_init(0);
    conn= mysql_real_connect(conn,hostname,username,password,database,port,unixsocket,clientflag);
    if(conn){
        cout<<"Database connected successfully!"<<endl;
        return conn;
    }
    else{
        cout<<" Oops! Database connection failed! "<<endl;
        return conn;
    }
}

insert(MYSQL*conn)
{
      int qstate=0;
      stringstream ss;
	string name,stud_id,aadhar,guardian,course,duration,fee,marks,gender,phone,email,location;

    cout << "\n\n\t\t\t * INSERT A NEW STUDENT'S RECORD: * ";
    cout << "\n\n\n ENTER THE NAME OF STUDENT : ";
    cin >> name;
    cout << "\n\n STUDENT-ID : ";
    cin >> stud_id;
    cout<<"\n\n ENTER THE LAST 4 DIGITS OF AADHAR NO. : ";
    cin>>aadhar;
    cout<<"\n\n NAME OF GUARDIAN : ";
    cin>>guardian;
    cout<<"\n\n COURSE ENROLLED :  ";
    cin>>course;
    cout<<"\n\n DURATION OF COURSE (in months) : ";
    cin>>duration;
    cout<<"\n\n COURSE FEE : ";
    cin>>fee;
    cout<<"\n\n MARKS : ";
    cin>>marks;
    cout<<"\n\n GENDER : ";
    cin>>gender;
    cout<<"\n\n PHONE No. : ";
    cin>>phone;
    cout<<"\n\n EMAIL ADDRESS : ";
    cin>>email;
    cout<<"\n\n LOCATION : ";
    cin>>location;



ss <<  "INSERT INTO kproject (NAME,STUD_ID,AADHAR,GUARDIAN,COURSE,DURATION,FEE,MARKS,GENDER,PHONE,EMAIL,LOCATION)VALUES('"+name+"','"+stud_id+"','"+aadhar+"','"+guardian+"','"+course+"','"+duration+"','"+fee+"','"+marks+"','"+gender+"','"+phone+"','"+email+"','"+location+"' )";
    string query = ss.str();
    const char* q= query.c_str();
    qstate = mysql_query(conn,q);
    if(qstate==0){
            system("cls");
        cout<<"\n\n\n\nRecord inserted successfully! .......\n";
    }
else {
        cout<<"\n\n\n\nFailed to insert! ........\n";
}
}
display(MYSQL*conn)
{
    MYSQL_ROW row;
    MYSQL_RES *res;
   	cout << "\n\n\t\t                                               ~~*~ STUDENTS DETAILS ~*~~~\n\n\n\n" << endl;

    cout<<"\t -----------------------------------------------------------------------------------------------------------------------------------------\n\n";
    cout<<"\t  NAME         STUD-ID AADHAR-No. GUARDIAN     COURSE DUR(in months) FEE MARKS   GENDER   PHONE            EMAIL-ID             LOCATION\n\n";
    cout<<"\t -----------------------------------------------------------------------------------------------------------------------------------------\n\n";

    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM kproject");
    if (!qstate)
    {
        res= mysql_store_result(conn);
        int count = mysql_num_fields(res);
        while(row=mysql_fetch_row(res))
        {
            for(int i=0;i<count;i++)
            {
                cout<<"\t "<<row[i];
            }
            cout<<endl;
        }
    }
    }
    else{
        cout<<"Failed to fetch any data! ";
    }
}

modify(MYSQL*conn)
{

        int x;
        int markc;
        int feed;
        int dr;
        if(conn)
    {
        int qstate = 0;
        string name;
        cout << "\t\tPlease enter the student's id for whom you want to make changes : ";
        cin>>name;

         cout<<"\n\n\n\n\t    1. UPDATE MARKS \n"<<endl;
         cout<<"\n\n\t    2. UPDATE FEES \n"<<endl;
         cout<<"\n\n\t    3. CHANGE COURSE DURATION \n"<<endl;

         cout<<"\n\tEnter your choice : ";
         cin>>x;

         if(x==1)
         {

             cout<<"\n\n\tENTER NEW MARKS : "<<" ";
             cin>>markc;




                   stringstream ss;
                      ss << "UPDATE kproject SET MARKS =  " << markc  << " WHERE STUD_ID = '" << name << "'";

                  string query = ss.str();

                   const char* q = query.c_str();
                   qstate = mysql_query(conn, q);
                   if(qstate == 0){
                        system("cls");
                   cout << "\n\nRecord Updated successfully! ..." << endl;
                   }
                   else{
                       cout<<"\n\nError! Record not updated";
                   }

        }

        else if(x==2)
         {

             cout<<"\n\n\tENTER NEW FEE : "<<" ";
             cin>>feed;

                   stringstream ss;
                      ss << "UPDATE kproject SET FEE =  " << feed << " WHERE STUD_ID = '" << name << "'";

                  string query = ss.str();

                   const char* q = query.c_str();
                   qstate = mysql_query(conn, q);
                   if(qstate == 0){
                        system("cls");
                   cout << "\n\nRecord Updated successfully! ..." << endl;
                   }
                   else{
                       cout<<"\n\nError! Record not updated";
                   }

        }

        else  if(x==3)
         {

             cout<<"\n\n\tENTER THE NEW DURATION OF COURSE : "<<" ";
             cin>>dr;

                   stringstream ss;
                      ss << "UPDATE kproject SET DURATION =  " << dr << " WHERE STUD_ID = '" << name << "'";

                  string query = ss.str();

                   const char* q = query.c_str();
                   qstate = mysql_query(conn, q);
                   if(qstate == 0){
                        system("cls");
                   cout << "\n\nRecord Updated successfully! ..." << endl;
                   }
                   else{
                       cout<<"\n\nError! Record not updated";
                   }
        }
        else{
            cout<<"INVALID CHOICE! ";
        }
    }
}


 deletee(MYSQL*conn)
 {
 MYSQL_ROW row;
 MYSQL_RES* res;
 string  codes;

 cout<<"\t\tPlease enter the student's id of whom you want to delete details : ";

 cin>>codes;
 stringstream ss,sss;

 sss<< "SELECT * FROM kproject where STUD_ID='"+codes+"'";
 string query = sss.str();
 const char *q = query.c_str();
 mysql_query(conn,q);
 res = mysql_store_result(conn);
 int count = mysql_num_fields(res);
 my_ulonglong x= mysql_num_rows(res);
 if(x>0)
    {
    ss<< "DELETE FROM kproject WHERE STUD_ID ='"+codes+"'";
    string query= ss.str();
    const char *q = query.c_str();
    mysql_query(conn,q);
    system("cls");
    cout<<" Record found... \n\n\n Record deleted successfully!";
 }
 else {
    cout<<"No Record Found";
 }

 }

  int main()
   {
       int s,ko;
       int x;
      MYSQL*conn= connectdatabase();
 op:
    cout << "\n\n\t\t                                             ############################################################################################" << endl;
    cout <<     "\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             #                      ~~* WELCOME TO OUR STUDENT MANAGEMENT SYSTEM *~~                    #" << endl;
    cout <<     "\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             #                                                                                          #";
	cout <<   "\n\t\t                                             ############################################################################################" << endl;

	cout<<endl;
	cout<<endl;

	cout<<"\n\n\t\t ..........CONTROL PANEL..........";
	cout<<"\n\n\n\t\t\t\t LOGIN AS:";
	cout<<endl;
	cout<<endl;
	cout<<"\n\n\t\t 1. ADMIN LOGIN  ";
	cout<<endl;
	cout<<"\n\n\t\t 2. STUDENT LOGIN ";
	cout<<endl;
	cout<<"\n\n\t\t Enter your choice:  ";

	cin>>s;

	if(s==1)

 {
     system("cls");
	string username;
	char password[10];
	string usrn;
	 char pswd[10];

	cout << "\n\n\n\t\t*   SIGN UP AS ADMIN: *" << endl;
	cout << "\n\n\n\t\t\t\t Please enter a username for your account: ";
	cin >> username;
	cout << "\n\n\n\t\t\t\t Please enter a 7 digit password for your account: ";
	for( ko=0;ko<7;ko++)
	 {
	  password[ko]=_getch();
	  cout<<"*";
	 }
	cout << "\n\n\n\n\t\tSigning you up as an admin...Please wait!  ";

	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		Sleep(500);
	}
	cout << "\n\n\t\tSigned up successfully! ";
	Sleep(2000);
     start:

	system("CLS");

admin:

	cout << "\n\n\t * WELCOME TO ADMIN PANEL *  " << endl;
	cout << "\n\n\t  PLEASE LOGIN " << endl;
	cout << "\n\t\tEnter your username: ";
	cin >> usrn;
	cout << "\n\n\t\tEnter password: ";
	for(ko=0;ko<7;ko++)
    {
	  	  pswd[ko]=_getch();
	      cout<<"*";

    }


	if (usrn == username)

	{
		system("CLS");
		int x;

		while (1) {



              cout<<"\n\n\t* ADMIN CONTROL PANEL *";
              cout<<"\n\n\n 1. INSERT A NEW STUDENT'S DETAILS ";
              cout<<"\n 2. MODIFY A STUDENT'S DETAILS ";
              cout<<"\n 3. DELETE A STUDENT'S DETAILS ";
              cout<<"\n 4. DISPLAY ALL THE STUDENT DETAILS ";
              cout<<"\n 5. Back To Main Menu";
              cout<<"\n 6. Exit ";
              cout<<"\n\n Please enter your choice:  ";
              cin>>x;

			system("CLS");
			switch(x)
             {
			case 1:insert(conn);
                    system("pause");
                    system("cls");
				break;
			case 2: modify(conn);
			system("pause");
                    system("cls");
				break;
			case 3: deletee(conn);
			system("pause");
                    system("cls");
				break;
            	case 4: display(conn);
            	system("pause");
                    system("cls");
                 		break;
            	case 5:
                    system("cls");
                    goto op;
				 break;
			case 6:exit(0);
			     break;

			default:cout << "\n\nInvalid Input" << endl;
			return (0);
			}
		}
	}


	else if (usrn != username)
	{
		cout << "\n\t\tInvalid credentials please try again";
		Sleep(2000);
		system("cls");
		goto admin;
	}
    }
 else if(s==2){
	system("cls");
      string username;
      char password[10];
	string usrn;
	char pswd[10];

	cout << "\n\n\n\t\t* STUDENT SIGN UP *" << endl;
	cout << "\n\n\n\t\tPlease enter a username : ";
	cin >> username;
	cout << "\n\n\t\tPlease enter a 7 digit password : ";
		for(ko=0;ko<7;ko++)
	     {
	       password[ko]=_getch();
	       cout<<"*";
	     }

	cout << "\n\n\n\n\t\tSigning up as a student...Please wait!   ";

	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		Sleep(1000);
	}
	cout << "\n\n\t\tSigned up successfully!";
	Sleep(2000);
	system("CLS");
on:
	cout << "\n\n\t    * STUDENT  CONTROL PANEL * " << endl;
	cout << "\n\n\n\t\t  STUDENT  LOGIN ---" << endl;
	cout << "\n\t\tPlease enter your username : ";
	cin >> usrn;
	cout << "\n\n\t\tPlease enter your password : ";
		for(ko=0;ko<7;ko++)
         {
	  	  pswd[ko]=_getch();
	      cout<<"*"; }

	if (usrn == username)
	{
		system("CLS");
		int x;

		display(conn);
		system("PAUSE");
		system("cls");
		goto op;
	}
	else {
		cout << "\n\t\tInvalid credentials! Please try again...";
		Sleep(2000);
		system("cls");
		goto on;
	}
 }
	else {
        cout << "\n\t\tInvalid choice...";
        system("PAUSE");
		system("cls");
        goto op;
	}

  return 0;
   }
