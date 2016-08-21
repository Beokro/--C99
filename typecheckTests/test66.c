// try to switch a non-basetype statement
int main() {
  int a = 1;
  int * aa = &a;
  switch ( aa ) {
  case 1 : return 1;
  default : return 0;
  }
  return 11;
}
