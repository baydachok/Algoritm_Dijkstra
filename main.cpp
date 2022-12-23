/*
 * Составить программу создания графа и реализовать процедуру для работы с
 * графом, определенную индивидуальным вариантом задания.
 *
 * Самостоятельно выбрать и реализовать способ представления графа в памяти.
 * В программе предусмотреть ввод с клавиатуры произвольного графа. В
 * вариантах построения остовного дерева также разработать доступный способ
 * (форму) вывода результирующего дерева на экран монитора.
 *
 *
 * Нахождение кратчайшего пути методом Дейкстра
 *
 * https://blog.skillfactory.ru/glossary/algoritm-dejkstry/
 */


#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Node {
public:
    string name;

    explicit Node(string name) : name(std::move(name)) {};
};

class Graph {
public:
    vector<Node> nodes;
    vector<vector<int>> matrix;

    void addNode(string name) {
        /*
         * Добавление узла в граф
         */
        Node* node = new Node(name);
        nodes.push_back(*node);
        matrix.resize(nodes.size());
        for (int i = 0; i < nodes.size(); i++) {
            matrix[i].resize(nodes.size());
        }
    }

    int getNodeIndex(string name) {
        /*
         * Получение индекса узла по его имени
         */
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].name == name) {
                return i;
            }
        }
        return -1;
    }


    void addEdge(string from, string to, int weight) {
        /*
         * Добавление ребра в граф
         */
        int fromIndex = getNodeIndex(from);
        int toIndex = getNodeIndex(to);
        if (fromIndex == -1 || toIndex == -1) {
            cout << "Node not found" << endl;
            return;
        }
        matrix[fromIndex][toIndex] = weight;
        matrix[toIndex][fromIndex] = weight;
    }

    void printMatrix() {
        /*
         * Вывод матрицы смежности
         */
        cout << "  ";
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i].name << " ";
        }
        cout << endl;
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i].name << " ";
            for (int j = 0; j < nodes.size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void find(string from, string to) {
        /*
         * Поиск кратчайшего пути
         */
        int fromIndex = getNodeIndex(from);
        int toIndex = getNodeIndex(to);
        if (fromIndex == -1 || toIndex == -1) {
            cout << "Node not found" << endl;
            return;
        }
        // Массив для хранения кратчайших расстояний от начальной вершины до всех остальных
        vector<int> distance(nodes.size(), INT32_MAX);

        // Массив для хранения предыдущих вершин
        vector<int> visited(nodes.size(), 0);
        vector<int> prev(nodes.size(), -1);

        // Начальная вершина
        distance[fromIndex] = 0;

        // Пока не пройдем все вершины
        for (int i = 0; i < nodes.size(); i++) {
            // Ищем вершину с минимальным расстоянием
            int minIndex = -1;
            int minDistance = INT32_MAX;
            for (int j = 0; j < nodes.size(); j++) {

                // Если вершина еще не пройдена и расстояние до нее меньше минимального
                if (!visited[j] && distance[j] < minDistance) {
                    minIndex = j;
                    minDistance = distance[j];
                }
            }

            // Если вершину не нашли, значит путь до нее невозможен
            if (minIndex == -1) {
                break;
            }

            // Помечаем вершину как пройденную
            visited[minIndex] = 1;

            // Обновляем расстояния до соседей
            for (int j = 0; j < nodes.size(); j++) {
                if (matrix[minIndex][j] != 0) {
                    if (distance[j] > distance[minIndex] + matrix[minIndex][j]) {
                        distance[j] = distance[minIndex] + matrix[minIndex][j];
                        prev[j] = minIndex;
                    }
                }
            }
        }

        // Выводим кратчайшие расстояния
        if (distance[toIndex] == INT32_MAX) {
            cout << "Path not found" << endl;
            return;
        }

        // Восстанавливаем путь
        vector<int> path;
        int index = toIndex;
        while (index != -1) {
            path.push_back(index);
            index = prev[index];
        }

        // Выводим путь
        cout << "Path: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << nodes[path[i]].name << " ";
        }
        cout << endl;
        cout << "Distance: " << distance[toIndex] << endl;
    }

    void printGraphviz() {
        /*
         * Вывод графа в формате Graphviz
         */
        cout << "graph {" << endl;
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = 0; j < nodes.size(); j++) {
                if (matrix[i][j] != 0 && i < j) {
                    cout << nodes[i].name << " -- " << nodes[j].name << " [label=" << matrix[i][j] << "]" << endl;
                }
            }
        }
        cout << "}" << endl;
    }
};


int main() {
    Graph graph;
    graph.addNode("L");
    graph.addNode("B");
    graph.addNode("A");
    graph.addNode("N");
    graph.addNode("G");
    graph.addNode("S");
    graph.addNode("R");
    graph.addNode("D");
    graph.addNode("M");

    graph.addEdge("L", "B", 7);
    graph.addEdge("B", "A", 27);
    graph.addEdge("L", "N", 10);
    graph.addEdge("B", "G", 9);
    graph.addEdge("G", "S", 11);
    graph.addEdge("A", "M", 15);
    graph.addEdge("N", "G", 8);
    graph.addEdge("N", "R", 31);
    graph.addEdge("R", "D", 32);
    graph.addEdge("S", "D", 17);
    graph.addEdge("S", "M", 15);
    graph.addEdge("D", "M", 21);

    // Текстовое меню со всеми командами
    string menu = "1. Add node\n"
        "2. Add edge\n"
        "3. Print matrix\n"
        "4. Find path\n"
        "5. Print graphviz\n"
        "6. Exit\n";


    while (true) {
        cout << menu;
        int command;
        cin >> command;
        switch (command) {
        case 1: {
            string name;
            cout << "Enter node name: ";
            cin >> name;
            graph.addNode(name);
            break;
        }
        case 2: {
            string from, to;
            int weight;
            cout << "Enter from: ";
            cin >> from;
            cout << "Enter to: ";
            cin >> to;
            cout << "Enter weight: ";
            cin >> weight;
            graph.addEdge(from, to, weight);
            break;
        }
        case 3: {
            graph.printMatrix();
            break;
        }
        case 4: {
            string from, to;
            cout << "Enter from: ";
            cin >> from;
            cout << "Enter to: ";
            cin >> to;
            graph.find(from, to);
            break;
        }
        case 5: {
            graph.printGraphviz();
            break;
        }
        case 6: {
            return 0;
        }
        default: {
            cout << "Unknown command" << endl;
        }
        }
    }
}