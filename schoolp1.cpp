/*                   		*****************************
									COMPUTER SCIENCE PROJECT WORK
									*****************************

								PROGRAM FOR SCHOOL ADMISSION PROCESS


											---INTRODUCTION---


								  ////////////////////////////////

									  NAME: SOHAIB KHAN
									  CLASS: XII-B
									  BOARD ROLL NO: XXXXXXX
									  SCHOOL: NEW HORIZON SCHOOL


								  ////////////////////////////////

									administrator password: admin

											\-------------\
*********************************\  ADMISSION  \******************************************
											\-------------\
*/


//*******************************************************
// 		HEADER FILES USED IN THE PROJECT
//*******************************************************

#include<fstream>
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
//#define clrscr() system("cls");
#define pos -243								  // preprocessor directive to set file pointer in position

using namespace std;

//*******************************************************
//				FUNCTIONS DEFINITIONS
//*******************************************************

void MainMenu();
void Fee_Structure();						  // function to show fees
void Admn_With();								  // function to admission window
void Read_Criteria();						  // function to read admission criteria
char Check(int);								  // function to check guest user and non-registered user
void gotoxy(int, int);
void clrscr(char fill = ' ');

//*******************************************************
//				GLOBAL FUNCTIONS DEFINITIONS & VARIABLES
//*******************************************************

int v=0;                                 // login value, condition to enter in 'main' if user passes/not passes login
int regn=0;     								  // alloted registration number to a student
char temp[30]="NULL";						  // 'location' temporary variable
char temp2[30]="NULL";						  // 'location' temporary variable
char temp3[30]="NULL";                   // 'location' temporary variable
char temp4[30]="NULL";                   // 'location' temporary variable
char ch=0;
char r_user[10]="NULL";                  // username of currently logged user
char sym=17;
fstream adminStream;									  // admin stream
fstream fuser;  								  // user stream

//*******************************************************
//				CLASSES USED IN THE PROJECT
//*******************************************************

//-------------------------------------------------------
//     1.CUSTOMISATIN CLASS
//-------------------------------------------------------

class custom
{
	public:

	void Location(const char* x, int y)
	{
		if(y==1)
			strcpy(temp,x);
		else if(y==2)
			strcpy(temp2,x);
		else if(y==3)
			strcpy(temp3,x);
		else if(y==4)
			strcpy(temp4,x);

		if(y==1)
			cout << " " << temp << " >> ";
		if(y==2)
		{
			clrscr();
			cout << " " << temp << " >> " << temp2 << " >> ";
		}
		if(y==3)
		{
			clrscr();
			cout << " " << temp << " >> " << temp2 << " >> " << temp3 << " >> ";
		}
		if(y==4)
		{
			clrscr();
			cout << " " << temp << " >> " << temp2 << " >> " << temp3  << " >> " << temp4 << " >> ";
		}
		cout << "\n" << setfill('-') << setw(81) << endl;
	}

	void Copy_right()
	{
		char sym=169;
		gotoxy(62,22);
		cout << " Copyright " << sym << " 2014";
		gotoxy(60,23);
		cout << " New Horizon School";
		gotoxy(60,24);
		cout << " All Right Reserved";
	}

	void Intro()
	{
		gotoxy(25,5);
		cout << "| SCHOOL ADMISSION PROCESS |";
		gotoxy(25,4);
		cout << "----------------------------";
		gotoxy(25,6);
		cout << "----------------------------";
		gotoxy(2,17);
		cout << sym << " Made By : SOHAIB KHAN";
		gotoxy(2,18);
		cout << sym << " School  : NEW HORIZON SCHOOL";
		cout << endl;
	}
}C1;

//-------------------------------------------------------
//     2.USER CLASS
//-------------------------------------------------------

class user
{
	char username[10], password[10], name[30], father_name[30], mother_name[30], address[100], lang, mobile[10];
	int regs, Class, eng, math, sc, sst, lang_marks, per, stream_pref, stream, registered;

	public:

	void AssignUser_ID();					  // assigns username/password to a new user
	void Registration();						  // register a new user
	void Allot_Stream();						  // allot stream to a registered user
	void Del_Registration();				  // delete form of a registered user
	void Modify_Registration();			  // edit a form
	void Change_Stream();					  // change stream of a registered

	char *Get_Username()						  // accessor function to get username to verify account in mainmenu
	{
		return username;
	}
	char *Get_Password()						  // accessor function to get password to verify account in mainmenu
	{
		return password;
	}
	int Get_Stream()
	{
		return stream;
	}
	int Get_Regs()
	{
		return regs;
	}
	int Get_Per()
	{
		return per;
	}
	void Stream(int S)
	{
		stream=S;
	}
	int Get_Registered()
	{
		return registered;
	}

	char EnterUser_ID()
	{
		do
		{
			ch=0;
			clrscr();
			cout << "\n\n\n\n\t\t | Login";
			cout << "\n\t\t --------";
			cout << "\n\t\t " << sym << " Username: ";
			cout << "\n\t\t " << sym << " Password: ";
			gotoxy(0,18);
			cout << setfill('-') << setw(80) << endl;
			cout << "\t\t [3] ADMININSTRATOR LOGIN (Press '3')";
			cout << endl << setfill('-') << setw(81) << endl;
			gotoxy(16,8);
			cout << "\n\n\n\t\t " << sym << " Already have an account ? (y/n): ";
			ch=getche();
			getch();

			switch(ch)
			{
				case 'y': return 'y';            	      // return 'y' to mainmenu to verify account
				case 'n': do
							 {
                      	ch=0;
								gotoxy(18,12);
								cout << sym << " Want to register or login as guest ? (r/g): ";
								ch=getche();
								getch();

								if(ch=='r')
								{
									AssignUser_ID();           // assigns username/password to a new user
									return 'r';
								}
								else if(ch=='g')
								{
									v=1;                       // return 'v' as true login value
									return 'g';					   // return 'a' to welcome guest

								}
								else
								{
									ch=0;
									cout << "\a";
								}
							 }
							 while(ch!=27);
				case '3': return '3';							// return '3' to mainmenu to verify admin
				default : cout << "\a";
							 break;
			}
		}
		while(ch!=27);
		return '0';
	}

	void Display(int S)
	{
		cout << "\n\t Student Details";
		cout << "\n\t-----------------";
		cout << "\n\t   - Name: " << name;
		cout << "\n\t   - Registration No: " << regs;
		cout << "\n\t   - Percentage: " << per << "%";
		if(S==1)
		{
			cout << "\n\t   - Stream Allocated: ";
			if(stream==1)
				cout << "Science";
			else if(stream==2)
				cout << "Commerce";
			else if(stream==3)
				cout << "Arts";
		}
		else if(S==0)
		{
			cout << "\n\t   - Stream Applied: ";
			if(stream_pref==1)
				cout << "Science";
			else if(stream_pref==2)
				cout << "Commerce";
			else if(stream_pref==3)
				cout << "Arts";
		}
	}

	void Display()
	{
		cout << "\n\t Registration form";
		cout << "\n\t-------------------\n";
		cout << setfill('-') << setw(80) << endl;
		cout << "\t\t\t Registration Number: " <<  regs;
		cout << endl << setfill('-') << setw(80) << endl;
		cout << "\t   - Name: " << name;
		cout << "\n\t   - Class: " << Class;
		cout << "\n\t   - Father's Name: " << father_name;
		cout << "\n\t   - Mother's Name: " << mother_name;
		cout << "\n\t   - Address: " << address;
		cout << "\n\t   - Mobile: ";
		for(int i=0; i<10; i++)
			cout << mobile[i];
		cout << "\n\t   - Class 10 Marks";
		cout << "\n\t\t-English: " << eng;
		cout << "\n\t\t-Maths: " << math;
		cout << "\n\t\t-Science: " << sc;
		cout << "\n\t\t-SST: " << sst;
		cout << "\n\t\t-Language (";
		if(lang=='H')
			cout << "Hindi): ";
		else if(lang=='U')
			cout << "Urdu): ";
		else if(lang=='S')
			cout << "Sanskrit): ";
		cout << lang_marks;
		cout << "\n\t   - Percentage: " << per << "%";
		cout << "\n\t   - Stream Prefered: " << stream_pref;
		if(stream_pref==1)
			cout << " (Science)";
		else if(stream_pref==2)
			cout << " (Commerce)";
		else if(stream_pref==3)
			cout << " (Arts)";
		cout << "\n\t   - Stream Allocated: " << stream;
		if(stream==1)
			cout << " (Science)...";
		else if(stream==2)
			cout << " (Commerce)...";
		else if(stream==3)
			cout << " (Arts)...";
		else
			cout << " (No Stream)...";
	}
}U1;

//-------------------------------------------------------
//     3.ADMINISTRATOR CLASS
//-------------------------------------------------------

class admin
{
	char password[10];
	int sc_min, com_min, arts_min, seat_sc, seat_com, seat_arts, regn;

	public:

	admin();
	void Edit_Admn_Criteria();				  // edit admission criteria
	void Show_Admn_Criteria();				  // show admission criteria
	void Set_Seat(int, int);              // increase/decrease seat when a user fill a registration form
													  // and alloted a stream
	void Set_Regn();							  // automatic function which allots registration number
	int Get_sc_min()						  	  // accessor function to get science criteria to compare
	{
		return sc_min;
	}
	int Get_com_min()						  	  // accessor function to get commerce criteria to compare
	{
		return com_min;
	}
	int Get_arts_min()						  // accessor function to get arts criteria to compare
	{
		return arts_min;
	}
	int Get_seat_sc()						  	  // accessor function to get arts criteria to compare
	{
		return seat_sc;
	}
	int Get_seat_com()						  // accessor function to get arts criteria to compare
	{
		return seat_com;
	}
	int Get_seat_arts()						  // accessor function to get arts criteria to compare
	{
		return seat_arts;
	}
	int Get_regn()								  // accessor function to get registration number
	{
		return regn;
	}

	int Verify_Pass()							  // member function to verify administrator password
	{
		clrscr();
		int i=0, temp=0;
		char pass[10]="NULL";


		cout << "\n\n\n\n\t\t\t | Administrator Menu |";
		gotoxy(25,4);
		cout << "------------------------";
		gotoxy(25,6);
		cout << "------------------------";
		cout << "\n\n\n\t\t " << sym << " Enter Password: ";
		while(temp!=13)
		{
			temp=getch();
			if(temp==13)
			{
				pass[i++]='\0';
				break;
			}

			pass[i]=temp;
			cout << "*";
			i++;
		}
		Read_Criteria();
		return strcmp(pass,password);                   // returns 1 or 0 if admin verifies or not
	}

	void Admin_Menu()
	{
		clrscr();
		ch=0;
		char *u, *p;
		int i=1, loc=10;
		while(ch!='4')
		{
			clrscr();
			C1.Location("Administrator Menu",1);
			cout << "\n\n\t\t\t ADMINISTRATOR MENU";
			cout << "\n\t\t\t--------------------";

			cout << "\n\n\t\t 1. See all user";
			cout << "\n\t\t 2. Show addmission criteria";
			cout << "\n\t\t 3. Edit addmission criteria";
			cout << "\n\t\t 4. Log Out";
			cout << "\n\n\n\t\t\t " << sym << " Enter your choice: ";
			ch=getche();
			getch();

			switch(ch)
			{
				case '1': clrscr();
							 C1.Location("All Users",2);
							 fuser.open("User.bin", ios::in | ios::binary);
							 if(!fuser)
							 {
								cout << "\n\n\n\t\t\t >  No user is registered.";
								getch();
								Admin_Menu();
							 }
							 else
							 {
								 cout << "\n\n\t\t===============================================";
								 cout << "\n\t\t  U S E R N A M E     |       P A S S W O R D";
								 cout << "\n\t\t===============================================";
								 cout <<  endl << endl;

								 while(!fuser.eof())
								 {
									fuser.read((char*)&U1,sizeof(U1));
									if(fuser.eof())
										break;

									u=U1.Get_Username();
									p=U1.Get_Password();

									cout << "\t\t    " << i++ << ". " << u ;
									gotoxy(35,loc++);
									cout << " ------------> \t" << p << endl;
								 }
								 fuser.close();

								 cout << "\n\n\t\t\t\t > Press any key...";
								 getch();
								 Admin_Menu();
							 }
							 break;
				case '2': C1.Location("Admission Criteria", 2);
							 Read_Criteria();
							 Show_Admn_Criteria();
							 cout << "\n\n\n\t\t\t > Press any key...";
							 getch();
							 Admin_Menu();
							 break;
				case '3': Edit_Admn_Criteria();
							 break;
				case '4': cout << "\n\n\t\t > You have successfully logged out.";
							 cout << "\a";
							 exit(0);
							 break;
				default : cout << "\a";
							 break;
			}
		}
	}
}A1;

//*******************************************************
//				MEMBER FUNCTIONS OF ABOVE DEFINED CLASS
//*******************************************************

admin :: admin()          					  // constructor which sets admission criteria
{
	adminStream.open("Admin.bin", ios::in | ios::binary);

	//file.open("Admin.bin", ios::out | ios::binary | ios::noreplace);
	if(!adminStream)
	{
	    adminStream.close();
	    adminStream.open("Admin.bin", ios::out | ios::binary);
		strcpy(password,"admin"); 			     // constructor which automatically assigns
														  // password to administrator menu
		A1.sc_min=90, A1.com_min=75, A1.arts_min=65, A1.seat_sc=35, A1.seat_com=45, A1.seat_arts=59, A1.regn=1000;
		adminStream.write((char*)&A1, sizeof(A1));
		adminStream.close();
	}
}

void admin :: Show_Admn_Criteria()
{
	cout << "\n\n\t\t Present Admission Criteria";
	cout << "\n\t\t----------------------------";
	cout << "\n\n\t > Marks required for SCIENCE stream(in percentage): " << A1.sc_min;
	cout << "\n\t > No. of Seats for SCIENCE stream: " << A1.seat_sc;
	cout << "\n\n\t > Marks required for COMMERCE stream(in percentage): " << A1.com_min;
	cout << "\n\t > No. of Seats for COMMERCE stream: " << A1.seat_com;
	cout << "\n\n\t > Marks required for ARTS stream(in percentage):" << A1.arts_min;
	cout << "\n\t > No. of Seats for ARTS stream: " << A1.seat_arts;
}

void admin :: Edit_Admn_Criteria()
{
	C1.Location("Edit Admission Criteria",2);
	Read_Criteria();

	cout << "\n\n\t Edit Admission Criteria";
	cout << "\n\t-------------------------";

	Show_Admn_Criteria();
	cout << "\n" << setfill('-') << setw(81) << endl;

	cout << "\t " << sym << " Enter the required marks for SCIENCE stream(in percentage): ";
	cin >> sc_min;
	cout << "\t " << sym << " Enter No. of Seats for SCIENCE stream: ";
	cin >> seat_sc;
	cout << "\n\t " << sym << " Enter the required marks for COMMERCE stream(in percentage): ";
	cin >> com_min;
	cout << "\t " << sym << " Enter No. of Seats for COMMERCE stream: ";
	cin >> seat_com;
	cout << "\n\t " << sym << " Enter the required marks for ARTS stream(in percentage)";
	cin >> arts_min;
	cout << "\t " << sym << " Enter No. of Seats for ARTS stream: ";
	cin >> seat_arts;

	adminStream.open("Admin.bin", ios::out | ios::binary);
	adminStream.write((char*)&A1, sizeof(A1));
	adminStream.close();

	cout << "\n\n\t\t > Records updated.";
	cout << "\n\t\t > Press any key...";
	getch();
}

void admin :: Set_Regn()
{
	Read_Criteria();
	adminStream.open("Admin.bin", ios::out | ios::binary);
	A1.regn+=1;
	adminStream.write((char*)&A1,sizeof(A1));
	adminStream.close();
}

void admin :: Set_Seat(int i, int j)
{
	switch(i)
	{
		case 1: Read_Criteria();
				  adminStream.open("Admin.bin", ios::out | ios::binary);
				  if(j==0)
					A1.seat_sc-=1;
				  else if(j==1)
					A1.seat_sc+=1;
				  adminStream.write((char*)&A1,sizeof(A1));
				  adminStream.close();
				  break;
		case 2: Read_Criteria();
				  adminStream.open("Admin.bin", ios::out | ios::binary);
				  if(j==0)
					A1.seat_com-=1;
				  else if(j==1)
					A1.seat_com+=1;
				  adminStream.write((char*)&A1,sizeof(A1));
				  adminStream.close();
				  break;
		case 3: Read_Criteria();
				  adminStream.open("Admin.bin", ios::out | ios::binary);
				  if(j==0)
					A1.seat_arts-=1;
				  else if(j==1)
					A1.seat_arts+=1;
				  adminStream.write((char*)&A1,sizeof(A1));
				  adminStream.close();
				  break;
	}
}

void user :: AssignUser_ID()   			  // member function of class 'user'.
{                                        // defined here as to use 'object' of
	clrscr();
	ch=0;
	user U2;
	int i=0;
	char pass[10], temp='0', user[10];

	fuser.open("User.bin",ios::in | ios::out | ios::binary);

	cout << "\n\n\n\n\t\t | Register Your Account";
	cout << "\n\t\t -----------------------";
	cout << "\n\t\t | Username (1-10 char) : ";
	cout << "\n\t\t | Password (1-10 char) : ";
	cout << "\n\t\t | Confirm Password     : ";

	gotoxy(44,7);
	user:
	cin.getline(user,10);
	if(strcmp(user,"")==0)
	{
		gotoxy(44,7);
		goto user;
	}

	while(!fuser.eof())
	{
		fuser.read((char*)&U1,sizeof(U1));
		if(fuser.eof())
			break;

		if((strcmp(U1.username,user)==0))
		{
			cout << "\n\n\n\t   > Someone already has that username. Try another ?";
			gotoxy(44,7);
			cout << "           ";
			gotoxy(44,7);
			gets(user);
			fuser.seekp(0);					  // to reset pointer to initial position
		}											  // so to read same mistake again

	}
	strcpy(U2.username,user);
	fuser.close();
	gotoxy(11,10);
	cout << "\n" << setfill(' ') << setw(80) << endl;
	do
	{
		temp='0';
		i=0;
		gotoxy(44,8);
		cout << setfill(' ') << setw(10) << endl;
		gotoxy(44,8);

		while(temp!=13)
		{
			temp=getch();
			if(temp==13)
			{
				U2.password[i++]='\0';
				break;
			}

			U2.password[i]=temp;
			cout << "*";
			i++;
		}

		temp='0';
		i=0;
		gotoxy(44,9);

		while(temp!=13)
		{
			temp=getch();
			if(temp==13)
			{
				pass[i++]='\0';
				break;
			}

			pass[i]=temp;
			cout << "*";
			i++;
		}
		if(strcmp(pass,U2.password)!=0)
		{
			cout << "\n\n\t\t\t > Passwords Do not match";
			gotoxy(44,9);
			cout << setfill(' ') << setw(10) << endl;
			ch='y';
		}
		else
			ch='n';
	}
	while(ch=='y');
	strcpy(r_user,U2.username);
	U2.registered=0;
	U2.eng=0;
	U2.math=0;
	U2.sc=0;
	U2.sst=0;
	U2.lang_marks=0;
	fuser.open("User.bin",	ios::out | ios::app | ios::binary);
	fuser.write((char*)&U2,sizeof(U2));
	fuser.close();
}

void user :: Registration()
{
	clrscr();
	ch=0;
	int str;
	char ch2='N';
	user U2;
	C1.Location("Registration",3);
	cout << "\n\n\t  Registration";
	cout << "\n\t --------------";

	cout << "\n\n\t >  Do you want apply for admission in class XI ?(y/n): ";
	cin >> ch;
	if(ch=='y')
	{
		cout << "\n\n\t\t=================STREAM PREFERED===============";
		cout << "\n\t\t\t [1] for SCIENCE";
		cout << "\n\t\t\t [2] for COMMERCE";
		cout << "\n\t\t\t [3] for ARTS ";
		cout << "\n\t\t================================================";
		cout << "\n\n\t\t   " << sym << " Enter Your choice: ";
		cin >> str;

		Read_Criteria();
		switch(str)
		{
			case 1: if(A1.Get_seat_sc()==0)
					  {
							cout << "\n\t\t   > Seats full in science stream.";
							getch();
							return;
					  }
					  break;
			case 2: if(A1.Get_seat_com()==0)
					  {
							cout << "\n\t\t   > Seats full in commerce stream.";
							getch();
							return;
					  }
					  break;
			case 3: if(A1.Get_seat_arts()==0)
					  {
							cout << "\n\t\t   > Seats full in arts stream.";
								getch();
							return;
					  }
					  break;
		}
		Read_Criteria();
		if(A1.Get_regn()==1000)
		{
			regn=1000;
			A1.Set_Regn();
		}
		else
		{
			regn=A1.Get_regn();
			A1.Set_Regn();
		}

		fuser.open("User.bin", ios::in | ios::out | ios::binary);
		while(!fuser.eof())
		{
			fuser.read((char*)&U2,sizeof(U2));
			if(fuser.eof())
				break;

			if(strcmp(U2.username,r_user)==0)
				break;
		}
		U2.stream_pref=str;
		U2.stream=0;
		U2.Class = 11;

		do
		{
			clrscr();
			C1.Location("Registration",3);

			cout << "\n\n\t > Enter Name of Student: ";
			cout << "\n\t > Enter father's name of Student: ";
			cout << "\n\t > Enter mother's name of Student: ";
			cout << "\n\t > Enter address of the Student: ";
			cout << "\n\t > Enter mobile number: ";
			cout << "\n\n\t    -Enter your class 10 marks..";
			cout << "\n\t > Enter marks in English: ";
			cout << "\n\t > Enter marks in Math: ";
			cout << "\n\t > Enter marks in Science: ";
			cout << "\n\t > Enter marks in SST: ";
			cout << "\n\t > Enter language(Hindi(H)/Urdu(U)/Sanskrit(S)): ";
			cout << "\n\t > Enter marks in language: ";
			gotoxy(35,6);
			gets(U2.name);
			gotoxy(44,7);
			gets(U2.father_name);
			gotoxy(44,8);
			gets(U2.mother_name);
			gotoxy(42,9);
			gets(U2.address);
			gotoxy(33,10);
			for(int i=0; i<10; i++)
			{
				U2.mobile[i]=getche();
			}
			getch();
			gotoxy(36,13);
			cin >> U2.eng;
			gotoxy(33,14);
			cin >> U2.math;
			gotoxy(36,15);
			cin >> U2.sc;
			gotoxy(32,16);
			cin >> U2.sst;
			gotoxy(58,17);
			cin >> U2.lang;
			gotoxy(37,18);
			cin >> U2.lang_marks;

			cout << "\n\n\t > You cannot edit some of the details after this.";
			cout << "\n\t > Do you want to continue or re-fill the application form ?(y/n): ";
			cin >> ch2;
		}
		while(toupper(ch2)=='N');


		U2.per = (U2.eng+U2.math+U2.sc+U2.sst+U2.lang_marks)/5;
		U2.registered=1;

		cout << endl << endl << setfill('=') << setw(80) << endl;
		cout << "\t\t     REGISTRATION SUCCESSFUL";
		U2.regs=regn;
		cout << "\n\t\t   > Your registration no: " << regn;
		cout << endl << setfill('=') << setw(80) << endl;

		fuser.seekp(pos,ios::cur);
		fuser.write((char*)&U2,sizeof(U2));
		fuser.close();

		cout << "\n\t\t   > Registration Successful.";
		cout << "\n\t\t   > Go back and select your stream.";
		cout << "\n\t\t   > Press an key...";
		getch();
	}
}

void user :: Allot_Stream()
{
	user U2;
	ch='Y';
	char choice='0';
	int done=0;
	C1.Location("Allot Stream",3);

	cout << "\n\n\t Allotement of stream";
	cout << "\n\t----------------------";

	fuser.open("User.bin", ios::in | ios::out | ios::binary);
	while(!fuser.eof())
	{
		fuser.read((char*)&U2,sizeof(U2));
		if(fuser.eof())
			break;

		if(strcmp(U2.username,r_user)==0)
		{
			if(U2.stream==1 || U2.stream==2 || U2.stream==3)
			{
				U2.Display(1);
				done=1;
				break;

			}
			break;
		}
	}
	if(done==1)
	{
		fuser.close();
		cout << "\n\n\t\t > Press any key...";
		getch();
		return;
	}
	U2.Display(0);
	Read_Criteria();

	if(U2.per<A1.Get_arts_min())
	{
		cout << "\n\n\t > Not eligible for any streams,";
		fuser.close();
		cout << "\n\t > Do you want to delete your registration ?(y/n): ";
		cin >> choice;
		if(toupper(choice)=='Y')
			U1.Del_Registration();
		cout << "\n\t\t > Press any key...";
		getch();
		return;
	}

	while(toupper(ch)=='Y')
	{
		switch(U2.stream_pref)
		{
			case 1:	if(U2.per>=A1.Get_sc_min())
						{
							cout << "\n\n\t > Stream allocation done.";
							cout << "\n\t > Stream allocated: Science";
							A1.Set_Seat(1,0);
							U2.stream=U2.stream_pref;
							fuser.seekp(pos,ios::cur);
							fuser.write((char*)&U2,sizeof(U2));
							fuser.close();
							getch();
							ch='N';
							break;
						}
						else
						{
							cout << "\n\n\t > Not eligible for science stream.";
							cout << "\n\t > Do you want to try for commerce stream ?(y/n): ";
							cin >> ch;
							if(toupper(ch)=='Y')
							{
								U2.stream_pref=2;
								break;
							}
							else
							{
								fuser.close();
								cout << "\n\t > Do you want to delete your registration ?(y/n): ";
								cin >> choice;
								if(toupper(choice)=='Y')
									U1.Del_Registration();
								ch='N';
								break;
							}
						}
			case 2:	if(U2.per>=A1.Get_com_min())
						{
							cout << "\n\n\t > Stream allocation done.";
							cout << "\n\t > Stream allocated: Commerce";
							A1.Set_Seat(2,0);
							U2.stream = U2.stream_pref;
							fuser.seekp(pos,ios::cur);
							fuser.write((char*)&U2,sizeof(U2));
							fuser.close();
							getch();
							ch='N';
							break;
						}
						else
						{
							cout << "\n\n\t > Not eligible for commerce stream.";
							cout << "\n\t > Do you want to try for arts stream ?(y/n): ";
							cin >> ch;
							if(toupper(ch)=='Y')
							{
								U2.stream_pref=3;
								break;
							}
							else
							{
								fuser.close();
								cout << "\n\t > Do you want to delete your registration ?(y/n): ";
								cin >> choice;
								if(toupper(choice)=='Y')
									U1.Del_Registration();
								ch='N';
								break;
							}
						}
			case 3:	if(U2.per>=A1.Get_arts_min())
						{
							cout << "\n\n\t > Stream allocation done.";
							cout << "\n\t > Stream allocated: Arts";
							A1.Set_Seat(3,0);
							U2.stream=U2.stream_pref;
							fuser.seekp(pos,ios::cur);
							fuser.write((char*)&U2,sizeof(U2));
							fuser.close();
							getch();
							ch='N';
							break;
						}
						else
						{
							cout << "\n\n\t > Not eligible for arts stream.";
							fuser.close();
							cout << "\n\t > Do you want to delete your registration ?(y/n): ";
							cin >> choice;
							if(toupper(choice)=='Y')
								U1.Del_Registration();
							ch='N';
							break;
						}
		}
	}
	cout << "\n\n\t\t > Press any key...";
	getch();
}

void user :: Modify_Registration()
{
	clrscr();
	ch=0;
	char temp[100];
	user U2;
	C1.Location("Edit Registration Form",3);
	cout << "\t Edit Registration Form";
	cout << "\n\t------------------------";

	cout << "\n\n\t\t  > Do you want to modify your records ?(y/n): ";
	cin >> ch;

	if(toupper(ch)=='N')
		return;

	else
	{
		fuser.open("User.bin", ios::in | ios::out | ios::binary);
		while(!fuser.eof())
		{
			fuser.read((char*)&U2,sizeof(U2));
			if(fuser.eof())
				break;
			if(strcmp(U2.Get_Username(),r_user)==0)
				break;
		}
		do
		{
			clrscr();
			C1.Location("Edit Registration Form",3);
			cout << "\t Edit Registration Form";
			cout << "\n\t------------------------";
			U2.Display();

			cout << "\n" << setfill('-') << setw(80) << endl;
			cout << "\t > Enter your modified details. Press ( . ) to retain previous details.";
			cout << endl;
			cout << "\n\t > Enter father's name of Student: ";
			gets(temp);
			if(strcmp(temp,".")!=0)
				strcpy(U2.father_name,temp);
			cout << "\t > Enter mother's name of Student: ";
			gets(temp);
			if(strcmp(temp,".")!=0)
				strcpy(U2.mother_name,temp);
			cout << "\t > Enter address of the Student: ";
			gets(temp);
			if(strcmp(temp,".")!=0)
				strcpy(U2.address,temp);
			cout << "\t > Enter mobile number: ";
			for(int i=0; i<10; i++)
			{
				U2.mobile[i]=getche();
			}
			getch();
			cout << "\n\t    -Enter your class 10 marks..";
			cout << "\n\t > Enter marks in English: ";
			cin >> U2.eng;
			cout << "\t > Enter marks in Math: ";
			cin >> U2.math;
			cout << "\t > Enter marks in Science: ";
			cin >> U2.sc;
			cout << "\t > Enter marks in SST: ";
			cin >> U2.sst;
			cout << "\t > Enter language(Hindi(H)/Urdu(U)/Sanskrit(S)): ";
			cin >> U2.lang;
			cout << "\t > Enter marks in language: ";
			cin >> U2.lang_marks;

			cout << "\n\t > Do you want to continue or re-edit the application form ?(y/n): ";
			cin >> ch;
		}
		while(toupper(ch)=='N');
		U2.per = (U2.eng+U2.math+U2.sc+U2.sst+U2.lang_marks)/5;

		fuser.seekp(pos,ios::cur);
		fuser.write((char*)&U2,sizeof(U2));
		fuser.close();
		cout << "\n\t " << sym << " Editing Done...";
		getch();
	}
}

void user :: Change_Stream()
{
	ch=0;
	int found=0, newstream=0, i;
	user U2;
	clrscr();
	C1.Location("Change Stream",3);
	cout << "\n\t Change Your Stream";
	cout << "\n\t--------------------";

	cout << "\n\n\t > Are you sure you want to change your stream ?(y/n): ";
	cin >> ch;
	if(toupper(ch)=='N')
		return;
	else
	{
		fuser.open("User.bin", ios::in | ios::out | ios::binary);
		while(!fuser.eof())
		{
			fuser.read((char*)&U2,sizeof(U2));
			if(fuser.eof())
				break;

			if(strcmp(U2.username,r_user)==0)
			{
				if(U2.stream==0)
				{
					cout << "\n\t > You have not alloted any stream or you are not";
					cout << "\n\t   eligible for admission.";
					getch();
					found=1;
					break;
				}
				break;
			}
		}
		if(found==1)
		{
			fuser.close();
			return;
		}
		else
		{
			Read_Criteria();
			U2.Display(1);
			i=U2.stream;
			cout << "\n\n\t > Select your new stream.";
			cout << "\n\t\t================================================";
			cout << "\n\t\t\t [1] for SCIENCE";
			cout << "\n\t\t\t [2] for COMMERCE";
			cout << "\n\t\t\t [3] for ARTS ";
			cout << "\n\t\t================================================";
			cout << "\n\t > Enter a new stream according to your percentage: ";
			cin >> newstream;

			if(newstream==U2.stream)
			{
				cout << "\n\t > You already have this stream.";
				getch();
				fuser.close();
				ch='n';
			}

			while(toupper(ch)=='Y')
			{
				switch(newstream)
				{
					case 1: if(U2.per>=A1.Get_sc_min())
							  {
								cout << "\n\t > You are eligible.";
								cout << "\n\t > Stream allocation done.";
								cout << "\n\t > Stream allocated: Science";
								A1.Set_Seat(i,1);
								A1.Set_Seat(1,0);
								U2.stream=newstream;
								U2.stream_pref=newstream;
								fuser.seekp(pos,ios::cur);
								fuser.write((char*)&U2,sizeof(U2));
								fuser.close();
								getch();
								ch='N';
								break;
							  }
							  else
							  {
								cout << "\n\t > Not eligible for science stream.";
								ch='N';
								fuser.close();
								break;
							  }
					case 2: if(U2.per>=A1.Get_com_min())
							  {
								cout << "\n\t > You are eligible.";
								cout << "\n\t > Stream allocation done.";
								cout << "\n\t > Stream allocated: Commerce";
								A1.Set_Seat(i,1);
								A1.Set_Seat(2,0);
								U2.stream = newstream;
								U2.stream_pref=newstream;
								fuser.seekp(pos,ios::cur);
								fuser.write((char*)&U2,sizeof(U2));
								fuser.close();
								getch();
								ch='N';
								break;
							  }
							  else
							  {
								cout << "\n\t > Not eligible for commerce stream.";
								ch='N';
								fuser.close();
								break;
							  }
					case 3: if(U2.per>=A1.Get_arts_min())
							  {
								cout << "\n\t > You are eligible.";
								cout << "\n\t > Stream allocation done.";
								cout << "\n\t > Stream allocated: Arts";
								A1.Set_Seat(i,1);
								A1.Set_Seat(3,0);
								U2.stream=newstream;
								U2.stream_pref=newstream;
								fuser.seekp(pos,ios::cur);
								fuser.write((char*)&U2,sizeof(U2));
								fuser.close();
								getch();
								ch='N';
								break;
							  }
							  else
							  {
								cout << "\n\t > Not eligible for arts stream.";
								fuser.close();
								ch='N';
								break;
							  }
				}
			}
		}
	}
	cout << "\n\n\t\t > Press any key...";
	getch();
}

void user :: Del_Registration()
{
	user U3;
	fuser.open("User.bin", ios::in | ios::out | ios::binary);
	while(!fuser.eof())
	{
		fuser.read((char*)&U1,sizeof(U1));
		if(fuser.eof())
			break;

		if(strcmp(U1.username,r_user)==0)
		{
			strcpy(U3.username,U1.username);
			strcpy(U3.password,U1.password);
			U3.registered=0;
			fuser.seekp(pos,ios::cur);
			fuser.write((char*)&U3,sizeof(U3));
			break;
		}
	}
	fuser.close();
}


//*******************************************************
//				FUNCTIONS USED IN THE PROJECT
//*******************************************************

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void clrscr(char fill) {
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

void Read_Criteria()
{
	adminStream.open("Admin.bin",ios::in | ios::binary);
	adminStream.read((char*)&A1,sizeof(A1));
	adminStream.close();
}

void Fee_Structure()
{
	clrscr();
	C1.Location("Fee Structure",2);

	cout << "\t  -> Fee can be deposited monthly/quaterly through cash/cheque";
	cout << "\n\t\t------------------------------------------------";
	cout << "\n\t\t Quarterly Fee For the Academic Session 2014-15";
	cout << "\n\t\t------------------------------------------------\n\n";

	cout << "   ==========================================================================\n";
	cout << "     Level |" <<  " Admission Fees |" <<" Annual Charges |" << " Tuition Fees |" << " Other |" << " Total \n";
	cout << "   ==========================================================================\n";
	cout << "   LKG/UKG       4000             1000            5000        1500    11500\n\n";
	cout << "   I-V           5000             1500            5600        1600    13700\n\n";
	cout << "   VI-VII        5000             1500            6000        1800    14300\n\n";
	cout << "   IX & X        5500             1800            6500        1800    15600\n\n";
	cout << "   XI & XII      5500             2000            8000        2000    17500\n\n";
	cout << setfill('-') << setw(80) << endl;
	cout << "\t > Registration Fees: Rs.250";
	cout << "\n\t > Press any key to go Mainmenu...";
	getch();
}

void Important_Dates()
{
	clrscr();
	C1.Location("Important Dates",2);
	cout << "\n\t 2014-2015 Important Dates";
	cout << "\n\t---------------------------";

	cout << "\n\n\t 1/1/14  - Start of online Registration and generation of";
	cout << "\n\t\t   New Registration No.";
	cout << "\n\t 31/1/14 - Last date for submitting online application form";
	cout << "\n\t 31/1/14 - Last date for correction in the application form";
	cout << "\n\t 31/1/14 - Last date for changing of stream";
	cout << "\n\t 1/2/14  - Payment of registration fees to school through cash/cheque";
	cout << "\n\t 10/2/14 - Last date of Payment of registration fees";
	cout << "\n\t\t   If any applicant has not paid the registration fee";
	cout << "\n\t\t   his registration will be cancelled";
	cout << "\n\t 11/2/14 - Admission test date alloted";
	cout << "\n\t 25/4/12 - First day of Admission test";
	cout << "\n\t 15/5/12 - Last date of admission test";
	cout << "\n\t 25/5/12 - Display of list of selected student";
	cout << "\n\t\t   Selected student can now pay school fee at school";
	cout << "\n\t\t   through cash/cheque";
	cout << "\n\t 1/7/12  - Start of New Session 2014 - 2015 ...";
}

void Admn_With()
{
	ch=0;
	clrscr();
	while(ch!='8')
	{
		ch=0;
		int i;
		char found='n';
		C1.Location("Admission/Withdrawal",2);
		cout << "\n\t  Admission/Withdrawal";
		cout << "\n\t ----------------------";
		cout << endl << endl << setfill('-') << setw(80) << endl;
		for(i=0;i<11;i++)
			cout << sym;
		cout << " 01. Registration (XI - SCIENCE/COMMERCE/ARTS) ";
		for(i=0;i<21;i++)
			cout << sym;
		cout << endl << setfill('-') << setw(80) << endl;
		cout << "\n\t    02. Allotment of Stream (for registered member only)";
		cout << "\n\t    03. View Registration Form (for registered member only)";
		cout << "\n\t    04. Edit Registration Form (for registered member only)";
		cout << "\n\t    05. Delete Registration";
		cout << "\n\t    06. Change Stream (for registered member only)";
		cout << "\n\t    07. Display Criteria for selection";
		cout << "\n\t    08. Back to Main Menu";

		cout << "\n\n\t " << sym << " Enter your choice: ";
		ch=getche();
		getch();

		switch(ch)
		{
			case '1': C1.Location("Registration",3);
						 cout << "\n\n\t  Registration";
						 cout << "\n\t --------------";
						 found=Check(1);
						 if(found=='y')
							U1.Registration();
						 break;
			case '2': C1.Location("Allot Stream",3);
						 cout << "\n\n\t Allotement of stream";
						 cout << "\n\t----------------------";
						 found=Check(2);
						 if(found=='y')
							U1.Allot_Stream();
						 break;
			case '3': clrscr();
						 C1.Location("View Registration Form",3);
						 found=Check(2);
						 if(found=='y')
						 { user U2;
							fuser.open("User.bin", ios::in | ios::binary);
							while(!fuser.eof())
							{
								fuser.read((char*)&U2,sizeof(U2));
								if(fuser.eof())
									break;
								if(strcmp(U2.Get_Username(),r_user)==0)
									break;
							}
							U2.Display();
							fuser.close();
							getch();
						 }
						 break;
			case '4': clrscr();
						 C1.Location("Edit Registration Form",3);
						 cout << "\n\n\t Edit Registration Form";
						 cout << "\n\t-------------------------";
						 found=Check(2);
						 if(found=='y')
							U1.Modify_Registration();
						 break;
			case '5': clrscr();
						 C1.Location("Delete Registration",3);
						 cout << "\n\n\t Delete Your Registration";
						 cout << "\n\t----------------------------";
						 found=Check(2);
						 if(found=='y')
						 {
							char t;
							cout << "\n\n\t > Are you sure you want to delete you registration ?(y/n): ";
							cin >> t;
							if(t=='y')
							{
								U1.Del_Registration();
								cout << "\n\t > Registration successfully deleted.";
								getch();
								  break;
							}
							else
								break;
						 }
						 break;
			case '6': clrscr();
						 C1.Location("Change Stream",3);
						 cout << "\n\t Change Your Stream";
						 cout << "\n\t-------------------";
						 found=Check(2);
						 if(found=='y')
							U1.Change_Stream();
						 break;
			case '7': clrscr();
						 C1.Location("Admission Criteria",3);
						 Read_Criteria();
						 A1.Show_Admn_Criteria();
						 cout << "\n\n\n\t\t   > Press an key...";
						 getch();
						 break;
			case '8': break;
			default : cout << "\a";
						 break;
		}
	}
}

char Check(int i)
{
	if(strcmp(r_user,"NULL")==0)
	{
		cout << "\n\n\t\t > You must login yourself for registration.";
		getch();
		return 'n';
	}
	else
	{
		user U2;
		fuser.open("User.bin", ios::in | ios::binary);
		while(!fuser.eof())
		{
			fuser.read((char*)&U2,sizeof(U2));
			if(fuser.eof())
				break;

			if(strcmp(U2.Get_Username(),r_user)==0)
			{
				switch(i)
				{
					case 1: if(U2.Get_Registered()==1)
								 {
									cout << "\n\n\t > You have already filled the registration form.";
									cout << "\n\t > You  can now edit or delete your registration form.";
									getch();
									fuser.close();
									return 'n';
								 }
								 else
								 {
									fuser.close();
									return 'y';
								 }
					case 2: if(U2.Get_Registered()==0)
								 {
									cout << "\n\n\t\t > You must first fill registration form.";
									getch();
									fuser.close();
									return 'n';
								 }
								 else
								 {
									fuser.close();
									return 'y';
								 }
				}
				break;
			}
		}
	}
}

//*******************************************************
//				 	 		MAINMENU
//*******************************************************

void MainMenu()
{
	clrscr();
	C1.Intro();
	C1.Copy_right();
	gotoxy(38,7);
	getch();
	clrscr();

	start3:  									  // to restart login
	char username[10], password[10], retrn, *t, *u, temp='0';
	int i=0,m, opt=0;
	ch=0;

	retrn=U1.EnterUser_ID();              // to select user
	if(retrn=='r')								  // to register account
	{
		cout << "\n\n\t\t\t > Registration Successful.";
		v=1;
	}
	else if(retrn=='y')    					  // to verify account
	{
		fuser.open("User.bin",ios::in | ios::binary);
		if(!fuser)
		{
			cout << "\n\n\n\t\t > No user is registered." << "\n\t\t > Create an account to login.";
			getch();

			U1.AssignUser_ID();
			cout << "\n\n\t\t\t > Registration Successful.";
			v=1;
		}
		else
		{
			gotoxy(30,7);
			gets(username);

			gotoxy(30,8);
			while(temp!=13)
			{
				temp=getch();
				if(temp==13)
				{
					password[i++]='\0';
					break;
				}

				password[i]=temp;
				cout << "*";
				i++;
			}
			temp=0;

			while(!fuser.eof())
			{
				fuser.read((char*)&U1,sizeof(U1));
				if(fuser.eof())
					break;

				t=U1.Get_Username();

				if((strcmp(t,username)==0))
				{
					u=U1.Get_Password();
					if(strcmp(u,password)==0)
					{
						gotoxy(40,7);
						cout << "\t\t > Verified Successfully.";
						strcpy(r_user,username);
						opt=0;
						v=1;
						break;
					}
					else
						opt=1;
				}
				else
					opt=1;
			}
			fuser.close();

			if(opt==1)
			{
				cout << "\n\t\t\t\t\t > Incorrect Account/Password.";
				gotoxy(42,12);
				cout << "\n\t\t\t\t\t > Want to retry ? (y/n): ";
				cin >> retrn;
				if(retrn=='y')
					goto start3;
				else
					exit(0);

			}
		}
	}

	else if(retrn=='3')                   // to login as admin
	{

		m=A1.Verify_Pass();                // administrator password verification
		if(m==0)
		{
			cout << "\n\n\n\t\t " << sym << " Admin verified.";
			getch();
			A1.Admin_Menu();
		}
		else
		{
			cout << "\n\n\n\t => You do not have the authority to make any changes.";
			getch();
			MainMenu();
		}
	}

	if(v==1)                    			  // if user has account or has a guest account
	{												  // then able to access 'main'
		getch();
		clrscr();

		while(ch!='4')
		{
			ch=0;
			clrscr();
			C1.Location("Main",1);

			if(retrn=='g')
				cout<<"\t\t\t\t\t\t  " << "  Welcome 'Guest' !!!";
			else
				cout<<"\t\t\t\t\t\t\t" << "Welcome '" << r_user << "' !!!" ;

			cout << "\n\t\t\t A D M I S S I O N";
			cout << "\n\t\t\t-------------------";
			cout << "\n\n\t\t\t\t\t\t ACADEMIC SESSION 2014-2015" << endl << endl;
			cout << "\n\t 01. Admission/Withdrawal";
//			cout << "\n\t 02. Test & Interviews";
			cout << "\n\t 02. Important Dates";
			cout << "\n\t 03. Fee Structure";
//			cout << "\n\t 05. Financial Aid Information";
//			cout << "\n\t 06. Termination";
			if(retrn!='g')
				cout << "\n\t 04. Logout";
			else if(retrn=='g')
				cout << "\n\t 04. Exit";
			cout << "\n\n\t " << sym << " Enter your choice: ";
			ch=getche();

			switch(ch)
			{
				case '1': getch();
							 clrscr();
							 Admn_With();
							 break;
				case '2': getch();
							 clrscr();
							 Important_Dates();
							 getch();
							 break;
				case '3': getch();
							 clrscr();
							 Fee_Structure();
							 break;
				case '4': getch();
							 if(retrn!='g')
							 {
								cout << "\n\t > Are you sure ?(y/n): ";
								 ch=getche();
								 getch();
								 if(ch == 'y')
								 {
									cout << "\n\t > Sucessfully logged out.";
									cout << "\a";
									exit(0);
								 }
							 }
							 else if(retrn=='g')
							 {
								cout << "\a";
								exit(0);
							 }
				default : cout << "\a";
							 break;
			}
			ch=0;
		}
	}
	else
		cout << "\n\n\t\t > Unusual behaviour detected. You are an ALIEN.";
	getch();
	MainMenu();
}

//*******************************************************
// 	 		MAIN FUNCTION OF THE PROGRAM
//*******************************************************
int main()
{
	MainMenu();
	return 0;
}
