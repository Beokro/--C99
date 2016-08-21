// function assignment that has different type on both side
char test() {
  return 'c';
}

int main() {
  char c = test();
  int a = test();
  return 1;
}
