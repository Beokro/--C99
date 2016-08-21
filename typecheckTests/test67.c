// function assignment fail on const type
int test() {
  return 1;
}

int main() {
  const int a = test();
  a = test();
  return 1;
}
