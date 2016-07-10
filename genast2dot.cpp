#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//this file is used to read ast.cdef and generate
//correspoding ast.cdef functions 

void processline(string line);

int main () {
  string line;
  ifstream myfile ("ast.cdef");
  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
        {
          processline(line);
        }
      myfile.close();
    }

  else cout << "Unable to open file"; 

  return 0;
}

void processline(string line){
  int size = line.size();
  bool impl = true;
  string class_name = "";

  if ( size == 0 || line[0] == '#' ){
    return;
  }

  for(int i =0; i<size; i++){
    if(line[i] == ':'){
      impl = false;
      class_name = "";
      continue;
    }
    if(line[i] == ' '){
      break;
    }
    class_name += line[i];
  }

  if( impl ){
    class_name += "Impl";
  }
  cout << "void visit" << class_name
       << "(" << class_name << " *p) "
       << "{ draw(\"" << class_name <<"\", p); }";

  cout<<endl;
}
