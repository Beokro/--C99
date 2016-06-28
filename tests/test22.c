struct list_node{
  struct list_node* prev;
  struct list_node* next;
  int test = 10;
  void* value;
};


int main(){
  struct list_node a;
  a.test = 5;
  if(a.test == 5 ){
    return 1;
  }
  return 0;
}
