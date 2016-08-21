// in for loop's init, use a variable that has not been defined
int main() {
  int a = 0;
  for ( a = 1; a >0; a++ ) {
    a--;
  }
  for ( b = 1; a >0; a++ ) {
    a--;
  }
  return 1;
}
