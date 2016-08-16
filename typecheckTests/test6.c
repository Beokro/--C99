// address of anything but 2d array ( test const type )
// deference of pointer, array, rhs and lhs
// declare a enum collection with type name
// declare a enum collection with type name
// declare a enum colection without type name
// enum collection with same name
enum color { red, blue, yellow };
enum { yes, no };
int main(){
  enum color { red, blue, yellow };
  bool b = true;
  const bool cb = b;
  bool * bp = &b;
  bp = &cb;
  *bp = b;
  char a[] = {'a','b'};
  char aa[1][1] = { {'a'} };
  *a = 'c';
  const char cc = *a;
  enum color { red1, blue1, yellow1 };
  return 0;
}
