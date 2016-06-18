int main(){
  int * a;
  int b = 100;
  a = &b;
  a = b;

  if(a == b)
    return 1;
  return 0;
}
