#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

//存储需要的路径信息
//可以直接借助强制类型转换实现赋值
struct Node2 {
    int cur,M,w,f;
};


//队列中使用的数据结构
struct Node
{
    int W,M,w,f;
    vector<Node2> path;  //变长数组保存路径
    Node(int W,int M,int w,int f)   //构造方法
    {
        this->W = W;
        this->M = M;
        this->w = w;
        this->f = f;
    }
} ;

int s, t;  //起点与终点
int cap, money, income, day, deadline;  //负载上限、初始资金、基础收入、总天数、最后期限
int f[3], w[3];  //食物和水在三种天气情况下的消耗，依次存储晴朗、高温、沙暴
int w_f, w_w, m_f, m_w;  //食物和水的重量、食物和水的基准价格
int weather[100], village[200], mine[200];  //分别存储天气状况，是否是村庄，是否是矿场
queue<Node> q;
vector<int> G[100];  //用于存储无向图

//初始化
void init(){
    //预处理部分
    //从input_1.in中读取数据
    freopen("C:\\数学建模\\ShuXueJianMo\\2020真题\\B\\input_1.in", "r", stdin);
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

//解决问题的过程
//返回路径，路径存储在变长数组(链表)中
vector<Node2> solve(){
    int tmp = min(cap / (f[0] * w_f + w[0] *w_w) , money /(f[0] *m_f + w[0]* m_w)); //购买食物份数
    Node start = Node(cap, money - tmp * (f[0] * m_f + w[0] * m_w), f[0] * tmp, w[0] * tmp);
    start.path.push_back((Node2){s,start.M, start.w,start.f});
    q.push(start);
    while (!q.empty()) {   //进行广度优先搜索
        Node node = q.front(); q.pop();   //取出队列顶部元素
        int id = node.path[node.path.size()-1].cur;   //得到所在位置
        int day = node.path.size() - 1;  //因为每天都会存放一个节点，所以可以借助path计算日期
        if (day == deadline + 2) return vector<Node2>();  //逾期未至，返回空数组
        if (id == t) return node.path;   //抵达终点
        if (village[id]) {  //在村庄购买补给
            tmp = min(cap / (f[0] * w_f + w[0] *w_w) , node.M /(f[0] * m_f * 2+ w[0]* m_w * 2));
            node.M = node.M - tmp * (f[0] * m_f + w[0] * m_w);
        }
        for (int i = 0; i < G[id].size(); ++i) {   //移动
            Node new_node = node;
            if (weather[day] == 2) {  //遇到沙暴天气，原地驻留
                new_node.f -= f[2];
                new_node.w -= w[2];
                if (new_node.f < 0 || new_node.w < 0) {  //资源耗尽，丢弃该节点
                    break;
                }
                new_node.path.push_back((Node2){id, new_node.M, new_node.w, new_node.f});
                q.push(new_node);
                break;
            } else {  //非沙暴天气，进行移动
                new_node.f -= f[weather[day]] * 2;
                new_node.w -= w[weather[day]] * 2;
                if (new_node.f < 0 || new_node.w < 0) {
                    continue;
                }
                new_node.path.push_back((Node2){G[id][i], new_node.M,new_node.w, new_node.f});
                q.push(new_node);
            }
        }
        if (mine[id]) {   //遇到矿场，进行挖矿操作
            node.f -= f[weather[day]] * 3;
            node.w -= f[weather[day]] * 3;
            node.M += income;
            if (node.f < 0 || node.w < 0) {
                continue;
            } else {
                node.path.push_back((Node2){id, node.M, node.w, node.f});
                q.push(node);
            }
        }
    }
}

//输出结果
void print(vector<Node2> path){
    if (path.empty()) {
        puts("Game Over!"); return;
    }
    puts("日期 位置 资金 食物 水");
    for (int i = 0; i < path.size(); ++i) {
        Node2 node = path[i];
        printf("%d %d %d %d %d\n", i, node.cur,node.M,node.f,node.w);
    }
}

int main(){
    init();
    //puts("111111111111");
    vector<Node2> path = solve();
    print(path);
}
