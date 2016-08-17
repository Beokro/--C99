// switch differnt type and have a default
// in for loop, init a variable that has the same name as the outside variable
// try to switch a non-basetype statement
int main() {
  char c = 'c';
  char b;
  char * cp = &c;
  for ( int i = 0; i < 5; i++ ) {
    char c = 'd';
    char b = 's';
  }
  switch ( c ) {
  case 'c' : return 1;
  case 'b' : return 0;
  case b : return 1;
  default : return 1;
  }
  switch ( cp ) {
  case 'c' : return 1;
  case 'b' : return 0;
  case b : return 1;
  default : return 1;
  }
  return 1;
}
