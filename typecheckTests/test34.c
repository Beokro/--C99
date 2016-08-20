// double access a non 2d array type
int main() {
  int a[ 1 ][ 2 ] = { { 1, 2 } };
  a[ 0 ][ 1 ] = 2;
  int b[ 2 ] = { 1, 2 };
  b[ 0 ][ 1 ] = 2;
  return 1;
}
