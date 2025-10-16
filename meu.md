```
def visualizar_rede(self):
        try:
            if self.G_subset is None:
                print("O subgrafo não existe!")
                return False
```

>> A biblioteca matplotlib é uma biblioteca do Python ideal para criar visualizações matemáticas, a matplotlib.pyplot é uma coleção de funções específicas para plotar grafos e gráficos
>> A função plt.figure cria uma imagem
```
            plt.figure(figsize=(20, 15))
```
>> A função spring_layout é nativa do NetworkX e distribui os nós a partir do algoritmo de força direcionada de Fruchterman-Reingold
>> A utilização dessa distribuição para os nós foi por questão estética, o algoritmo precisa do número k que é a distância entre os nós e o número de iterações para o algoritmo convergir. A escolha de k=2 e iterations=1000 foram para deixar uma distribuição mais organizada
```
            pos = nx.spring_layout(self.G_subset, k=2, iterations=2000)
```
>> O tamanho dos nós é variável de acordo com o grau dele, mas para a diferença visual não ser tão grande, foi utilizado o logaritmo do grau dos nós para criar uma lista com os tamanhos. O log()+1 evita erros com o log(0) que é indefinido
```
            #Calcula o grau de cada nó coloca em um dicionário e o tamanho do nó é proporcional ao grau
            graus = dict(self.G_subset.degree())
            tamanhos = [np.log(graus[node]+1)*25 for node in self.G_subset.nodes()]
```
>> A função percentile da biblioteca NumPy divide os graus em valores de porcentagem. Para os nós serem dividos em cores de acordo com o grau, o percentis divide os valores dos graus em porcentagens de 25%, 50%, 75% e 95%. O que significa que se 25% dos nós tem um certo valor de grau ou menor eles vão ter a mesma cor, nós utilizamos a paleta de cores "plasma" do matplotlib que faz com que os nós menos conectados sejam da cor azul e os mais da cor amarela
```
            #Para melhor visualização no grafo, os nós tem cores de acordo com o grau
            graus_valores = list(graus.values())
            percentis = np.percentile(graus_valores, [25, 50, 75, 95])
```
>> Divide as cores de cada nó em 4 divisões de acordo com as porcentagens calculadas anteriormente
```
            node_colors = []
            for node in self.G_subset.nodes():
                if graus[node] <= percentis[0]:
                    node_colors.append(0)
                elif graus[node] <= percentis[1]:
                    node_colors.append(1)
                elif graus[node] <= percentis[2]:
                    node_colors.append(2)
                elif graus[node] <= percentis[3]:
                    node_colors.append(3)
                else:
                    node_colors.append(4)
            
            #Definições de visualização
            nx.draw_networkx_nodes(self.G_subset, pos, node_size=tamanhos, node_color=node_colors, cmap="plasma", alpha=1)
            nx.draw_networkx_edges(self.G_subset, pos, alpha=1, edge_color="gray", width=0.5)
```
>> Cria uma legenda explicando as cores de acordo com o grau dos nós, é variável a cada vez que é rodado o código, pois depende da porcentagem
```
            #Definição da legenda
            legend_labels = [f"Grau ≤ {int(percentis[0])}", f"Grau {int(percentis[0])+1}-{int(percentis[1])}",
                             f"Grau {int(percentis[1])+1}-{int(percentis[2])}", f"Grau {int(percentis[2])+1}-{int(percentis[3])}",
                             f"Grau > {int(percentis[3])}"]
            
            cmap = plt.cm.plasma
            legend_colors = [cmap(0.1), cmap(0.3), cmap(0.5), cmap(0.7), cmap(0.9)]

            legend_elements = [Patch(facecolor=legend_colors[i], label=legend_labels[i], alpha=0.8) for i in range(5)]

            plt.legend(handles=legend_elements, loc="upper right", bbox_to_anchor=(1.15, 1.0), title="Legenda - Cores por Grau",
                  fontsize=10, framealpha=0.9)

            plt.title("REDE FACEBOOK", fontsize=16, pad=20)
            plt.axis("off")
            plt.tight_layout()
            plt.show()
            return True
            
        except Exception as e:
            print(f"Erro na visualização: {e}")
            return False
```
