int main(){
    int i = 5;
    char c = 'a';
    long l = 0x124123;
    long long ll = 0x12331;
    
    ll = i+c;
    ll = c*l;
    ll = l/i;
    ll = ll+c;
    ll+= l;
    ll-= l ;
    return ll;
}