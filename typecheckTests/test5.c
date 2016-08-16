// number > < >= <=number, pointer > < >= <. pointer
// same type of compare( == ), const does not matter
// !=, == a pointer with NULL
// ! with a bool
// - with a number literature
// use a undeclare variable
int main() {
  int a = 1, b = 2;
  const int ca = a, cb = b;
  long c = 3, d = 4;
  const long cc = c;
  short e = 5, f = 6;
  char ch = 'c';
  bool bb = a > b;
  int * ap = &a;
  int * bp = &b;
  long * cp = &c;
  char * ccp = &ch;
  bool * bbp;
  bb = b < a;
  bb = c >= e;
  bb = f <= b;
  bb = ap > bp;
  bb = ca == a;
  bb = ca >= cc;
  bb = ap == bp;
  bb = ccp == NULL;
  bb = bbp != NULL;
  bb = !bb;
  a = -5;
  asdasd = 1;
  return 0;
}
