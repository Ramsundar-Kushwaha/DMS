#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
// #include <cstdlib>

using namespace std;

//for clearing screen
void clearScreen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

//CLASS FOR ERROR CHECK AND BUFFER CLEARING
class Error_Buffer{
  public:

  //buffer clearing function
  void clearBuffer(){
    cin.clear();//clear error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//clear input buffer upto maximum characted and stopped when new line character is found
  }

  //error checking function
  bool checkError(){
    try{
      if(cin.fail()){
        clearBuffer();
        throw invalid_argument("invalid input ");
      }
    }
    catch(invalid_argument& e){
      cout << "please enter valid input";
      return false;
    }
    return true;
  }
};

//CLASS FOR TABLE CREATION
class Table:public Error_Buffer{
  protected:
  string tableName;
  int numberOfRows;
  int numberOfColumn;
  
  public:
  //top row function
  void topRow(int t, vector<string>& namest){
    cout << "+";
    for(int i = 0; i < t; i++){
      int width = namest[i].length();
      cout << string(width + 2, '-') << "+";
    }
    cout << endl;
  }
  
  //mid row function
  void midRow(int m, vector<string>& namesm){
    cout << "|";
    for(int i = 0; i < m; i++){
      int width = namesm[i].length();
      cout << " " << setw(width) << namesm[i] << " |";
    }
    cout << endl;
  }
  
  //bottom row function
  void bottomRow(int b, vector<string>& namesb){
    topRow(b, namesb);
  }
  
  //class for table's row and column
  int table(int row, int col, vector<string>& namestb){
    for(int i = 0; i < row; i++){
      if(row == 1){
        topRow(col, namestb);
        midRow(col, namestb);
        bottomRow(col, namestb);
      }
      if(row > 1){
        topRow(col, namestb);
        midRow(col, namestb);
        if(i == row-1){
          bottomRow(col, namestb);
        }
      }
    }
    return 0;
  }
};

//CLASS FOR GETTING DATA FOR TABLE CREATION AND OUTPUT TABLE FORMAT
class getPut:public Table{
  private:
  vector<string>names;//for automatic memory allocation

  public:
  //table formation
  void getData(){
    bool trueCondition;
    
    cout << "Enter Table Name: ";
    cin >> tableName;
    
    if(tableName.length() < 3){
      cerr << "invalid name : please enter again" << endl;
      return getData();
    }
    
    trueCondition = checkError();
    if(!trueCondition){
      return;
    }
    clearBuffer();
    
    cout << "Enter Number Of Rows: ";
    cin >> numberOfRows;
    if(numberOfRows < 1){
      cout << "row can't be lesan one" << endl;
      return getData();
    }
    
    trueCondition = checkError();
    if(!trueCondition){
      return;
    }
    clearBuffer();
    
    cout << "Enter Number of Column: ";
    cin >> numberOfColumn;
    if(numberOfColumn < 1){
      cout << "column can't be lesan one" << endl;
      return getData();
    }
    
    trueCondition = checkError();
    if(!trueCondition){
      return;
    }
    clearBuffer();
    
    
    //error handling while memory allocation te vector<string>name
    try{
        names.resize(numberOfColumn);
        cout << "memory allocation successful : "<<names.size() << endl;
      
      }
      catch(const bad_alloc& e){
          cerr << "memory allocation failed" << endl;
          return;
        }
        
    for(int i = 0; i < numberOfColumn; i++){
      cout << "Enter Table Heading " << i+1 << ": ";
      getline(cin, names[i]);
    }
  }

  //table out put format
  void outPutFormat(){
    clearScreen();
    if(numberOfColumn >= 1 && numberOfRows >= 1){
      table(numberOfRows, numberOfColumn, names);
    }
    return;
  }

};

//main function starts here...  
int main(){
  getPut ef;
  ef.getData();
  ef.outPutFormat();
  string x;
  cin >> x;
  return 0;
}
