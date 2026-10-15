#include <bits/stdc++.h>
#include <cctype>

#include "json.hpp"

using json = nlohmann::json;

// Merge sort auxiliar
void merge(std::vector<int>& v, int inicio, int meio, int fim) {
  std::vector<int> aux;

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

void mergeSort(std::vector<int>& v, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }

    int meio = inicio + (fim - inicio) / 2;

    mergeSort(v, inicio, meio);
    mergeSort(v, meio + 1, fim);

    merge(v, inicio, meio, fim);
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
    std::ofstream arquivo_csv("resultados_mergeSort.csv");
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
                
                int begin = 0;
                int end = trabalho_vec.size() - 1;
                mergeSort(trabalho_vec, begin, end);

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
