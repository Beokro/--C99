// ^= &= |=, >>=, <<= ++, -- const number type and pointer, char, bool, array type
int main() {
  char cc = 'c';
  char *c = &cc;
  c ^= 1;
  c >>= 1;
  c++;
  return 1;
}
