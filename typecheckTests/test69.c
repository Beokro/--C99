// struct with base type
struct s1 {
  int a;
  int b;
  char c;
};
enum color { red, blue, green };

int main() {
  struct s1 ss1;
  struct s1 ss2 = ss1;
  struct s2 ss3;
  ss1 = ss2;
  ss1.a = 2;
  ss1.c = 'c';
  color e1 = red, e2 = blue;
  e1 = e2;
  ss1 = 2;

  return 1;
}
