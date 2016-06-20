int main(){
  int x[][2] ={
    { 1, 11 },
    { 2, 22 },
    { 3, 33 }
  };

  int col = 2, row = 3;
  for (int r = 0; r < row; r++){
    for (int c = 0; c < col; c++){
      printf("x[%d][%d] = %d\n", r, c, x[r][c]);
    }
  }

  int y[2][2] = {
    {2,2},
    {3,3}
  };
  return 1;
}
