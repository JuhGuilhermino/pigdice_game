# Pig Dice Game

Esse projeto é uma versão do jogo Pig Dice para um trabalho da disciplina "Programação I", do curso de Bacharelado em Ciência da Computação da Universidade Federal do Rio Grande do Norte (UFRN). 

**Autoras:** [Júlia Maria A. Guilhermino](https://github.com/JuhGuilhermino) e [Ludmilla Rodrigues](https://github.com/Ludrodrigues).

## Como Executar
Para compilar o programa utilize o comando <make> e em seguida o parâmentro <./pig_dice> no terminal.
Ao compilar o make uma vez todos os arquivos são inicializados. Para suspender essa ação digite <make clean>.

## Desafio Encontrado: Arquiteura Game Loop
O principal desafio nesse projeto foi implementar a arquitura Game Loop. Antes de começar a programação, sentimos a necessidade de discutir como trabalhar com os difentes estados para que as ações ocorrecem na ordem correta. 
Para facilitar esse processo também optamos por não ultilizar na integra o template ofertado pelo professor. Mas procuramos estudar o código e acabamos utilizando algumas estruturas que fizeram sentido para gente.
Geramos vários esquemas diferentes em uma ferramenta chamada [Miro](https://miro.com/app/dashboard/). O mais recente e que decidimos implementar foi o aprensentado abaixo.

![Projeto do Jogo](./imgs/project_final.png)

## Problemas Não Solucionados 
A única falha identificada por nós no projeto foi na autualização e exbição do histórico do jogo ao final da partida. Não conseguimos sincronizar o momento adequado de salvar os dados: quantidade de vezes que a ação "ROOL" é solicitada e pontos que ela gerou no turno. Desse modo os números que aparecem no histórico sofrem ocilações. 
Entretando essa falha não altera a contagem de pontos da partida, nem influencia no resultado final do jogo. Pois trata-se apenas de um erro ao escolher o momento do código associado a gravação das informações no array referente ao histórico de cada jogador. Acreditamos que a dificuldade em solucionar esse problema está associada ao primiero contanto com a arquitetura Game Loop.
