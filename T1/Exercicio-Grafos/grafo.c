/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  if (!G || !G->arestas || !G->vertices) return;
  
  t_no *atual = G->arestas->primeiro_no;
  t_no *ant = NULL;

  // Desfaz a lista de arestas
  while (atual) {
    ant = atual;
    atual = atual->proximo;
    
    free (ant);
  }
  
  if (ant)
    free (ant);
  free (G->arestas);
  G->arestas = NULL;

  
  atual = G->vertices->primeiro_no;
  ant = NULL;

  // Desfaz a lista de vértices
  while (atual) {
  ant = atual;
    atual = atual->proximo;
    
    free (ant);
  }
  
  if (ant)
    free (ant);
  free (G->vertices);
  G->vertices = NULL;


  // Libera a o grafo em si
  free (G);
  G = NULL;
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  if (!G) return;

  t_vertice *v = malloc (sizeof (t_vertice));
  v->id = id;
  v->fronteira = NULL;

  if (!G->vertices) {
    G->vertices = cria_lista ();
  }

  empilha (v, G->vertices);
}



// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  
  // codificar...


  /*
  Possibilidades:

  1)
    Vou lá no ID e encontro o vértice em questão 
    Localizo cada um uma das arestas que estão na lista fronteira, lá
    na lista de arestas no grafo e tiro simultanuamente das duas listas
  
    Depois de desconectar tudo, removo o vértice
  
  2) 
    Vou lá no ID e encontro o vértice em questão
    Localizo as fronteiras, e tiro todas elas (pressupondo que elas estão diretamente ligadas as fronteiras do grafo G)

    Depois de desconectar tudo, removo o vértice


    */

}


int existe_aresta (int u_id, int v_id, grafo G) {
  if (!G) return;

  // Verifica se existe né
  if (busca_chave (u_id, G->vertices, vertice_id) && busca_chave (v_id, G->vertices, vertice_id)) {
    return 1;
  }

  return 0;
}



// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  if (!G) return;

  // Verifica se aqueles vértices existem antes de fazer o malloc e adicionar
  if (existe_aresta (u_id, v_id, G)) {

    t_aresta *a = malloc (sizeof(t_aresta));
    if (!a) perror ("Erro ao criar a aresta\n");

    a->id = id;
    a->u = u_id;
    a->v = v_id;

    empilha (a, G->arestas);
  }
  else perror ("Não existem esses vértices\n");

}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  
  // codificar...

}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}
