// dot access a struct with member that it does not have
struct s1 {
  int a;
  int b;
  char c;
};
enum color { red, blue, green };
enum color2 { yellow, white };
int main() {
  color e1 = red, e2 = blue;
  color2 e3 = yellow;
  e1 = e2;
  e1 = green;
  struct s1 ss1;
  ss1.d = 1;

  return 1;
}
