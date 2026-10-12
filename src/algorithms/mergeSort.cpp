#include <bits/stdc++.h>
#include <cctype>

// Merge sort auxiliar
void merge(vector<int>& v, int inicio, int meio, int fim) {
    vector<int> aux;

    int i = inicio;
    int j = meio + 1;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) {
            aux.push_back(v[i]);
            i++;
        } else {
            aux.push_back(v[j]);
            j++;
        }
    }

    while (i <= meio) {
        aux.push_back(v[i]);
        i++;
    }

    while (j <= fim) {
        aux.push_back(v[j]);
        j++;
    }

    for (int k = 0; k < aux.size(); k++) {
        v[inicio + k] = aux[k];
    }
}

void mergeSort(vector<int>& v, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    mergeSort(v, inicio, meio);
    mergeSort(v, meio + 1, fim);

    merge(v, inicio, meio, fim);
}