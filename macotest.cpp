#define HELLO 7
#define OHELLO 7 + 8 * 5		
#define testxy ({\
      int _z = x + y;\
      _z; })

int main(){
  testxy;
  HELLO + OHELLO;
  return OHELLO ;
}
