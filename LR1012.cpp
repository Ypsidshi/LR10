#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include <clocale>

#define MAX_NODES 500

// Функция для генерации случайной матрицы смежности
void generateRandomGraph(int graph[MAX_NODES][MAX_NODES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0; // Нет петель
            }
            else {
                int random_value = rand() % 2; // Генерируем 0 или 1
                graph[i][j] = random_value;
                graph[j][i] = random_value; // Граф неориентированный
            }
        }
    }
}

// Функция для поиска расстояний в графе с использованием BFS
void bfs(int graph[MAX_NODES][MAX_NODES], int n, int startNode) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // Выводим расстояния от startNode до всех остальных узлов
    for (int i = 0; i < n; i++) {
        printf("Расстояние от ребра %d до ребра %d: %d\n", startNode, i, distances[i]);
    }
}

// Функция для определения эксцентриситета вершины
int findEccentricity(int graph[MAX_NODES][MAX_NODES], int n, int vertex) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // Находим максимальное расстояние (эксцентриситет)
    int eccentricity = 0;
    for (int i = 0; i < n; i++) {
        if (distances[i] > eccentricity) {
            eccentricity = distances[i];
        }
    }

    return eccentricity;
}

// Функция для определения радиуса графа
int findRadius(int graph[MAX_NODES][MAX_NODES], int n) {
    int minEccentricity = INT_MAX;

    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity < minEccentricity) {
            minEccentricity = eccentricity;
        }
    }

    return minEccentricity;
}

// Функция для определения диаметра графа
int findDiameter(int graph[MAX_NODES][MAX_NODES], int n) {
    int maxEccentricity = 0;

    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity > maxEccentricity) {
            maxEccentricity = eccentricity;
        }
    }

    return maxEccentricity;
}

// Функция для определения центральных вершин
void findCentralVertices(int graph[MAX_NODES][MAX_NODES], int n, int radius) {
    printf("Центральные вершины (эксцентриситет равен радиусу графа):\n");
    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity == radius) {
            printf("%d\n", i);
        }
    }
}

// Функция для определения периферийных вершин
void findPeripheralVertices(int graph[MAX_NODES][MAX_NODES], int n, int diameter) {
    printf("Периферийные вершины (эксцентриситет равен диаметру графа):\n");
    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity == diameter) {
            printf("%d\n", i);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL)); // Инициализируем генератор случайных чисел

    int n; // Количество узлов в графе
    printf("Введите размерность матрицы: ");
    scanf("%d", &n);

    int graph[MAX_NODES][MAX_NODES] = { 0 };

    generateRandomGraph(graph, n);

    // Выводим матрицу смежности
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    int startNode;
    printf("Введите начальный узел для поиска расстояний: ");
    scanf("%d", &startNode);

    bfs(graph, n, startNode);

    // Определение радиуса и диаметра
    int radius = findRadius(graph, n);
    int diameter = findDiameter(graph, n);

    printf("Радиус графа: %d\n", radius);
    printf("Диаметр графа: %d\n", diameter);

    // Определение центральных и периферийных вершин
    findCentralVertices(graph, n, radius);
    findPeripheralVertices(graph, n, diameter);


    return 0;
}