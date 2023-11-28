#define _CRT_SECURE_NO_WARNINGS
#include <clocale>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Функция для поиска минимального расстояния
int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


// Функция для вывода матрицы смежности
void printMatrix(int** graph, int V) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Функция для вывода результатов поиска расстояний
void printSolution(int dist[], int V) {
    printf("Вершина \t Расстояние от начальной вершины\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Функция для реализации поиска расстояний в графе
void dijkstra(int** graph, int src, int V, int* dist) {
    int* sptSet = (int*)malloc(V * sizeof(int)); // Массив для отслеживания посещенных вершин

    // Инициализация массива расстояний и массива посещенных вершин
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Расстояние от начальной вершины до неё самой равно 0
    dist[src] = 0;

    // Поиск кратчайшего пути для всех вершин
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);

        // Помечаем выбранную вершину как посещенную
        sptSet[u] = 1;

        // Обновляем значения расстояний для соседей выбранной вершины
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    free(sptSet);
}

// Функция для определения радиуса графа
int findRadius(int** graph, int V) {
    int minEccentricity = INT_MAX;

    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);

        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance < minEccentricity) {
            minEccentricity = maxDistance;
        }

        free(dist);
    }

    return minEccentricity;
}

// Функция для определения диаметра графа
int findDiameter(int** graph, int V) {
    int maxEccentricity = 0;

    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);

        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance > maxEccentricity) {
            maxEccentricity = maxDistance;
        }

        free(dist);
    }

    return maxEccentricity;
}

// Функция для определения центральных вершин
void findCentralVertices(int** graph, int V, int radius) {
    printf("Центральные вершины (эксцентриситет равен радиусу графа):\n");
    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);
        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance == radius) {
            printf("%d\n", i);
        }

        free(dist);
    }
}

// Функция для определения периферийных вершин
void findPeripheralVertices(int** graph, int V, int diameter) {
    printf("Периферийные вершины (эксцентриситет равен диаметру графа):\n");
    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);
        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance == diameter) {
            printf("%d\n", i);
        }

        free(dist);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int V; // Количество вершин
    printf("Введите количество вершин в графе: ");
    scanf("%d", &V);

    // Создание графа и автоматическое заполнение матрицы смежности
    int** graph = (int**)malloc(V * sizeof(int*));

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0; // Расстояние от вершины до самой себя
            }
            else {
                // Заполняем случайными весами от 1 до 10
                graph[i][j] = rand() % 10 + 1;
            }
        }
    }

    printMatrix(graph, V);

    // Создание матрицы для хранения расстояний
    int* dist = (int*)malloc(V * sizeof(int));

    // Выбор начальной вершины для поиска расстояний
    int source;
    printf("Введите начальную вершину для поиска расстояний: ");
    scanf("%d", &source);

    // Выполнение поиска расстояний для одной из вершин (можно выбрать любую)
    dijkstra(graph, source, V, dist);

    // Вывод результатов
    printSolution(dist, V);

    // Определение радиуса и диаметра
    int radius = findRadius(graph, V);
    int diameter = findDiameter(graph, V);

    printf("Радиус графа: %d\n", radius);
    printf("Диаметр графа: %d\n", diameter);

    // Определение центральных и периферийных вершин
    findCentralVertices(graph, V, radius);
    findPeripheralVertices(graph, V, diameter);

    // Освобождение выделенной памяти
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    free(dist);

    return 0;
}