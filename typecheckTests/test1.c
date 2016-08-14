// basic assignment test
// pointer with same type
// pointer with NULL
// ( const )bool/char to ( const ) bool/char
// one main
int main(){
  int i;
  char c;
  bool b;
  short s;
  long l;
  long * ll = &l;
  short* ss = &s;
  bool *bb = &b;
  char *cc = NULL;
  const char cc1 = c;
  const char cc2 = 'c';
  const bool cb1 = b;
  const bool cb2 = true;
  const int ci1 = i;
  i = 1;
  i = ci1;
  c = 'c';
  c = cc1;
  b = true;
  bb = NULL;
  b = cb2;
  s = 12;
  l = 11111;
  i = l;
  ss = &s;
  l = s;
  s = i;
  i = c;
  return 1;
}
