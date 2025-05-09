import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os

# Lista de arquivos CSV para comparar (dicionário com nome do arquivo e legenda)
csv_files = {
     "C:/Users/Pedro/Desktop/proj_renault_atualizado/Simulador_renault_rota2030/build/All_debug/OutputData/outputDatadT20est.csv" : "Referência",
     "C:/Users/Pedro/Desktop/proj_renault_atualizado/Simulador_renault_rota2030/build/All_debug/OutputData/outputDataxc042est.csv" : "xc = 0.42",
     "C:/Users/Pedro/Desktop/proj_renault_atualizado/Simulador_renault_rota2030/build/All_debug/OutputData/outputDatamaeby2est.csv" : "mae / 2",
     "C:/Users/Pedro/Desktop/proj_renault_atualizado/Simulador_renault_rota2030/build/All_debug/OutputData/outputDataqsolest.csv" : "qsol = 1500"
     #"C:/Users/Pedro/Desktop/proj_renault_atualizado/Simulador_renault_rota2030/build/All_debug/OutputData/outputDatamiv01est.csv" : "miv = 0.1 * mae"
}

# Lista de colunas que deseja plotar
columns_to_plot = ["Inlet Temperature"]

x_axis_column = "Tempo (s)"  # Coluna do eixo X
starting_line = 1  # Define a linha a partir da qual os dados serão lidos
MAX_TEMPO = 7000  # Limite para parar a plotagem
PRINT_LAST_ROW = True  # Se True, imprime os valores da última linha

def update(frame):
    plt.cla()  # Limpa o gráfico antes de redesenhar

    plt.xlabel(x_axis_column)
    plt.ylabel("Temperatura do ar de retorno (°C)")
    plt.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)

    for csv_file, label_name in csv_files.items():
        if os.path.exists(csv_file):
            try:
                # Lê o cabeçalho da primeira linha
                headers = pd.read_csv(csv_file, sep=";", nrows=0).columns

                # Lê os dados a partir de uma linha específica, mantendo o cabeçalho
                data = pd.read_csv(csv_file, sep=";", skiprows=starting_line, names=headers)

                # 🚨 Filtrar para que Tempo <= 5000
                data = data[data[x_axis_column] <= MAX_TEMPO]

                # Tratamento de erros e remoção de valores inválidos
                data = data.replace([float('inf'), float('-inf')], pd.NA)  # Remove inf
                data = data.dropna()  # Remove NaN
                
                # Garantir que todos os valores zero sejam removidos
                for col in columns_to_plot:
                    if col in data.columns:
                        data = data[data[col] != 0]

                # Plotar os dados
                if not data.empty and x_axis_column in data.columns:
                    for col in columns_to_plot:
                        if col in data.columns:
                            plt.plot(data[x_axis_column], data[col], label=f"{label_name}")

                    # ✅ Exibe os valores da última linha se ativado
                    if PRINT_LAST_ROW:
                        last_row = data.iloc[-1]
                        print(f"\nÚltima linha de '{label_name}':")
                        for col in columns_to_plot:
                            if col in data.columns:
                                print(f"{col}: {last_row[col]}")
            except pd.errors.EmptyDataError:
                print(f"Arquivo {csv_file} está vazio.")
        else:
            print(f"Arquivo {csv_file} não encontrado.")

    plt.legend(loc="upper right")

# Criação da figura e configuração da animação
fig, ax = plt.subplots()
ani = FuncAnimation(fig, update, interval=1000)  # Atualiza a cada 1s
plt.show()
