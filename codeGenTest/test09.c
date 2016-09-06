// expect result is 6
int main() {
  int a = 3;
  a++;
  a++;
  a--;
  ++a;
  --a;
  ++a;
  int b = 4;
  a &= b;
  a ^= 4;
  a |= 2;
  a *= 4;
  a += 1000;
  a -= 700;
  a /= 150;
  a <<= 5;
  a >>= 1;
  a %= 13;
  return a;
}
