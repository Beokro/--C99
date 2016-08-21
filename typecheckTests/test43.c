// compare two different type pointer
int main() {
  int b = 5;
  int *a = &b;
  int *c = &b;
  char cc = 'c';
  char *d = &cc;
  bool bbb = a >= c;
  if ( a > d ) {
    *a = 2;
  }
  return 1;
}
