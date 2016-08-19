// && || 2 boolean
// number ( const or not ) + - * / ^ & % >> <<
// declare a list with same type
// array access a non exist variable

int main() {
  bool b1 = true, b2 = false;
  int i = 1, j =2, k =3;
  if ( b1 && b2 ){
    b1 = false;
  }
  if ( b1 || b2 ) {
    b2 = false;
  } else {
    b2 = true;
  }
  i = i + j * k / i ^ i;
  i = i & k % k >> 2 << 2;

  char c[5] = { 'a', 'b', 'c', 'd', 'e' };
  char d[2][3] = { { 'a', 'b', 'c'}, { 'd', 'e', 'f' } };
  f[2] = 'c';
  return 1;
}
