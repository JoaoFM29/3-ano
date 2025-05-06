import math

from Node import Node # from -> nome do ficheiro, import -> nome da classe

class Graph:
    def __int__(self, directed = False):
        self.m_node = []
        self.m_directed = directed
        self.m_graph = {}
        self.m_h = {}

def get_arc_cost(self, node1, node2):
    custoT = math.inf
    a = self.m_graph[node1]
    for(nodo, custo) in a:
        if nodo == node2:
            custoT = custo
    return custoT

def calcula_custo(self, caminho):
    teste = caminho
    custo = 0
    i = 0
    while i+1 < len(teste):
        custo = custo + self.get_arc_cost(teste[i], teste[i+1])
        i = i + 1
    return custo

def procura_DFS(self, start, end, path = [], visited = set()):
    path.append(start)
    visited.add(start)

    if start == end:
        custoT = self.calcula_custo(path)
        return (path, custoT)
    for(adjacente, peso) in self.m_graph[start]:
        if adjacente not in visited :
            resultado = self.procura_DFS(adjacente, end, start, visited)
            if resultado is not None:
                return resultado
    path.pop()
    return None


def procura_BFS(self, start, end):

    # definir nodos visitados para evitar ciclos
    visited = set()
    fila = Queue()
    custo = 0

    # adicionar o nodo incial à fila e aos visitados
    fila.put(start)
    visited.add(start)

    # garantir que o start node nao tem pais...
    parent = dict()
    parent[start] = Node

    path_found = False
    while not fila.empty() and path_found == False:
        nodo_atual = fila.get()
        if nodo_atual == end:
            path_found = True
        else:
            for(adjacente, peso) in self.m_graph[nodo_atual]:
                if adjacente not in visited:
                    fila.put(adjacente)
                    parent[adjacente] = nodo_atual
                    visited.add(adjacente)

    # reconstruir o caminho
    path = []
    if path_found:
        path.append(end)
        while parent[end] is not Node:
            path.append(parent[end])
            end = parent[end]
        path.reverse()

        # função calcula custo caminho
        custo = self.calcula_custo(path)
    return (path, custo)