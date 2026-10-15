import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

# Encontra todos os arquivos CSV de resultados na pasta
arquivos_csv = glob.glob("../resultados/resultados_*.csv")

if not arquivos_csv:
    print(
        "Nenhum arquivo 'resultados_*.csv' encontrado! Rode os testes em C++ primeiro."
    )
    exit()

# Configuração visual base
plt.style.use(
    "seaborn-v0_8-whitegrid"
    if "seaborn-v0_8-whitegrid" in plt.style.available
    else "default"
)

for arquivo in arquivos_csv:
    # Extrai o nome do algoritmo (ex: resultados_bubblesort.csv -> BUBBLESORT)
    nome_algoritmo = (
        os.path.basename(arquivo).replace("resultados_", "").replace(".csv", "").upper()
    )

    df = pd.read_csv(arquivo)

    # Cria uma nova figura para cada algoritmo individualmente
    plt.figure(figsize=(8, 6))

    # Cria a coluna com o multiplicador do intervalo
    df["multiplicador"] = (df["intervalo_max"] / df["n"]).round().astype(int)

    # Itera diretamente sobre os valores únicos ordenados
    for mult in sorted(df["multiplicador"].unique()):
        grupo = df[df["multiplicador"] == mult]

        m = int(mult)
        label_legenda = "[0, n]" if m <= 1 else f"[0, {m}n]"

        # Ordena estritamente por n para a linha conectar os pontos na ordem correta
        grupo = grupo.sort_values(by="n")

        plt.plot(
            grupo["n"],
            grupo["tempo_medio_ms"],
            marker="o",
            linewidth=2,
            markersize=6,
            label=f"Intervalo {label_legenda}",
        )

    plt.title(
        f"Desempenho de Execução: {nome_algoritmo}",
        fontsize=14,
        fontweight="bold",
        pad=15,
    )
    plt.xlabel("Tamanho da Entrada (n)", fontsize=11, fontweight="bold")
    plt.ylabel("Tempo Médio (ms)", fontsize=11, fontweight="bold")
    plt.legend(title="Intervalos de Chaves", fontsize=10, title_fontsize=10)
    plt.grid(True, linestyle="--", alpha=0.6)

    plt.tight_layout()

    # Salva uma imagem separada para cada algoritmo
    nome_arquivo_saida = f"grafico_{nome_algoritmo.lower()}.png"
    plt.savefig(nome_arquivo_saida, dpi=300, bbox_inches="tight")
    print(f"Gráfico gerado e salvo: {nome_arquivo_saida}")

    # Fecha a figura atual para liberar memória
    plt.close()

print("\Todos os gráficos individuais foram gerados com sucesso!")
