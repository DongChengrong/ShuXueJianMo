#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

//�洢��Ҫ��·����Ϣ
//����ֱ�ӽ���ǿ������ת��ʵ�ָ�ֵ
struct Node2 {
    int cur,M,w,f;
};


//������ʹ�õ����ݽṹ
struct Node
{
    int W,M,w,f;
    vector<Node2> path;  //�䳤���鱣��·��
    Node(int W,int M,int w,int f)   //���췽��
    {
        this->W = W;
        this->M = M;
        this->w = w;
        this->f = f;
    }
} ;

int s, t;  //������յ�
int cap, money, income, day, deadline;  //�������ޡ���ʼ�ʽ𡢻������롢���������������
int f[3], w[3];  //ʳ���ˮ��������������µ����ģ����δ洢���ʡ����¡�ɳ��
int w_f, w_w, m_f, m_w;  //ʳ���ˮ��������ʳ���ˮ�Ļ�׼�۸�
int weather[100], village[200], mine[200];  //�ֱ�洢����״�����Ƿ��Ǵ�ׯ���Ƿ��ǿ�
queue<Node> q;
vector<int> G[100];  //���ڴ洢����ͼ

//��ʼ��
void init(){
    //Ԥ������
    //��input_1.in�ж�ȡ����
    freopen("C:\\��ѧ��ģ\\ShuXueJianMo\\2020����\\B\\input_1.in", "r", stdin);
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

//�������Ĺ���
//����·����·���洢�ڱ䳤����(����)��
vector<Node2> solve(){
    int tmp = min(cap / (f[0] * w_f + w[0] *w_w) , money /(f[0] *m_f + w[0]* m_w)); //����ʳ�����
    Node start = Node(cap, money - tmp * (f[0] * m_f + w[0] * m_w), f[0] * tmp, w[0] * tmp);
    start.path.push_back((Node2){s,start.M, start.w,start.f});
    q.push(start);
    while (!q.empty()) {   //���й����������
        Node node = q.front(); q.pop();   //ȡ�����ж���Ԫ��
        int id = node.path[node.path.size()-1].cur;   //�õ�����λ��
        int day = node.path.size() - 1;  //��Ϊÿ�춼����һ���ڵ㣬���Կ��Խ���path��������
        if (day == deadline + 2) return vector<Node2>();  //����δ�������ؿ�����
        if (id == t) return node.path;   //�ִ��յ�
        if (village[id]) {  //�ڴ�ׯ���򲹸�
            tmp = min(cap / (f[0] * w_f + w[0] *w_w) , node.M /(f[0] * m_f * 2+ w[0]* m_w * 2));
            node.M = node.M - tmp * (f[0] * m_f + w[0] * m_w);
        }
        for (int i = 0; i < G[id].size(); ++i) {   //�ƶ�
            Node new_node = node;
            if (weather[day] == 2) {  //����ɳ��������ԭ��פ��
                new_node.f -= f[2];
                new_node.w -= w[2];
                if (new_node.f < 0 || new_node.w < 0) {  //��Դ�ľ��������ýڵ�
                    break;
                }
                new_node.path.push_back((Node2){id, new_node.M, new_node.w, new_node.f});
                q.push(new_node);
                break;
            } else {  //��ɳ�������������ƶ�
                new_node.f -= f[weather[day]] * 2;
                new_node.w -= w[weather[day]] * 2;
                if (new_node.f < 0 || new_node.w < 0) {
                    continue;
                }
                new_node.path.push_back((Node2){G[id][i], new_node.M,new_node.w, new_node.f});
                q.push(new_node);
            }
        }
        if (mine[id]) {   //�����󳡣������ڿ����
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

//������
void print(vector<Node2> path){
    if (path.empty()) {
        puts("Game Over!"); return;
    }
    puts("���� λ�� �ʽ� ʳ�� ˮ");
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
