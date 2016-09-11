int main() {
  int a = 78;
  int b = 0;
  switch ( a ) {
  case 50 : b += 10;
  case 70 : b += 100;
  case 78 : b += 1000;
  case 1000 : b += 10000;
  default: b++;
  }
  return b;
}
