// declare variable / function with same name but in differnet scope
// function used its argument and variable in higher scope
// int the for, while, if, have the variable with the same name as outer scope
// define a regular struct with members
// in struct, members have the same name
struct testType {
  int a ;
  bool b;
  char c;
  long l;
};
int a = 5;
int test() {
  return 5;
}
int main() {
  int a = 3;
  int test( int b) {
    b = a;
    return 0;
  }
  test(a);
  if ( true ) {
    a = 100;
    long b = a;
  }
  bool bo = true;
  while ( bo ) {
    bo = !bo;
  }
  for( int a = 5; a > 0 ; a-- ) {
    a+=0;
  }
  for( a = 3; a <5; a*= 5 ) {
    a = 0;
  }
  do {
    a += 5;
  } while ( a > 0 );
  return 1;
}

struct testType2 {
  int a;
  int b;
  int a;
};
