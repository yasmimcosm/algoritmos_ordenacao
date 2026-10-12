#include <bits/stdc++.h>

using namespace std;

// Counting Sort estável, aceita números negativos.
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(arr.size());

    // Conta as ocorrências de cada valor
    for (int x : arr)
        count[x - minVal]++;

    // Soma acumulada: count[i] passa a ser a posição final do elemento
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    // Percorre de trás pra frente para manter a estabilidade
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    arr = output;
}