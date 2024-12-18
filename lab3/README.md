6. Dijkstra算法（dijkstra 函数）
Dijkstra算法用于计算图中从某个起点到所有其他顶点的最短路径。其主要思想是逐步扩展已知的最短路径集合，每次选择距离起点最近的未访问顶点，更新其邻接点的最短路径。

在程序中，dijkstra 函数接受三个参数：

start：起始景点的编号。
dist[]：存储每个景点从起始景点的最短距离。
path[]：存储每个景点的前驱节点，用于回溯最短路径。

算法步骤：
初始化：

将源点的距离设置为0，其他所有点的距离设置为无穷大。
初始化一个“已访问”集合，用来记录已确定最短路径的点。
选择未访问的点：

每次选择一个距离源点最近的未访问点（即当前最小的距离）。
对于这个点，检查它所有的邻居节点，如果通过它到达邻居节点的路径更短，就更新邻居节点的最短路径。
重复：

重复上述步骤，直到所有点的最短路径都确定为止。
输出结果：

当所有点的最短路径都确定后，可以输出源点到其他所有点的最短路径。
