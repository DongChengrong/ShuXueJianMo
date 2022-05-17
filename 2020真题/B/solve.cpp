#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

int s, t;  //起点与终点
int cap, money, income, day, deadline;  //负载上限、初始资金、基础收入、总天数、最后期限
int f[3], w[3];  //食物和水在三种天气情况下的消耗，依次存储晴朗、高温、沙暴
int w_f, w_w, m_f, m_w;  //食物和水的重量、食物和水的基准价格
int weather[100], village[200], mine[200];  //分别存储天气状况，是否是村庄，是否是矿场
queue<int> q;
vector<int> G[100];  //用于存储无向图

//队列中使用的数据结构
typedef struct Node
{
    int W,M,w,f;
    vector<int> path;  //变长数组保存路径
    Node(W,M,w,f)   //构造方法，主要是在初始化时计算day
    {
        this->W = W;
        this->M = M;
        this->w = w;
        this->f = f;
    }
} Node;


//初始化
void init(){
    //预处理部分
    //从input_1.in中读取数据
    freopen("C:\\数学建模\\2020真题\\B\\input_1.in", "r", stdin);
    while(!q.empty()) q.pop();  //清空队列
    memset(weather, 0, sizeof(weather));
    //读入数据
    int i, j; //用于临时存储数据
    scanf("%d%d%d%d", &cap, &money, &income, &deadline);
    scanf("%d%d%d%d%d", &w_w, &m_w, &w[0], &w[1], &w[2]);
    scanf("%d%d%d%d%d", &w_f, &m_f, &f[0], &f[1], &f[2]);
    scanf("%d%d", &s, &t);
    scanf("%d", &i); while (i--) { scanf("%d", &j); village[j] = 1; }
    scanf("%d", &i); while (i--) { scanf("%d", &j); mine[j] = 1; }
    scanf("%d", &i);
    while(i--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    scanf("%d", &day);
    for (int i = 0; i < day; ++i) {
        scanf("%d", &weather[i]);
    }
}

//解决问题的算法
void solve(){
}

//输出结果
void print(){
}

int main(){
    init();
    solve();
    print();
}
