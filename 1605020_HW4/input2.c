int f(int a,int b,int c){
    if(a==1) return 1;
    return a*f(a-1,1,2);
}

int g(){

    int a;
    int b;
}

int main(){
    int x,y;
    y=6;
    x=f(y,2,3);
    println(x);
    return 0;
}
