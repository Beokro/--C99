// result should be 14103
struct temp {
  int a;
  int b;
  char c;
};

int main() {
  int a = 3;
  int * b = &a;
  int * c = &*b;
  int d[ 2 ] = { 100, 200 };
  int * e = &d[ 0 ];
  int f[ 2 ][ 2 ] = { { 1000, 2000 }, { 3000, 4000 } };
  struct temp g;
  g.a = 10000;
  *c = *c + *e;
  e = &f[ 1 ][ 1 ];
  *c = *c + *e;
  e = &g.a;
  return *c + *e;
}
