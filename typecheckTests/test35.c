// double array access
int main() {
  int a[ 1 ][ 2 ] = { { 1, 2 } };
  a[ 0 ][ 1 ] = 2;
  int b[ 2 ] = { 1, 2 };
  int c = b[ 0 ][ 1 ];
  return 1;
}
