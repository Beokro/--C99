// call a function with same number of arguments but different type
int test1( int a, char c, bool b ) {
  return 1;
}
int main() {
  test1( 1, 'c', 2 );
  return 1;
}
