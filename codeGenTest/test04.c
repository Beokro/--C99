// assign 2d list to 2d array, do the access
// assign it back to array
// reutrn 2d array access
short main() {
  int a[ 2 ][ 2 ] = { { 0, 1 }, { 3, 5 } };
  a[ 1 ][ 0 ] = 100;
  return a[ 1 ][ 0 ];
}
