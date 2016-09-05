char main() {
  char c[ 6 ] = { 'a', 'b', 'c', 'd', 'e', 'c' };
  char cc = c[ 5 ];
  c[ 0 ] = cc;
  return c[ 0 ];
}
