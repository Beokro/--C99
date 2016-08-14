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
  testProc2();
  testProc3();
  return 1;
}

char * failed() {
  return NULL;
}
