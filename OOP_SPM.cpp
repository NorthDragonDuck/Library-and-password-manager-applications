/* 
Additional comments:
*In recent tests, the script worked without errors
*Possible to use other libraries on Windows
*Lines 34, 35 , 281, 282, 408, 611, 638 need to replace the path 
*A not entirely secure encryption algorithm was used
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


// set some generous maximum lengths for each line in a file
#define MAX_LINE 2048

using namespace std;


//creating class to facilitate access to certain functions
class PasswordCreation{
private:
string permanent_path = "/home/user_name/Desktop/Simple_Pasword_Menadger/My_passwords.txt";//file to store passwords
string temp_file = "/home/user_name/Desktop/Simple_Pasword_Menadger/Encription_test.txt";//buffer file
    char c;//get file data
    bool check_l;//true value checker


public:

void FileTopasswordStorage(string master_pass)//file creation on first start-up
{ 
fstream file_programm;

 file_programm.open(permanent_path.c_str(), ios::out );
if(file_programm.is_open())
  {
 file_programm <<  master_pass  << "\n"; //save master password
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
   int l_counter=0;
   
    file_display.open(permanent_path.c_str(), fstream::in);
    if(!file_display.is_open())//file closed
    {
        cout<<"\nError Occurred! ";
       
    }
    
   else{ //file opened
    while( getline (file_display,content))//till the end
    {
    l_counter++;
  if(l_counter > 1){
    cout << content << endl;
  }
    }
   
}
file_display.close();
}





//--------------------------------------------------------
//enter new data to file
bool EnterNewPaswordTo(string program_name, string password){
ifstream file_in;
ofstream file_out;
string line; //check lines
check_l=false;


 file_in.open (permanent_path.c_str());
 file_out.open (permanent_path.c_str(),ios::app); 

 while (getline(file_in, line))//check if program/service exist already
    {    
        if (line.find("[ "+program_name+" ]") != string::npos){
          
              cout << "This program/service exist already: "<< endl<<endl;
  cout << line << endl;
            check_l=true;
       
        }
      
} 

if (check_l==false)//if program not exist
 {

 if(file_in.is_open())
  
  file_in.open(permanent_path.c_str(), ios::out);
  
 file_out << "\n[ " << program_name << " ]" << " - [" << password << "] " << "\n"; 

  
}
file_in.close();
 file_out.close();
return 0;
}
//--------------------------------------------------
//display head
void head(){
  cout<<endl;
  
  cout<<" ---------------------------------------------"<<endl;

  cout<<"  --------  ";
 
  cout<<"SIMPLE PASSWORD MANAGER";
  
  cout<<"  --------  "<<endl;
  
  cout<<" ---------------------------------------------"<<endl;
}
//------------------------------------------------------
//Generate random 15 characters password
void yes(){
  int size =15;
   string input;
  cout<<endl;
  cout<<"Secure generated password suggested for you: ";
  cout<<endl<<endl;
 srand(time(0));//get random time for rundom function
  for(int i=0;i<size;++i){
    int num=rand() % 94 + 1;//get rand char
    num=num+32;
    cout<<(char)num;
     input = input + (char)num;
  }

  cout<<endl<<endl;
 
  
}
//------------------------------------------------------------------
//program start function
void start(){

  head();
 
   cout<<"    Secure password criteria:"<<endl;
  cout<<"    *At least 12 characters "<<endl;
 cout<<"    *A mixture of both uppercase and lowercase letters."<<endl;
 cout<<"    *A mixture of letters and numbers."<<endl;
  cout<<"    *Inclusion of at least one special character, e.g., ! @ # ? ]"<<endl;
  yes();
  cout<<" ------------------------------------------------"<<endl;
}


//------------------------------------------------------------------
//delete temp file data
void delete_filedata(){
fstream fin;
fin.open(temp_file.c_str(), std::ifstream::out | std::ifstream::trunc );
fin.close();

}


//---------------------------------------------
// copy data from temp to main file
 void copy(){
fstream f_in, f_out;

f_in.open(temp_file.c_str(), fstream::in);
f_out.open(permanent_path.c_str(), fstream::out);

  if(f_in && f_out)
       {  while (f_in >> noskipws >> c) //till file end
       {
      f_out << c;
        }    
         cout << endl;}
else{

        cout<< "Error!!!" << endl;
        }
f_in.close();
    f_out.close();
delete_filedata();//delete temp file data
 }
 //----------------------------------
// Encryption function by your master password
void encrypt(string master_key)
{   fstream f_in, f_out;
    int i =0;
    int n = master_key.length();//password len
    char key[n + 1];//declaring character array

    // copying the contents of the
    // string to char array
    strcpy(key, master_key.c_str());

    f_in.open(permanent_path.c_str(), fstream::in);
    f_out.open(temp_file.c_str(), fstream::out);
 
    // Reading original file till
    // end of file
    while (f_in >> noskipws >> c) 
    {
        int temp = (c + (int)key[i]);//replace char 
        f_out << (char)temp;//output replace char
        if (i < n)//get next password char or return to first one
        {
         i++;   
         }
         else {
         i=0;
          }
    }
    f_in.close();
    f_out.close();
copy();
}
 //--------------------------------------------
//  decryption function
void decrypt(string master_key)
{   fstream fin, fout;
    int i =0;
    int n = master_key.length();
    char key[n + 1];// declaring character array
 
    // copying the contents of the
    // string to char array
    strcpy(key, master_key.c_str());
 
    
   
    fin.open(permanent_path.c_str(), fstream::in);
    fout.open(temp_file.c_str(), fstream::out);
 
    while (fin >> noskipws >> c) {
 
        // Remove the key char from the
        // character
        int temp = (c - (int)key[i]);
        fout << (char)temp;
         if (i < n){
         i++;    
         }
         else {
          i=0;
          }
    }
    fin.close();
    fout.close();
    copy();
}
//---------------------------------------------------------
// rewrite file data
void replaceFileline(string data,int replace_line, bool action){

  auto filename ="/home/user_name/Desktop/Simple_Pasword_Menadger/My_passwords.txt";//original file
  auto temp_filename ="/home/user_name/Desktop/Simple_Pasword_Menadger/temp.txt";//temp file
  FILE *file, *temp;

  int s = data.length();
  char rplc[s+1];
  strcpy(rplc, data.c_str());
   
  char buffer[MAX_LINE];

  fflush(stdin);//for stable
  
  // open the original file for reading, and the temp file for writing
  file = fopen(filename, "r");
  temp = fopen(temp_filename, "w");
  
  // check if either file failed to open, if either did exit with error status
  if (file == NULL || temp == NULL)
  {
    printf("Error opening files(s).\n");
    return;
  }
  
  // keep reading the file so long as keep_reading is true
  bool keep_reading = true;
  // keep track of the current line number we are reading from the file
  int current_line = 1;

  do 
  {  if (action==true){//prog replace
      // read the next line of the file into the buffer
    fgets(buffer, MAX_LINE, file);
    
    // if we've reached the end of the file, stop reading
    if (feof(file)) keep_reading = false;
    // if the line we've reached is the one we wish to replace, write the 
    // replacement text to this line of the temp file
    else if (current_line == replace_line || current_line == replace_line-1){
      fputs("", temp);
       fputs("", temp);
      } 
    // otherwise write this line to the temp file
    else fputs(buffer, temp);
   
    } else if (action==false){// prog deletion
      // read the next line of the file into the buffer
    fgets(buffer, MAX_LINE, file);
    
    // if we've reached the end of the file, stop reading
    if (feof(file)) keep_reading = false;
    // if the line we've reached is the one we wish to replace, write the 
    // replacement text to this line of the temp file
    else if (current_line == replace_line){
        
      fputs(rplc, temp);
      fputs("\n", temp);
      
      }
      //replace next line if eist
      else if (current_line== replace_line+1){

        fputs("\n", temp);
      }
    // otherwise write this line to the temp file
    else fputs(buffer, temp);
    }
    //keep reading the next line
    current_line++;

  } while (keep_reading);

  fclose(file);
  fclose(temp);
  
  // delete the original file, rename temp file to the original file's name
  remove(filename);
  rename(temp_filename, filename);
}

};//class close


//-------------------------------------------------------------
//display menu content
void menuContents() {
cout<<" ---------------------------------------------" << endl;
cout<<"  --------  ";
cout<<"SIMPLE PASSWORD MANAGER";
cout<<"  --------  " << endl;
cout<<" ---------------------------------------------" << endl;
cout << endl;
cout << "Select the operation you want to perform:" << endl;
cout << "-------------------------------------" << endl;
cout << "[1] Insert password for new service program: " << endl;
cout << "[2] Display my passwords: " << endl;
cout << "[3] Find program/service/password by name or part of it: " << endl;
cout << "[4] Generate secure random password: " << endl;
cout << "[5] Ghange password for service/program: " << endl;
cout << "[6] Delete service program: " << endl;
cout << "[7] Change master password: " << endl;
cout << "[8] Finish work: " << endl;
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

string program_service_name;
string password;
bool my_return;
string input;
PasswordCreation test;
string file_m = "/home/user_name/Desktop/Simple_Pasword_Menadger/My_passwords.txt";
int line_counter;
bool check_a;
string fa_line;
//------------------------------------------------------------
//get master password
void specifyPass(){
getline(cin, password);

}
//------------------------------------------------------------
//get general password
void myGeneralPass(){
  getline(cin, input);
}
//------------------------------------------------------------
///get password name
void addNewName(){
getline(cin, program_service_name);
}



//------------------------------------------------------------
//get program name and password
void iTswork(){ 
  getchar();
  cout << "Specify program/service name: ";
               addNewName();
               cout << endl;
               cout << "Specify password: ";
               myGeneralPass();
           cout << endl;

}

//-------------------------------------------------------------

//program service serch
bool getLine(string search_name){
    ifstream find_pass(file_m);
    check_a=false;//started value for check
    line_counter=0;//line counter
   
   while (getline(find_pass, fa_line))//till file end
    {    
      line_counter++;//get line number


        if (fa_line.find("[ "+search_name+" ]") != string::npos){//if the program  is find
          
            cout << fa_line << endl ;//display line
            check_a=true;//assign new value for check
            return 0;//stopper
        }
       
} 

  if (fa_line.find("[ "+search_name+" ]") == string::npos && check_a==false)//if the program  is find
    {
        cout << "This program or service not founded! :(" << endl<<endl;
    }
 return 0;       

}
//-------------------------------------------------------------
//replace program/service password
bool LineReplace(){
fstream file_in(file_m);
check_a=false;
line_counter=0;
addNewName();  //name search

 while (getline(file_in, fa_line) && check_a==false)//till file end
    {   
      line_counter++;
        if (fa_line.find("[ "+program_service_name+" ]") != string::npos){
  
            check_a=true;//name is find
       
        }
      
} 
if(check_a==false){//if name is not find
cout << endl;
cout << "Sorry, this program/service does not exist : (" << endl<< endl;
 }  else {   //if  name find 
   cout << endl;
   cout << "Specify new password: ";
myGeneralPass();//enter new pass
cout << endl;
input= "[ " + program_service_name + " ] - [" + input + "]";//replase text
test.replaceFileline(input, line_counter,false);//replace line
cout << "Insertion has been done successfully! : )" << endl<< endl;
}
return 0;
}
//--------------------------------------------------------------
//remove line

void forProgarmRemove(){
 cout << "Specify name of program/service you want to remove: ";
              myGeneralPass();//enter name to be removal 
              cout << endl;
            
               getLine(input);
               if(check_a==true){//if name exist
               test.replaceFileline(input, line_counter, true);
               }

cout << endl;               
};
//--------------------------------------------------------------
//checking master password security

void printStrongNess(string& password) {


   int n = password.length();
   // Checking lower alphabet in string
   
   bool hasLower = false, hasUpper = false;
   bool hasDigit = false, specialChar = false;
   string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

   for (int i = 0; i < n; i++) {
      if (islower(password[i]))
         hasLower = true;
      if (isupper(password[i]))
         hasUpper = true;
      if (isdigit(password[i]))
         hasDigit = true;
      size_t special = password.find_first_not_of(normalChars);
      if (special != string::npos)
         specialChar = true;
   }
   // Strength of password
   cout << "Strength of password: ";
   if (hasLower && hasUpper && hasDigit &&
      specialChar && (n >= 12)){
      cout << "Strong password" << endl;
      my_return= true;
      }
   else{cout << "Sorry you pasword easy to gues, try" << endl;
      cout << "enter new password acording security criteria. "<<endl<<endl;
      cout<<"    Secure password criteria:"<<endl;
  cout<<"    *At least 12 characters "<<endl;
 cout<<"    *A mixture of both uppercase and lowercase letters."<<endl;
 cout<<"    *A mixture of letters and numbers."<<endl;
  cout<<"    *Inclusion of at least one special character, e.g., ! @ # ? ]"<<endl << endl;
      
      my_return= false;
      
      }
     
}

//------------------------------------------------------------
//recurse function
void recurseFun(){
  cout << "Please enter new master password: ";
specifyPass();//enter master pass
printStrongNess(password);//check
if(my_return == true){//if pasword strong
cout << "Success insertion of master password! : )"<< endl<<endl;

}
else if(my_return == false){//if password not secure enought
 recurseFun();
}

}
//------------------------------------------------------------
//check master password
void encrCheck(){
 string pLine;
ifstream infile(file_m);


 specifyPass();//enter master password
test.decrypt(password);

  if (infile.good())//get first linne
  { 
    getline(infile, pLine);
    
  }

 if (password==pLine){//if stored and entered passwords the same open program
   cout  << endl;

 }
else {//master password false
  test.head();
test.encrypt(password);
cout << "Wrong password, try enter password again: ";
encrCheck();
}
}
//------------------------------------------------------------
///Folder to store file with your passwords creation
bool FolderCreation(const char * name) 
{ 
auto folder_creation ="mkdir /home/lugyxa/Desktop/Simple_Pasword_Menadger";//folder creation operation

    struct stat s;
    if (stat(name, &s)){//create new folder
        system(folder_creation);
        cout << "Folder for storing your passwords was created" << endl;
        test.start();
        recurseFun();
        test.FileTopasswordStorage(password);
       
    } 
    else{//if exist already
    test.head();
cout << endl; 
cout << "Please enter master password: ";
encrCheck();

 

    }
    return S_ISDIR(s.st_mode);//return for bool
}
//------------------------------------------------------------


int main(){
PasswordCreation testpass;//class access
auto path = "/home/user_name/Desktop/Simple_Pasword_Menadger";//folder store path
              
//-------------------------------------------------------------
//First script run
  FolderCreation(path);
 
int keyPass;

do {
          Menu(&keyPass);
           switch (keyPass) 
           {
             case 1:
             cout << "Operation [1]" << endl <<endl;

               iTswork();
               testpass.EnterNewPaswordTo(program_service_name, input);

             cout << endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             break;

             case 2:
             cout << "Operation [2]" << endl<<endl;
             cout << "[ Program/service Name ] - [Password]:" << endl;

             testpass.DisplayData();
             cout<< endl<<endl;

             cout << "Press enter key [info]..." << endl;
             getchar();
             getchar();
             break;
 
             case 3:
             cout << "Operation [3]" << endl<<endl;
             getchar();
             cout << "Enter search program/service name: ";
             
             addNewName();
             cout << endl;
             cout << "Your program/service and password: " << endl << endl;
             getLine(program_service_name);
            
  
             cout << endl<< endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             break;
 
             case 4:
             cout << "Operation [4]" << endl<<endl;

             testpass.yes();

             cout << endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             getchar();
             break;

             case 5:
             cout << "Operation [5]" << endl<<endl;
             getchar();

             cout << "Enter search program/service name: ";
             LineReplace();

             cout << "Press enter key [info]..." << endl;
             getchar();
              break;

              case 6:
             cout << "Operation [6]" << endl<< endl;
             getchar();

            forProgarmRemove();

             cout << "Press enter key [info]..." << endl;
             getchar();
             break;

               case 7:
             cout << "Operation [7]" << endl<<endl;
              getchar();

              test.start();
              recurseFun();
              testpass.replaceFileline(password, 1, false);

             cout << endl;
             cout << "Press enter key [info]..." << endl;
             getchar();
             break;

               case 8:
             cout << "Operation [8]"<< endl ;
            testpass.encrypt(password);
              
            cout << "Thank you for choosing 'SYMPLE PASSWORD MANAGER' " << endl << endl;
            cout << "Goodbye :) ..." << endl << endl;
            getchar();
             return 0;
            

              default:
              testpass.encrypt(password);
              cout << "Goodbye :) ..." << endl << endl;
               
             }
              } while (keyPass != 9);          
return 0;
}
