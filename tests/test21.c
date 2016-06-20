int main(){
  int x[][2] =
    {
      { 1, 11 },
      { 2, 22 },
      { 3, 33 }
    };
  int len = sizeof(x) / sizeof(int);
  int* p = (int*)x;
  for (int i = 0; i < len; i++){
    printf("x[%d] = %d\n", i, p[i]);
  }
  if(x[5] == 33)
    return 1;
  return 0;
}
