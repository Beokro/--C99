#include <stdio.h>
#include <string.h>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;


//add macro to map and change the line if it contains defiend macro
int ProcessLine(string& line, map<string,string>& mymap, bool& append_mode, string& macro, string & replace );

int main ( int argc, char **argv ){
  if(argc!=2){
    cerr<<"You have to enter the name of the file you want to compile\n";
    return 1;
  }

  //if last line start with #define and end with \
 
  string line = "", text = "", macro = "", replace = "";
  int n_lines = 0;
  ifstream myfile (argv[1]);
  map<string,string> mymap;
  if (myfile.is_open())
    {
      bool append_mode = false;
      while ( getline (myfile,line) )
        {
          cout << line << '\n';
          if(ProcessLine(line, mymap, append_mode, macro, replace)!=1)
            text+=(line);
	  text+='\n';
        }
      myfile.close();
    }

  else cout << "Unable to open file";

  cout<<"\n\nnew file starts here\n";
  cout<<text;


  return 0;
}

int ProcessLine(string& line, map<string,string>& mymap, bool& append_mode, string& macro, string & replace ){
  int size = line.size();

  //check if it is in append_mode
  if(append_mode){
    //check if current line ends
    if(size !=0 && line[size-1] == '\\'){
      replace += line.substr(0,size-1);
    }
    else{
      append_mode = false;
      mymap.insert ( pair<string,string>(macro, replace+line) );
    }
    return 1;
  }

  //if it is empty, do nothing
  if(size == 0)
    return 0;

  //it is a macro define scetence, need to add it to the map
  if(size>6 && line.substr(0,7) == "#define"){
    int current_delete = 7;
    while(current_delete < size && line[current_delete] == ' ' ){
      current_delete++;
    }
    line = line.substr(current_delete, size-current_delete);
    size -= current_delete;

    int space_point =0;
    //find the space/spearte point between defined macro and replaced context
    for(int i = 0; i < size; i++){
      if(line[i] == ' '){
	space_point = i;
	break;
      }
    }
    //if not space found or space at last, error macro
    if(space_point ==0 || space_point == (size-1))
      return 0;
    if(line[line.size()-1] != '\\'){
      mymap.insert ( pair<string,string>(line.substr(0, space_point),
					 line.substr(space_point+1, size-space_point-1)) );
    }
    else{
      //line that start with #define and end with \, first case
      append_mode = true;
      macro = line.substr(0, space_point);
      cout<<"current macro is "<<macro<<endl;
      replace = line.substr(space_point+1, size-space_point-2);
    }
    

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
	      
	      if(index > 0 && ((line[index-1] >='A' && line[index-1] <='z')|| line[index-1] == '_')){
		break;
	      }
	      if(index < (size+string(pch).size()) && ((line[index+string(pch).size()] >='A' && line[index+1] <='z')|| line[index+1] == '_') ){
		break;
	      }
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

