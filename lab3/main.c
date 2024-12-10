#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999999  // 用一个大数表示路径不存在
#define MAX_V 20       // 最大景点数量

// 景点结构体
typedef struct {
    char name[50];  // 景点名称
    char code[10];  // 景点代号
    char description[200];  // 景点简介
} Spot;

// 图结构体，使用邻接矩阵表示
typedef struct {
    int matrix[MAX_V][MAX_V];  // 邻接矩阵
    int numVertices;  // 图中顶点的数量
    Spot spots[MAX_V];  // 存储景点信息
} Graph;

// 初始化图
void initGraph(Graph *g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                g->matrix[i][j] = 0;  // 自己到自己距离为0
            } else {
                g->matrix[i][j] = INF;  // 初始化为INF，表示没有路径
            }
        }
    }
}

// 添加景点
void addSpot(Graph *g, int index, const char *name, const char *code, const char *description) {
    strcpy(g->spots[index].name, name);
    strcpy(g->spots[index].code, code);
    strcpy(g->spots[index].description, description);
}

// 添加路径（边）
void addPath(Graph *g, int from, int to, int length) {
    g->matrix[from][to] = length;
    g->matrix[to][from] = length;  // 假设路径是双向的
}

// 打印景点信息
void printSpotInfo(Graph *g, int index) {
    printf("景点名称: %s\n", g->spots[index].name);
    printf("景点代号: %s\n", g->spots[index].code);
    printf("景点简介: %s\n", g->spots[index].description);
}

// Dijkstra算法计算最短路径
void dijkstra(Graph *g, int start, int dist[], int path[]) {
    int visited[MAX_V] = {0};  // 记录已访问的顶点
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < g->numVertices; i++) {
        int minDist = INF, u = -1;
        for (int j = 0; j < g->numVertices; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // 没有未访问的点了
        visited[u] = 1;

        for (int v = 0; v < g->numVertices; v++) {
            if (g->matrix[u][v] != INF && dist[u] + g->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->matrix[u][v];
                path[v] = u;
            }
        }
    }
}

// 打印最短路径
void printPath(int path[], int start, int end) {
    if (end == start) {
        printf("%d", start);
        return;
    }
    if (path[end] == -1) {
        printf("没有路径\n");
        return;
    }
    printPath(path, start, path[end]);
    printf(" -> %d", end);
}

int main() {
    Graph g;
    int numVertices = 10;  // 假设有10个景点

    initGraph(&g, numVertices);

    // 添加景点
    addSpot(&g, 0, "教学楼", "A1", "主要用于上课和学术活动的建筑。");
    addSpot(&g, 1, "图书馆", "B2", "提供书籍和期刊的地方，适合阅读和学习。");
    addSpot(&g, 2, "操场", "C3", "供学生运动、体育活动使用的场地。");
    addSpot(&g, 3, "食堂", "D4", "提供早餐、午餐和晚餐的餐厅。");
    addSpot(&g, 4, "学生宿舍", "E5", "为学生提供住宿的地方。");
    addSpot(&g, 5, "行政楼", "F6", "处理学校行政事务的办公楼。");
    addSpot(&g, 6, "体育馆", "G7", "进行大型体育活动和赛事的场地。");
    addSpot(&g, 7, "医务室", "H8", "为学生提供医疗服务的地方。");
    addSpot(&g, 8, "教学楼北", "I9", "教学楼的北侧，提供更多的教室和资源。");
    addSpot(&g, 9, "会议中心", "J10", "举行学术会议和活动的场所。");

    // 添加路径（双向）
    addPath(&g, 0, 1, 5);
    addPath(&g, 1, 2, 10);
    addPath(&g, 2, 3, 2);
    addPath(&g, 3, 4, 3);
    addPath(&g, 4, 5, 7);
    addPath(&g, 5, 6, 8);
    addPath(&g, 6, 7, 4);
    addPath(&g, 7, 8, 6);
    addPath(&g, 8, 9, 1);

    // 景点信息查询
    printf("请输入景点代号查询信息：");
    char code[10];
    scanf("%s", code);
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(g.spots[i].code, code) == 0) {
            printSpotInfo(&g, i);
            break;
        }
    }

    // 最短路径查询
    int start, end;
    printf("请输入起始景点编号和目标景点编号查询最短路径：");
    scanf("%d %d", &start, &end);

    int dist[MAX_V], path[MAX_V];
    dijkstra(&g, start, dist, path);
    printf("最短路径为: ");
    printPath(path, start, end);
    printf("\n");
    printf("路径长度为: %d\n", dist[end]);

    return 0;
}
