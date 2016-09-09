// expect 100
char test( char c, int a ) {
  if ( c == 'b' ) {
    c = 'd';
  } else {
    c = 'z';
  }
  return c;
}

char main() {
  char c1 = 'a';
  char c2 = 'b';
  int a = 2;
  c2 = test( c2, a );
  return c2;
}
