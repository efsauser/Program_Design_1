#include <stdio.h>
# define mask 0x80000000
//下面這個是Lec6已經做過的全加器，後面會用到
int full_adder_c(int a, int b ,int c) {
     return (a&b)|(b&c)|(a&c); // a,b,c其中兩個為1，輸出就為1
}

int full_adder_x(int a, int b, int c) {
     return (a^b)^c; // 2進位加法跟XOR差不多
}

void print_bit(int num[]){
    for(int i=0; i<32; i++){
        printf("%d", num[i]);
        if((i+1)%8==0)
            printf(" ");
    }
}

int main(){
    float a,b;
    int c=0; //used by full_adder
    int n1[32], n2[32], sum[32];
    unsigned ans=0;
    /*下面這個十分技巧的作法是我從網路上學到的
      原理簡單講就是強迫編譯器用解讀unsigned位元的方式來解讀float的位元*/
    scanf("%f %f",&a,&b);
    unsigned u1, u2;
    u1 = *(unsigned*)&a;
    u2 = *(unsigned*)&b;
    for(int i=0; i<32; i++){
        n1[i] = (u1&(mask>>i))>>(31-i); //更聰明的寫法是n1[i] = (u1&(mask>>i))!=0U;
        n2[i] = (u2&(mask>>i))>>(31-i); 
    }
    //全加器在助教給的Loader code是這樣運作的，方向由左往右
    for(int i=0; i<32; i++){
        sum[31-i] = full_adder_x(n1[31-i], n2[31-i], c);
        c = full_adder_c(n1[31-i], n2[31-i], c);
    }
    for(int i=0; i<32; i++)
        ans |= ((0x1&sum[31-i])<<i);
    //符合題目格式的輸出
    printf("   ");
    print_bit(n1);
    printf("\n+) ");
    print_bit(n2);
    printf("\n---------------------------------------\n");
    printf("   ");
    print_bit(sum);
    printf("\n%d + %d = %d", (int)a, (int)b, ans);//這裡做了implicit conversions
    return 0;
}
