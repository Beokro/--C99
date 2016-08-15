// declare a procedure
// decl and assign multiple same type variable
// return a const type when base type is required
// return a base type when const is required
// return a number type when number type is required
// call a function with same number of args and same type
// call a number with same number of args and const/non const type, void/pointer type
// assign a string literature to a string variable

int testProc1( int a, int b, char c, bool bb ){
  long l = a + b;
  return l;
}

const int testProc2() {
  int a = 1;
  return a;
}

int testProc3() {
  const int a = 2;
  return a;
}

int main() {
  int c = testProc1( 1, 2, 'c', true );
  const int ci = 5;
  const char cc = 'c';
  c = testProc1( ci, ci, cc, true );
  bool b = true, bb = false, bbb = true;
  string s = "121321";
  s = "12312312asda";
  testProc2();
  testProc3();
  return 1;
}

char * failed() {
  return NULL;
}
