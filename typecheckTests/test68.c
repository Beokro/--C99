// assign struct with same struct type
// enum with same enum type
// deference pointer, 1d/2d array, do a assign
// struct with different type
struct s1 {
  int a;
  int b;
  char c;
};

struct s2 {
  int a;
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

  char a[ 1 ][ 2 ] = { { '1', '2' } };
  char b[ 2 ] = a[ 0 ];
  char c[] = a[ 1 ];

  ss3 = ss2;
  struct s2 ss4 = ss2;
  return 1;
}
