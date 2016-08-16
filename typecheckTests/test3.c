// array access a pointer/string type with number as index
// assign to array outside the decl
// double access a 2d array type with 2 number ( variable and element )
int main() {
  string s = "hahhahah";
  int asd;
  int a[ 2 ] = { 2,3 };
  int aa[1][2] = { {2,3} };
  aa[0][1] = 2;
  asd = a[1];
  int aaa = aa[1][2];
  s[ 1 ] = 'c';
  a = 5;
  return 0;
}
