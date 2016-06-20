#include <stdio.h>
#include <string.h>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

//add macro to map and change the line if it contains defiend macro
int ProcessLine(string& line, map<string,string>& mymap );

int main ( int argc, char **argv ){
  if(argc!=2){
    cerr<<"You have to enter the name of the file you want to compile\n";
    return 1;
  }

  string line, text;
  int n_lines = 0;
  ifstream myfile (argv[1]);
  map<string,string> mymap;
  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
        {
          cout << line << '\n';
          if(ProcessLine(line, mymap)!=1)
            text+=(line+'\n');
        }
      myfile.close();
    }

  else cout << "Unable to open file";

  cout<<"\n\n\n";
  cout<<text;


  return 0;
}

int  ProcessLine(string& line, map<string,string>& mymap ){
  int size = line.size();

  //if it is empty, do nothing
  if(size == 0)
    return 0;

  //it is a macro define scetence, need to add it to the map
  if(size>6 && line.substr(0,7) == "#define"){
    line = line.substr(7, size-7);

    //convert the string to char * for strtok function
    char * c = new char[line.length()+1];
    strcpy(c,line.c_str());

    //what's being replaced, the word after #define
    string s;

    char * ctemp;
    ctemp = strtok (c," ");
    if (ctemp != NULL)
      {
        s = string(ctemp);
        ctemp = strtok (NULL, " ");
        if(ctemp != NULL){

          mymap.insert ( pair<string,string>(s,string(ctemp)) );
        }
      }
    delete c;
    //1 mean it is a macro define scentence, no need to add it
    return 1;

  }

  //check if we need to replace any macro in this line
  if(mymap.size()!=0){
    //split the line by space
    char * c = new char[line.length()+1];
    strcpy(c,line.c_str());

    //used to determined if certain key exist
    map<string,string>::iterator it;

    char * pch;
    pch = strtok (c," (),.-+*/%!~*=[]{}|&:;");
    while (pch != NULL)
      {
        it = mymap.find(string(pch));
        if(it != mymap.end())
          {
            int index = 0;
            //element found, need to replace
            while (true) {
              /* Locate the substring to replace. */
              index = line.find(string(pch), index);
              if (index == std::string::npos) break;

              /* Make the replacement. */
              line.replace(index, it->first.length(), it->second);

              /* Advance index forward so the next iteration doesn't pick it up as well. */
              index += it->second.length();

            }
          }
        pch = strtok (NULL, " (),.-+*/%!~*=[]{}|&:;");
      }
    return 0;
  }

  return 0;
}

