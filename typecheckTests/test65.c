// In switch, case has different type than switch
int main() {
  int a =3;
  switch ( a ) {
  case 1 : return 1;
  case 2 : return 2;
  case 'c' : return -1;
  default : return 0;
  }
  return 1;
}
