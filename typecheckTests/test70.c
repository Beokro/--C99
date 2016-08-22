// enum with different type
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
  e2 = e3;
  e2 = white;

  return 1;
}
