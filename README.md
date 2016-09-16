# CefetinhoDoApocalipse

Método de Ataque::::

As setas indicaram o andar;
o ataque deverá ser direcionado para o sentido da seta clicada;
o default será o ataque para frente.
Shift corre;
Tomar dano perde a espada;
Quando toma dano ele fica temporariamente invencível;

Estado/Animacoes do Player::::

0 - Idle; (3 sprites)
1 - Walking (3);
2 - Running (4)
3 - Jumping (1);
4 - stdAtacking(1)(1)(1)(1);
5 - stdSpecial Atack (4) kamehameha;
6 - Damage (Animação de dano será o personagem piscando ;) );
7 - Die;
ID de outras animacoes entram seguindo a sequencia:
8-
.
.
.
n-NULL

Inimigos ::::

Boos no final de cada fase;
Inimigos triviais ficarão andando de um lado para outro;

Struct Configurations :::::

Musica;
Sons;
Lives;
CurrentMap;
CurrentCheckPoint;
AmountofMaps;
Tipo de Espada;

Tipos de Bloco :::::

0 -> Ar;
entre 1 - 100 -> Blocos estáticos com texturas diferentes;
entre 101 - 200 -> Blocos que atiram;
entre 201 - 250-> Blocos que mexem horizontalmente;
entre 251 - 300-> Blocos que mexem verticalmente;
301 a 325 -> Upgrades (espada, invencível, kamekameha, vida extra, dano);
326 a 350 -> Blocos que destroem;
351 a 375 -> Blocos invisíveis;
376 a 400 -> Blocos de liquidos/dano
401 a 450 -> Blocos decorativos(transparentes)
451 a 475 -> Alavancas(destroem blocos destrutivos com mesmo id em modulo)
476 a 500 -> Baus 
501 a 525 -> Jump Boost
666 -> ponto final da fase

1000 -> Spawn do player;
2000 a 3000 -> Spawn de Inimigos;
4000 a 4012 -> CheckPoints (quantidade depende do tamanho da fase);
Maiores que 5000 -> Spawn de Boss;
Menores que 0 -> Blocos de Teletransporte(Vai para o primeiro bloco encontrado com o mesmo valor)





