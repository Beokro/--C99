// expect output is 3
int main() {
  int a[ 2 ] = { 3, 1 };
  int b = a[ 0 ];
  int c =0;
  a[ 1 ] = b;
  c = a[ 1 ];
  return c;
}
