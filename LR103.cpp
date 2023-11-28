#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <cstring>
#include <locale>

using namespace std;

void breadthFirstSearch(const vector<vector<int>>& graph, int start_vertex, vector<int>& distances) {
    queue<int> Q;
    Q.push(start_vertex);
    distances[start_vertex] = 0;

    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for (int i = 0; i < graph[current].size(); ++i) {
            if (graph[current][i] > 0 && distances[i] == -1) {
                Q.push(i);
                distances[i] = distances[current] + graph[current][i];
            }
        }
    }
}

void dijkstra(const vector<vector<int>>& graph, int start_vertex, vector<int>& distances) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start_vertex });
    distances[start_vertex] = 0;

    while (!pq.empty()) {
        int current = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (cost > distances[current]) continue;

        for (int i = 0; i < graph[current].size(); ++i) {
            if (graph[current][i] > 0 && distances[i] > distances[current] + graph[current][i]) {
                distances[i] = distances[current] + graph[current][i];
                pq.push({ distances[i], i });
            }
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RUS");

    int isWeighted = 0;
    int isDirected = 0;

    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            if (strcmp(argv[i], "-w") == 0)
                isWeighted = 1;

            if (strcmp(argv[i], "-o") == 0)
                isDirected = 1;
        }
    }

    if (argc != 3) {
        printf("Укажите параметры графа (взвешенный и ориентированный или нет (1 или 0)):\n");
        scanf("%d", &isWeighted);
        scanf("%d", &isDirected);
    }
    else {
        isWeighted = atoi(argv[1]);
        isDirected = atoi(argv[2]);
    }

    if ((isWeighted != 0 && isWeighted != 1) || (isDirected != 0 && isDirected != 1)) {
        printf("Неверные параметры. Пожалуйста, следуйте инструкциям.\n");
        return 1;
    }

    int num_vertices;

    do {
        printf("Введите количество вершин в графе: ");
        scanf("%d", &num_vertices);
    } while (num_vertices <= 0);

    srand(static_cast<unsigned int>(time(nullptr)));

    vector<vector<int>> adjacency_matrix(num_vertices + 1, vector<int>(num_vertices + 1, 0));
    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = (isDirected ? 1 : i + 1); j <= num_vertices; ++j) {
            if (i != j && (rand() % 2) == 1) {
                if (isWeighted) {
                    adjacency_matrix[i][j] = rand() % 10 + 1;
                }
                else {
                    adjacency_matrix[i][j] = 1;
                }

                if (!isDirected) {
                    adjacency_matrix[j][i] = adjacency_matrix[i][j];
                }
            }
        }
    }

    printf("Матрица смежности:\n");
    for (int i = 1; i <= num_vertices; ++i) {
        for (int j = 1; j <= num_vertices; ++j) {
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }

    int start_vertex;

    do {
        printf("Введите начальную вершину (от 1 до %d): ", num_vertices);
        scanf("%d", &start_vertex);
    } while (start_vertex < 1 || start_vertex > num_vertices);

    vector<int> distances(num_vertices + 1, INT_MAX);

    if (isWeighted && isDirected) {
        printf("Поиск кратчайшего пути с помощью алгоритма Дейкстры\n");
        dijkstra(adjacency_matrix, start_vertex, distances);
    }
    else {
        printf("Поиск кратчайшего пути с помощью обхода в ширину.\n");
        breadthFirstSearch(adjacency_matrix, start_vertex, distances);
    }

    return 0;
}
