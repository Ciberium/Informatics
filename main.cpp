#include <iostream>
#include <vector>
using namespace std;


int countPermutations=2;


void printPath(vector<int> &path) {
    cout << "0";
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << "-" << *it;
    }
    cout << "-0";
}

int shortestPath(vector<vector<int>> &matrix, const vector<int> &path) {
    int distance = 0;
    distance += matrix[0][path[0]];
    for (int i = 1; i < path.size(); ++i) {
        distance += matrix[path[i - 1]][path[i]];
    }
    distance += matrix[path.back()][0];
    return distance;
}

void swap(vector<int> &path, int idx1, int idx2) {
    int temp = path[idx1];
    path[idx1] = path[idx2];
    path[idx2] = temp;
}


int generate_permutations(vector<vector<int>> &matrix, vector<int> &path, int start, int end, int minDistance) {
    if (start == end) {
        int currentDistance = shortestPath(matrix, path);
        printPath(path);
        countPermutations++;
        cout << " = " << currentDistance << endl;
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap(path,start, i);
            minDistance = generate_permutations(matrix, path, start + 1, end, minDistance);
            swap(path,start, i);//возвращаю в исходное состояние вектор
        }
    }
    return minDistance;
}

int main() {
    vector<vector<int>> matrix = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
    };
    int n = matrix.size();
    vector<int> path(n - 1);
    for (int i = 1; i < n; ++i) {
        path[i - 1] = i;
    }
    int minDistance = 100000;

    minDistance = generate_permutations(matrix, path, 0, path.size() - 1, minDistance);

    cout << "The shortest distance is " << minDistance << endl;
    cout<<"Count of permutations is "<<countPermutations<<endl;
    return 0;
}