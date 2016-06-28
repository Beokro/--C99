int main(){
  int x[][2] =
    {
      { 1, 11 },
      { 2, 22 },
      { 3, 33 }
    };
  int len = 6;
  int* p = x;
  for (int i = 0; i < len; i++){
    printf("x[%d] = %d\n", i, p[i]);
  }
  if(x[5] == 33){
    return 1;
  }
  return 0;
}
