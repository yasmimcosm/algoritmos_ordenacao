#include <bits/stdc++.h>

using namespace std;

// Counting sort auxiliar
static void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // De trás pra frente para manter a estabilidade
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

// Radix Sort LSD (base 10) para inteiros NÃO negativos.
// Complexidade: O(d * (n + b)), onde d = nº de dígitos do maior valor e b = 10.
void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    for (long long exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(arr, (int)exp);
}

int main() {
    vector<int> v = {170, 45, 75, 90, 802, 24, 2, 66};

    radixSort(v);

    for (int x : v)
        cout << x << " ";
    cout << endl;

    return 0;
}