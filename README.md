#RESUMO DOS ASSUNTOS ABORDADOS AO LONGO DA DISCIPLINA
## Estrutura de Dados II - Universidade Federal de Sergipe (UFS)

Este repositório contém materiais e implementações práticas dos principais conceitos ensinados na disciplina **Estrutura de Dados II** (SINF0007), oferecida pelo **Departamento de Sistemas de Informação** da **Universidade Federal de Sergipe (UFS)** e ministrada pelo **Prof. Dr. Raphael Pereira de Oliveira**. A disciplina abrange algoritmos e estruturas de dados avançadas para armazenamento, manipulação e recuperação eficiente de dados em sistemas de larga escala.

---

## 📚 Conteúdo do Curso

### 1. **Dispositivos de Armazenamento Secundário**

   - **Conteúdo**:
     - Visão geral sobre dispositivos de armazenamento secundário, como HDs, SSDs e unidades de backup.
     - Hierarquia de memória e a diferença entre armazenamento primário e secundário.
     - Impacto das tecnologias de armazenamento na performance dos sistemas.

---

### 2. **Revisão de C**

   - **Descrição**: Revisão dos principais conceitos da linguagem C, essenciais para a implementação de estruturas de dados avançadas.
   - **Conteúdo**:
     - Ponteiros, tipos estruturados e alocação dinâmica de memória.
     - Manipulação de dados por ponteiros e operações básicas para modificar dados na memória.
     - Estruturas básicas para criação e manipulação de arquivos em C.

---

### 3. **Conceitos Preliminares de Arquivos e Implementação em C**

   - **Descrição**: Introdução ao uso de arquivos em C, abordando os conceitos fundamentais para a organização de dados externos.
   - **Conteúdo**:
     - Estrutura e tipos de arquivos (texto e binário).
     - Utilização de buffers para otimizar operações de leitura e escrita.
     - Modos de abertura, fechamento de arquivos e operações de flush para integridade dos dados.

---

### 4. **Arquivo e Organização Sequencial**

   - **Descrição**: Organização de dados em arquivos sequenciais, com operações e algoritmos para manipulação de dados ordenados e não ordenados.
   - **Conteúdo**:
     - Estrutura de arquivos sequenciais e suas operações.
     - Algoritmos de inserção, exclusão e busca em arquivos sequenciais.
     - Técnicas de otimização de busca em arquivos ordenados e desordenados.

---

### 5. **Arquivo Sequencial em Lote**

   - **Descrição**: Técnicas de processamento e atualização em lote para dados armazenados em arquivos sequenciais.
   - **Conteúdo**:
     - Organização e atualização de dados em massa.
     - Estruturas de arquivos mestre e transações.
     - Implementação do algoritmo "Balance Line" para manutenção de registros de transações.

---

### 6. **Classificação Externa - Geração e Intercalação de Partições Classificadas**

   - **Descrição**: Métodos para ordenação de grandes volumes de dados que não cabem na memória principal, dividindo o processo em etapas de geração e intercalação.
   - **Conteúdo**:
     - Geração de partições ordenadas para organização de grandes arquivos.
     - Intercalação de partições utilizando estruturas como árvore binária de vencedores.
     - Aplicação de classificação externa para manipulação de grandes conjuntos de dados.

---

### 7. **Arquivo de Acesso Direto (Hash)**

   - **Descrição**: Introdução ao uso de hashing para acesso direto e rápido a registros em grandes arquivos, abordando técnicas de tratamento de colisões.
   - **Conteúdo**:
     - Conceito de função de hash e suas propriedades.
     - Técnicas de tratamento de colisões, como encadeamento exterior e interior.
     - Aplicações práticas de hashing em indexação e recuperação de dados.

---

### 8. **Arquivo Indexado (Árvore B)**

   - **Descrição**: Estruturas de árvores B como método de indexação para busca eficiente em grandes volumes de dados, comuns em sistemas de bancos de dados.
   - **Conteúdo**:
     - Estrutura de uma árvore B, incluindo organização de dados e nós internos.
     - Operações de inserção, exclusão e busca em árvores B.
     - Vantagens das árvores B para armazenamento eficiente e alta performance de busca.

---

### 9. **Arquivo Indexado (Árvore B+)**

   - **Descrição**: Estruturas de árvore B+ para otimização de busca em arquivos de grande volume, com armazenamento de dados nas folhas.
   - **Conteúdo**:
     - Estrutura e operações de uma árvore B+, incluindo inserção, busca e exclusão.
     - Comparação entre árvores B e B+ em aplicações de indexação.
     - Aplicação prática em sistemas de banco de dados.

---

### 10. **Recuperação de Chave Secundária - Multilistas e Arquivos Invertidos**

   - **Descrição**: Métodos de recuperação de dados usando chaves secundárias, importantes para sistemas com múltiplos critérios de busca.
   - **Conteúdo**:
     - Implementação de multilistas para buscas eficientes com base em atributos secundários.
     - Estrutura e funcionamento de arquivos invertidos para indexação secundária.
     - Aplicações práticas em bancos de dados e busca por múltiplos atributos.

---

### 11. **Backtracking**

   - **Descrição**: Algoritmos de backtracking para exploração de espaços de busca e solução de problemas de otimização.
   - **Conteúdo**:
     - Implementação de algoritmos de backtracking para problemas complexos.
     - Soluções de problemas clássicos, como Passeio do Cavalo e problema das nRainhas.
     - Análise de complexidade e otimização em problemas combinatórios.

---

### 12. **Divide and Conquer**

   - **Descrição**: Estratégia de divisão e conquista aplicada a algoritmos como ordenação e busca, eficiente para problemas que podem ser divididos em subproblemas.
   - **Conteúdo**:
     - Algoritmos de divisão e conquista, como mergesort e busca binária.
     - Cálculo eficiente de potências e outras operações recursivas.
     - Aplicação em problemas que requerem divisão para ganho de eficiência.

---

### 13. **Programação Dinâmica**

   - **Descrição**: Técnicas de otimização usando programação dinâmica para resolver problemas com subproblemas sobrepostos e evitar cálculos redundantes.
   - **Conteúdo**:
     - Conceitos de programação dinâmica e diferença para métodos gulosos.
     - Problemas clássicos, como a mochila e subsequência comum máxima.
     - Aplicação de tabelas de memoização e análise de complexidade.

---

### 14. **Algoritmos Gulosos**

   - **Descrição**: Algoritmos que utilizam a abordagem gulosa para resolver problemas de otimização com escolhas locais ótimas.
   - **Conteúdo**:
     - Fundamentos de algoritmos gulosos e análise de eficiência.
     - Aplicações em problemas clássicos, como mochila fracionária e cobertura de intervalos.
     - Limitações dos algoritmos gulosos e situações ideais para seu uso.
