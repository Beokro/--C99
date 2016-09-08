// expect output 6
int test( int a, int b ) {
  return a + b;
}

int main() {
  int c = 1;
  c = test( 1, 5 );
  return c;
}
