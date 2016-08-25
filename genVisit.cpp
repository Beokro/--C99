#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdio.h>
#include <string.h>
using namespace std;

//this file is used to read ast.cdef and generate
//correspoding ast.cdef functions 

void genTypeCheck();
void gen2dot();
void processTypeCheck( string line );
void process2dot( string line );

int main ( int argc, char *argv[] ) {
  assert( argc == 2 && ( strcmp( argv[ 1 ], "2dot" ) == 0 || \
                         strcmp( argv[ 1 ], "typecheck" ) == 0 ) );

  if ( strcmp( argv[ 0 ], "2dot" ) == 0 ){
    gen2dot();
  } else {
    genTypeCheck();
  }
  return 0;
}

void genTypeCheck() {
  string line;
  ifstream myfile ("ast.cdef");
  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
        {
          processTypeCheck(line);
        }
      myfile.close();
    }

  else cout << "Unable to open file"; 

}

void gen2dot() {
  string line;
  ifstream myfile ("ast.cdef");
  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
        {
          process2dot(line);
        }
      myfile.close();
    }

  else cout << "Unable to open file"; 

}

void processTypeCheck( string line ){
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
       << "( " << class_name << " *p ) "
       << "{ " << endl << endl <<"}";

  cout << endl << endl;
}

void process2dot(string line){
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
