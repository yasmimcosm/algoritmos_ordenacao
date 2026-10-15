#include <bits/stdc++.h>

#include "json.hpp"
using json = nlohmann::json;

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
    // Abre o json com os vetores gerados
    std::ifstream arquivo_entrada("entrys.json");
    if (!arquivo_entrada.is_open()) {
      std::cerr << "Erro ao abrir o arquivo de vetores. Verifique se ele foi criado e se está neste diretorio" << "\n";
      return 1;
    }

    json data;
    arquivo_entrada >> data;
    arquivo_entrada.close();

    // Criação do CSV para armazenar as medições
    std::ofstream arquivo_csv("resultados_radixSort.csv");
    if (!arquivo_csv.is_open()) {
      std::cerr << "Erro ao criar o CSV" << "\n";
      return 1;
    }

    // Cabeçalho do CSV
    arquivo_csv << "n,intervalo_min,intervalo_max,tempo_medio_ms\n";

    // Testando as istâncias de vetores do JSON
    for (auto& instancia : data) {
        int n = instancia["n"];
        int min_val = instancia["intervalo"][0];
        int max_val = instancia["intervalo"][1];
        
        auto vetores = instancia["vetores"]; // Lista de 5 vetores

        double soma_tempos_totais = 0.0;
        int total_testes = 0;

        // Para cada um dos 5 vetores
        for (auto& vec_json : vetores) {
          std::vector<int> original_vec = vec_json.get<std::vector<int>>();

            // Executar o algoritmo 5 vezes para cada veto
            for (int exec = 0; exec < 5; exec++) {
                // copia
              std::vector<int> trabalho_vec = original_vec;

                // Medição de tempo
                auto inicio = std::chrono::high_resolution_clock::now();

                radixSort(trabalho_vec);

                auto fim = std::chrono::high_resolution_clock::now();
                
                std::chrono::duration<double, std::milli> duracao = fim - inicio;
                soma_tempos_totais += duracao.count();
                total_testes++;
            }
        }

        double media_tempo = soma_tempos_totais / total_testes;

        // Escreve no CSV
        arquivo_csv << n << "," << min_val << "," << max_val << "," << media_tempo << "\n";
        
        std::cout << "Processado: n = " << n << " | Intervalo = [" << min_val << ", " << max_val << "] | Média = " << media_tempo << " ms" << "\n";
    }

    arquivo_csv.close();
    std::cout << "Deu certo. Resultados salvos em 'resultados_insertion.csv'." << "\n";

    return 0;

}
