// expect 97
struct temp {
  int a;
  int b;
  char c;
};

char main() {
  struct temp st;
  st.a = 2;
  st.b = 3;
  st.c = 'a';
  char cc = st.c;
  return cc;
}
