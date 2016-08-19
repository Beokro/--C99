// function assignment that has the same type on both side
// in for's init, assign const to non const type
// += -= /= *= %= ^= &= |=, >>=, <<= ++, -- non-const number type
// function assignment fail on const type

char testChar( int a ) {
  return 'c';
}

int testInt( char c ) {
  long l = 5;
  return l;
}

int main() {
  const int a = 5;
  const bool bo = true;
  int b = a;
  char c = testChar( a );
  b = testInt( c );
  for( int i = a; i>0; i-- ) {
    i-=2;
  }
  for( bool boo = bo; boo; b-- ) {
    b-=2;
  }
  b+=1;
  b-=1;
  b/=1;
  b*=1;
  b%=1;
  b^=1;
  b&=1;
  b|=1;
  b>>=1;
  b<<=1;
  b++;
  b--;
  a = testInt( c );
  return 1;
}
