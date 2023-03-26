/* 
Task:
User inputs the name of a book to a Library management system.
Each book has number of pages, author name, date of release,
due date, and name of person who has it.
The program should allow the user to input a new book with its details,
and recognize if a book has been previously inputted.
If today’s date is past the due date, the person is fined 5 EUR


Additional comments:
*In recent tests, the script worked without errors
*Possible to use other libraries on Windows
*Lines 40, 356, 458, 474 need to replace the path 
*/
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
#include <dirent.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>



using namespace std;


//creating class to facilitate access to certain functions
class BookActions{
private:
string permanent_path = "/home/user_name/Desktop/Task_from_collegue/Books_Data.txt";//file to store passwords

    char c;//get file data
    bool check_l;//true value checker
char response;// [Y/n]
double difference;//dates difference
public:

void FileToBookData()//file creation on first start-up
{ 
fstream file_programm;

 file_programm.open(permanent_path.c_str(), ios::out );
if(file_programm.is_open())
  {
   cout<< " File for book data created successfully"  << endl; 
  }else{
      cout << "Error!";
  }
 file_programm.close();

}
//-----------------------------------------------------
//Display passwords from file
void DisplayData(){

ifstream file_display;
   string content;
  int sday, smonth, syear;
   int i;
    file_display.open(permanent_path.c_str(), fstream::in);
    if(!file_display.is_open())//file closed
    {
        cout<<"\nError Occurred! ";
       
    }
    
   else{ //file opened
    while( getline (file_display,content))//till the end
    {
   
    cout << content << endl;
 
              

              if (content.find("Due date - [") != string::npos ){//find file content due date
                  
               int s = content.length();
               char rplc[s+1];
               strcpy(rplc, content.c_str());
               //get day from file
               sday=((int)rplc[13]-48)*10 +((int)rplc[14]-48);
               
               //get month from file
               smonth=((int)rplc[16]-48)*10 +((int)rplc[17]-48);

               //get year from file
               syear=((int)rplc[19]-48)*1000 +((int)rplc[20]-48)*100+((int)rplc[21]-48)*10 +((int)rplc[21]-48);
               
               for (i=1; i<2; i++ ){
              getline(file_display,content);
             }
               timeChecking(sday, smonth, syear);//compare due and current date
            if(difference<0)//if due date has been over
            {
              difference=difference*(-1);//reverse to normal looking form
              cout << endl << "The date of possession of the book is " << difference <<  " days overdue" << endl;
              cout << "The current penalty is €5"<< endl;
            }
            else {
              cout<< endl <<"The temporary owner still has " << difference <<" days to return the" << endl;
               cout  << "book before being fined" << endl;

            }
            cout << "---------------------------------------------------------"<< endl;
             }
        


          
           
    }
   
}
file_display.close();
}
//--------------------------------------------------------

//dates comparison function
void timeChecking(int c_day, int c_month, int c_year)
{


   time_t rawtime;
	 struct tm* timeinfo;
   //gets current date
    time(&rawtime);
  	timeinfo = localtime(&rawtime);


    struct tm a = {0,0,0,timeinfo->tm_mday,timeinfo->tm_mon + 1,timeinfo->tm_year}; //today date
    struct tm b = {0,0,0,c_day,c_month,c_year-1900}; // due date
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    if ( x != (time_t)(-1) && y != (time_t)(-1) )
    {
        difference = difftime(y, x) / (60 * 60 * 24);
   
    }
}



//--------------------------------------------------------
//enter new data to file
bool EnterNewBook(string book_t, string autor_name, int pages, string r_d, string r_m, string r_y, string person_name, string  d_d, string d_m, string d_y){
ifstream file_in;
ofstream file_out;
string line; //check lines
int i;
int fday, fyear, fmonth;
int counter;
check_l=false;


 file_in.open (permanent_path.c_str());
 file_out.open (permanent_path.c_str(),ios::app); 

 while (getline(file_in, line))//check if book exist already
    {    
        if (line.find("Book Title - [ "+book_t+" ]") != string::npos ){
          if(check_l==false){
            cout << "This book has been previously inputted: "<< endl<<endl;
          }
              cout << "---------------------------------------------------------"<< endl;
              for (i=1; i<7; i++ ){
              cout << line << endl;
              getline(file_in, line);

              if (line.find("Due date - [") != string::npos ){
                  
               int s = line.length();
               char rplc[s+1];
               strcpy(rplc, line.c_str());
               //get day from file
               fday=((int)rplc[13]-48)*10 +((int)rplc[14]-48);
               
               //get month from file
               fmonth=((int)rplc[16]-48)*10 +((int)rplc[17]-48);

               //get year from file
               fyear=((int)rplc[19]-48)*1000 +((int)rplc[20]-48)*100+((int)rplc[21]-48)*10 +((int)rplc[21]-48);
               
               
             }
             
             }
            check_l=true;


            timeChecking(fday, fmonth, fyear);
            if(difference<0){
              difference=difference*(-1);
              cout << endl << "The date of possession of the book is " << difference <<  " days overdue" << endl;
              cout << "The current penalty is €5"<< endl;
            }
            else {
              cout<< endl <<"The temporary owner still has " << difference <<" days to return the" << endl;
               cout  << "book before being fined" << endl;

            }
            cout << "---------------------------------------------------------"<< endl;
        }
      
} 
if (check_l == true){
  cout << endl;
cout << "Would you like to add  this book one more time? [y/N] "<< endl;
cin >> response;
getchar();
}
if (response == 'Y' || response == 'y' || check_l== false)//if program not exist
 {

 if(file_in.is_open())
  
  file_in.open(permanent_path.c_str(), ios::out);
  file_out << "\n---------------------------------------------------------"; 
 file_out << "\nBook Title" << " - [ " << book_t << " ] "; 
 file_out << "\nAutor Name" << " - [ " << autor_name << " ] " ;
 file_out << "\nNumber of pages" << " - [ " << pages << " ] " ;
 file_out << "\nRelease date" << " - [ " << r_d << "/"<< r_m << "/" << r_y << " ] " ;
 file_out << "\nPerson who has it" << " - [ " << person_name << " ] " ;
 file_out << "\nDue date" << " - [ " << d_d << "/"<< d_m << "/" << d_y << " ] " ;
  file_out << "\n---------------------------------------------------------\n"; 
  
}
file_in.close();
 file_out.close();
return 0;
}

//-------------------------------------------------------------

//book  serch by title
bool getBookByTitle(string search_name){
    ifstream file_in(permanent_path);
    string fa_line;
    check_l=false;//started value for check
    int gday, gmonth, gyear;
    int i;
   
   while (getline(file_in, fa_line))//till file end
    {    
    


        if (fa_line.find("Book Title - [ "+search_name+" ]") != string::npos){//if the program  is find
          
        
            cout << "---------------------------------------------------------"<< endl;
              for (i=1; i<7; i++ ){
              cout << fa_line << endl;
              getline(file_in, fa_line);

              if (fa_line.find("Due date - [") != string::npos ){
                  
               int s = fa_line.length();
               char rplc[s+1];
               strcpy(rplc, fa_line.c_str());
               //get day from file
               gday=((int)rplc[13]-48)*10 +((int)rplc[14]-48);
               
               //get month from file
               gmonth=((int)rplc[16]-48)*10 +((int)rplc[17]-48);

               //get year from file
               gyear=((int)rplc[19]-48)*1000 +((int)rplc[20]-48)*100+((int)rplc[21]-48)*10 +((int)rplc[21]-48);
               
               
             }
             
             }
         


            timeChecking(gday, gmonth, gyear);
            if(difference<0){
              difference=difference*(-1);
              cout << endl << "The date of possession of the book is " << difference <<  " days overdue" << endl;
              cout << "The current penalty is €5"<< endl;
            }
            else {
              cout<< endl <<"The temporary owner still has " << difference <<" days to return the" << endl;
                cout << "book before being fined" << endl;

            }
            cout << "---------------------------------------------------------"<< endl;
            check_l=true;//assign new value for check
            
        }
       
} 
if (check_l==true)
{
  return 0;//stopper
}


  if (fa_line.find("[ "+search_name+" ]") == string::npos && check_l==false)//if the program  is find
    {
        cout << "This Book was not founded! :(" << endl<<endl;
    }
 return 0;       

}
};//class closed


//-------------------------------------------------------------
//display menu content
void menuContents() {
cout<<"--------------------------------------------------------" << endl;
cout<<"          --------  ";
cout<<"TASK FROM COLLEGUE";
cout<<"  --------          " << endl;
cout<<"--------------------------------------------------------" << endl;
cout << endl;
cout << "Select the operation you want to perform:" << endl;
cout << "--------------------------------------------------------" << endl;
cout << "[1] Insert new book: " << endl;
cout << "[2] Display all books: " << endl;
cout << "[3] Find book by title or autor name: " << endl;
cout << "[4] Finish work: " << endl;
}

//-----------------------------------------------------
//menu functins

void Menu(int *keyPass) {
char keyOperation;
menuContents();
do {
keyOperation = getchar();
if ((isdigit(keyOperation) == false) && (keyOperation != '\n')) {
cout << "You must specify a number... [!]" << endl;
cout << "Try again:" << endl;
menuContents();
}
} while (isdigit((unsigned char)keyOperation) == false);
*keyPass = (int)keyOperation - '0';
}
//------------------------------------------------------------
//void functions variables
BookActions myAction;

string file_m = "/home/user_name/Desktop/Task_from_collegue/Books_Data.txt";
string bookTitle;
string autorName;
string personName;
string fa_line;

int num_page;
string r_day, r_month, r_year;
string due_day, due_month, due_year;
int line_counter;

//------------------------------------------------------------
//get autor name
void specifyTitle(){
getline(cin, bookTitle);

}
//------------------------------------------------------------
//get autor name
void specifyAutorName(){
getline(cin, autorName);

}
//------------------------------------------------------------
//get person Name
void specifyPersonName(){
  getline(cin, personName);
}
//------------------------------------------------------------
///get number of pages
void specifyPages(){
cin >> num_page;
}
//------------------------------------------------------------
void specifyReleaseD(){
   cout<< "Input example: (day: 09 / month: 06 / year: 2022)"<<endl << endl;
  cout << "Please enter the day of release: ";
  cin >> r_day;
  cout<< endl ;
  cout << "Please enter the month of release: ";
  cin >> r_month;
  cout<< endl ;
  cout << "Please enter the year of release: ";
  cin >> r_year;
  cout << endl;

 int conv_d = stoi(r_day);
 int conv_m = stoi(r_month);
  if ((int)conv_d>31 || conv_m>12){
    cout<< "Try again. Please enter the real date!"<<endl;
    specifyReleaseD();
  }
getchar();
}
//------------------------------------------------------------
void specifyDueD(){
  cout<< "Input example: (day: 09 / month: 03 / year: 2022)"<<endl << endl;
  cout << "Please enter the due day: ";
  cin >> due_day;
  cout<< endl ;
  cout << "Please enter the due month: ";
  cin >> due_month;
  cout<< endl ;
  cout << "Please enter the due year: ";
  cin >> due_year;
   cout << endl;

  int conv_d = stoi(due_day);
 int conv_m = stoi(due_month);
  if ((int)conv_d>31 || conv_m>12){
    cout<< "Try again. Please enter the real date!"<< endl;
    specifyDueD();
  }
getchar();
}

void bookDataFunc(){
cout << "Please specify Book Title: ";
specifyTitle();
cout << endl ;

cout << "Please specify Autor Name: ";
specifyAutorName();
cout << endl ;

cout << "Please specify Pages Number: ";
specifyPages();
cout << endl<<endl ;

specifyReleaseD();
cout << endl ;
cout << "Please specify Name of Person who has it: ";
specifyPersonName();
cout << endl << endl;
specifyDueD();
}


//------------------------------------------------------------
///Folder to store data
bool FolderCreation(const char * name) 
{ 
auto folder_creation ="mkdir /home/user_name/Desktop/Task_from_collegue";//folder creation operation

    struct stat s;
    if (stat(name, &s)){//create new folder
        system(folder_creation);
        cout << "Folder for storing your books data was created" << endl;
      myAction.FileToBookData();
    } 
   
    return S_ISDIR(s.st_mode);//return for bool
}
//------------------------------------------------------------


int main(){
BookActions bookAccess;
auto path = "/home/user_name/Desktop/Task_from_collegue";//folder store path
              
//-------------------------------------------------------------
//First script run
  FolderCreation(path);
 
int keyPass;

do {
          Menu(&keyPass);
           switch (keyPass) 
           {
             case 1:
             getchar();
             cout << "Operation [1]" << endl <<endl;
             bookDataFunc();
             bookAccess.EnterNewBook(bookTitle, autorName, num_page,  r_day, r_month, r_year, personName, due_day, due_month, due_year );
             cout << endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             break;

             case 2:
             cout << "Operation [2]" << endl<<endl;
             cout << "Your library data:" << endl;
             bookAccess.DisplayData();
             cout<< endl<<endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             getchar();
             break;
 
             case 3:
             cout << "Operation [3]" << endl<<endl;
             getchar();
             cout << "Enter Book Title you want to serch: ";
             specifyTitle();
             cout << endl;
             cout << "Your Book by Title: " << endl << endl;
             bookAccess.getBookByTitle(bookTitle);
             cout << endl<< endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             break;
 
            case 4:
            cout << "Operation [4]"<< endl ;
            cout << "Thank you for choosing this script! " << endl << endl;
            cout << "Goodbye :) ..." << endl << endl;
            getchar();
            return 0;
            

            default:
            cout << "Goodbye :) ..." << endl << endl;
               
             }
              } while (keyPass != 5);          
return 0;
}
