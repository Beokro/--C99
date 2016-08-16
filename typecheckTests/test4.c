// and, or 2 bool/ const bool
// pointer + number, pointer - number, number might be const
// ! with a non bool
int main() {
  bool a = true, b = false;
  const bool c = a, d = b;
  if ( ( a && b ) || ( c || d ) ) {
    a = d;
  }
  const long l = 5;
  const short s = l;
  bool * ap = &a;
  bool * bp = ap + l;
  bp = l + ap;
  bp = ap -s;
  bp = l - ap; // undefine behavior
  *bp = a;
  *bp = !l;
  return 0;
}
