// not all number * / ^ & %
int main() {
  int a = 3;
  long l = 111111;
  short s = 12;
  char c = 's';
  a = l * s / s ^ l % a;
  a = l * s / s ^ c % a;
  return 1;
}
