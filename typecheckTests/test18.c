// deference a base/struct type
int main() {
  const char c = 'c';
  char * cp = &c;
  c = *c;
  return 1;
}
