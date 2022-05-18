#include <stdio.h>

int main(){
    int cnt = 0;  //统计边的总数
    for (int i = 1; i <= 63; ++i){
        if (i + 8 <= 64) { printf("%d %d\n", i, i + 8); ++cnt; }
        if (i % 8 != 0) { printf("%d %d\n", i, i + 1); ++cnt; }
        if (i % 8 != 1 && i + 8 - 1 <= 64) { printf("%d %d\n", i, i + 8 -1); ++cnt; }
    }
    printf("%d\n", cnt);
    return 0;
}
