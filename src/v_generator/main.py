import json
import random


def instance_generator(
    lens,  # Lista com os tamanhos dos vetores que serão criados
    ranges,  # Intervalos de valores de cada instancia de vetor
    v_num=5,  # numero de vetores a serem criados
    out_file="benchmarks.json",
):
    test_data = []

    for n in lens:
        for min_val, max_val in ranges:
            # Cria v_num vetores distintos para o mesmo tamanho
            vectors = []
            for _ in range(v_num):
                # Gera n elementos aleatórios no intervalo [min_val, max_val]
                vetor = [random.randint(min_val, max_val) for _ in range(n)]
                vectors.append(vetor)

            # estrutura de cada instancia de vetor para possível verificação
            instance = {
                "n": n,
                "intervalo": [min_val, max_val],
                "quantidade_vetores": v_num,
                "vetores": vectors,
            }
            test_data.append(instance)

    # Salvando JSON para jogar nos algoritmos de ordenacao
    with open(out_file, "w", encoding="utf-8") as f:
        json.dump(test_data, f, indent=4)

    print(f"{len(test_data)} instancias difetentes salvas em '{out_file}'.")


if __name__ == "__main__":
    v_lens = [1000, 5000, 10000, 50000, 100000]

    instances = []
    for n in v_lens:
        n_ranges = [(0, n), (0, 10 * n), (0, 100 * n), (0, 1000 * n)]
        for r in n_ranges:
            vectors = [[random.randint(r[0], r[1]) for _ in range(n)] for _ in range(5)]
            instances.append({"n": n, "intervalo": list(r), "vetores": vectors})

    with open("entrys.json", "w", encoding="utf-8") as f:
        json.dump(instances, f, indent=2)

    print("deu certo")
