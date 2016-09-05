char main() {
  char c[ 2 ][ 3 ] = { { 'a', 'b', 'c' }, { 'd', 'e', 'f' } };
  char cc = c[ 0 ][ 2 ];
  c[ 1 ][ 2 ] = cc;
  return c[ 1 ][ 2 ];
}
