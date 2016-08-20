// in 2d access, one or two non number is used
int main() {
  int a[ 1 ][ 2 ] = { { 1, 2 } };
  a[ 0 ][ 1 ] = 2;
  a[ 'c' ][ 1 ] = 1;
  return 1;
}
