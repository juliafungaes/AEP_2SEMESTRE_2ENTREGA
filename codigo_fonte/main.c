#include <stdio.h>
#include <string.h>

#define MAX 10

struct Acao {
    int codigo;
    char escola[50];
    char tema[50];
    char data[11];
    char publico[50];
    char responsavel[50];
    int qtdPrevista;
    int qtdEfetiva;
    int situacao;
};

struct Acao acoes[MAX];
int total = 0;

int lerInteiro(char mensagem[]) {
    int numero;
    printf("%s", mensagem);
    while (scanf("%d", &numero) != 1) {
        while (getchar() != '\n');
        printf("Erro: digite apenas numeros. Tente de novo: ");
    }
    return numero;
}

int buscarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void imprimirSituacao(int situacao) {
    if (situacao == 1) {
        printf("Planejada");
    } else if (situacao == 2) {
        printf("Realizada");
    } else {
        printf("Cancelada");
    }
}

void mostrarAcao(int i) {
    printf("\nCodigo.............: %d\n", acoes[i].codigo);
    printf("Escola.............: %s\n", acoes[i].escola);
    printf("Tema...............: %s\n", acoes[i].tema);
    printf("Data prevista......: %s\n", acoes[i].data);
    printf("Publico-alvo.......: %s\n", acoes[i].publico);
    printf("Responsavel........: %s\n", acoes[i].responsavel);
    printf("Participantes prev.: %d\n", acoes[i].qtdPrevista);
    printf("Participantes efet.: %d\n", acoes[i].qtdEfetiva);
    printf("Situacao...........: ");
    imprimirSituacao(acoes[i].situacao);
    printf("\n");
}

void cadastrarAcao() {
    struct Acao nova;

    printf("\n=== CADASTRAR ACAO ===\n");

    if (total >= MAX) {
        printf("Erro: limite de armazenamento atingido (%d acoes).\n", MAX);
        return;
    }

    nova.codigo = lerInteiro("Codigo (numero maior que 0): ");
    if (nova.codigo <= 0) {
        printf("Erro: o codigo deve ser maior que zero.\n");
        return;
    }
    if (buscarPorCodigo(nova.codigo) != -1) {
        printf("Erro: ja existe uma acao com esse codigo.\n");
        return;
    }

    printf("Escola: ");
    scanf("%49s", nova.escola);
    printf("Tema: ");
    scanf("%49s", nova.tema);

    printf("Data prevista (DD/MM/AAAA): ");
    scanf("%10s", nova.data);
    while (strlen(nova.data) != 10 || nova.data[2] != '/' || nova.data[5] != '/') {
        printf("Erro: data invalida. Use o formato DD/MM/AAAA: ");
        scanf("%10s", nova.data);
    }

    printf("Publico-alvo: ");
    scanf("%49s", nova.publico);
    printf("Responsavel: ");
    scanf("%49s", nova.responsavel);

    nova.qtdPrevista = lerInteiro("Quantidade prevista de participantes: ");
    while (nova.qtdPrevista <= 0) {
        printf("Erro: a quantidade deve ser maior que zero.\n");
        nova.qtdPrevista = lerInteiro("Quantidade prevista de participantes: ");
    }

    nova.qtdEfetiva = 0;
    nova.situacao = 1;

    acoes[total] = nova;
    total++;
    printf("Acao cadastrada com sucesso!\n");
}

void listarAcoes() {
    int i;

    printf("\n=== LISTA DE ACOES ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        printf("\n[%d] Codigo %d | %s | %s | %s | Prev: %d | Efet: %d | ",
               i + 1, acoes[i].codigo, acoes[i].escola, acoes[i].tema,
               acoes[i].data, acoes[i].qtdPrevista, acoes[i].qtdEfetiva);
        imprimirSituacao(acoes[i].situacao);
    }
    printf("\n");
}

void pesquisarAcao() {
    int opcao, codigo, i, achou = 0;
    char texto[50];

    printf("\n=== PESQUISAR ACAO ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("1 - Por codigo\n2 - Por escola\n3 - Por tema\n");
    opcao = lerInteiro("Escolha: ");

    if (opcao == 1) {
        codigo = lerInteiro("Codigo: ");
        i = buscarPorCodigo(codigo);
        if (i == -1) {
            printf("Nenhuma acao encontrada com esse codigo.\n");
        } else {
            mostrarAcao(i);
        }
    } else if (opcao == 2) {
        printf("Nome da escola (igual ao cadastrado): ");
        scanf("%49s", texto);
        for (i = 0; i < total; i++) {
            if (strcmp(acoes[i].escola, texto) == 0) {
                mostrarAcao(i);
                achou = 1;
            }
        }
        if (achou == 0) {
            printf("Nenhuma acao encontrada para essa escola.\n");
        }
    } else if (opcao == 3) {
        printf("Tema (igual ao cadastrado): ");
        scanf("%49s", texto);
        for (i = 0; i < total; i++) {
            if (strcmp(acoes[i].tema, texto) == 0) {
                mostrarAcao(i);
                achou = 1;
            }
        }
        if (achou == 0) {
            printf("Nenhuma acao encontrada para esse tema.\n");
        }
    } else {
        printf("Erro: opcao de pesquisa inexistente.\n");
    }
}

void atualizarSituacao() {
    int codigo, i, nova, efetiva;

    printf("\n=== ATUALIZAR SITUACAO ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ");
    i = buscarPorCodigo(codigo);
    if (i == -1) {
        printf("Erro: acao nao encontrada.\n");
        return;
    }

    printf("1 - Planejada\n2 - Realizada\n3 - Cancelada\n");
    nova = lerInteiro("Nova situacao: ");

    if (nova == 2) {
        efetiva = lerInteiro("Quantidade efetiva de participantes: ");
        while (efetiva < 0) {
            printf("Erro: a quantidade nao pode ser negativa.\n");
            efetiva = lerInteiro("Quantidade efetiva de participantes: ");
        }
        acoes[i].qtdEfetiva = efetiva;
        acoes[i].situacao = 2;
    } else if (nova == 1 || nova == 3) {
        acoes[i].qtdEfetiva = 0;
        acoes[i].situacao = nova;
    } else {
        printf("Erro: situacao inexistente.\n");
        return;
    }

    printf("Situacao atualizada com sucesso!\n");
}

void gerarResumo() {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    int participantes = 0, previstos = 0;
    float percentual;

    printf("\n=== RESUMO GERAL ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            participantes = participantes + acoes[i].qtdEfetiva;
            previstos = previstos + acoes[i].qtdPrevista;
        } else {
            canceladas++;
        }
    }

    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Total de participantes (acoes realizadas): %d\n", participantes);

    if (previstos > 0) {
        percentual = (float)participantes * 100 / previstos;
        printf("Percentual de participacao: %.1f%%\n", percentual);
    } else {
        printf("Percentual de participacao: indisponivel (nenhuma acao realizada)\n");
    }
}

void mostrarInformacoes() {
    printf("\n=== INFORMACOES DO SISTEMA ===\n");
    printf("Guarda ate %d acoes na memoria (some ao fechar o programa).\n", MAX);
    printf("Usa somente dados ficticios e coletivos.\n");
    printf("NAO registra dados de estudantes e NAO faz diagnostico.\n");
}

void mostrarMenu() {
    printf("\n=========== PSE EM ACAO ===========\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acao\n");
    printf("4 - Atualizar situacao\n");
    printf("5 - Gerar resumo geral\n");
    printf("6 - Informacoes do sistema\n");
    printf("7 - Sair\n");
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrarAcao();      break;
            case 2: listarAcoes();        break;
            case 3: pesquisarAcao();      break;
            case 4: atualizarSituacao();  break;
            case 5: gerarResumo();        break;
            case 6: mostrarInformacoes(); break;
            case 7: printf("Encerrando o programa. Ate logo!\n"); break;
            default: printf("Opcao invalida. Escolha de 1 a 7.\n");
        }
    } while (opcao != 7);

    return 0;
}
