#ifndef IO_H
#define IO_H

/*
    leiaArquivo()

A entrada será fornecida em um arquivo com o seguinte formato:

    A primeira linha tem os parâmetros globais, separados por espaço:
        Tamanho do planeta (raio).
        Massa do planeta.
        Tempo total de simulação.
    A segunda linha contém a descrição da primeira nave, com os seguintes campos separados por espaço:
        nome — nome da nave, para referência posterior.
        massa — massa da nave.
        pos_x — coordenada x da posição da nave.
        pos_y — coordenada y da posição da nave.
        vel_x — componente x da velocidade da nave.
        vel_y — componente y da velocidade da nave.
    A terceira linha descreve a segunda nave, da mesma forma.
    A quarta linha indicará o número de projéteis e a duração (tempo de vida) deles.
    As linhas seguintes conterão a descrição de cada projétil, da mesma forma que nas naves, mas sem o campo nome.

    Os valores serão fornecidos no sistema métrico.
*/
void leiaArquivo();

#endif
