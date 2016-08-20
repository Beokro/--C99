// array acces with an non number type index
int main() {
  int a[3] = { 1, 2, 3 };
  a[ 0 ] = 2;
  a[ 'c' ] = 4;
  return 1;
}
