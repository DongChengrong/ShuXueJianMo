#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

int s, t;  //������յ�
int cap, money, income, day, deadline;  //�������ޡ���ʼ�ʽ𡢻������롢���������������
int f[3], w[3];  //ʳ���ˮ��������������µ����ģ����δ洢���ʡ����¡�ɳ��
int w_f, w_w, m_f, m_w;  //ʳ���ˮ��������ʳ���ˮ�Ļ�׼�۸�
int weather[100], village[200], mine[200];  //�ֱ�洢����״�����Ƿ��Ǵ�ׯ���Ƿ��ǿ�
queue<int> q;
vector<int> G[100];  //���ڴ洢����ͼ

//������ʹ�õ����ݽṹ
typedef struct Node
{
    int W,M,w,f;
    vector<int> path;  //�䳤���鱣��·��
    Node(W,M,w,f)   //���췽������Ҫ���ڳ�ʼ��ʱ����day
    {
        this->W = W;
        this->M = M;
        this->w = w;
        this->f = f;
    }
} Node;


//��ʼ��
void init(){
    //Ԥ������
    //��input_1.in�ж�ȡ����
    freopen("C:\\��ѧ��ģ\\2020����\\B\\input_1.in", "r", stdin);
    while(!q.empty()) q.pop();  //��ն���
    memset(weather, 0, sizeof(weather));
    //��������
    int i, j; //������ʱ�洢����
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

//���������㷨
void solve(){
}

//������
void print(){
}

int main(){
    init();
    solve();
    print();
}
