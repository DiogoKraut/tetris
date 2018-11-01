DIOGO PARIS KRAUT - GRR20166365

TETRIS
Compilar com make.

O programa pode ser dividido em 3 partes para facilitar o entendimento.

1. INICIALIZAÇÃO

	É a geraçâo do estado inicial do jogo. Ocorre na declaração de variaveis
	globais em tetris.c e na função main até a linha 114.

	Durante a inicialização são impressas as telas auxiliares que mostram a borda
	da arena, instruções de como jogar, um preview da próxima peça e os highscores.

	As funções de inicialização estão em game.c

2. PARTE ASSÍNCRONA

	É usado um timer para implementar a queda das peças. Sempre que o timer chega
	em 0 é elevado o sinal SIGALRM que, na função signal_handler, move a peça para
	baixo. Se a peça colidir ela é fixada nessa posição e uma nova peça é gerada.

	A implementação de signal_handler e a inicialização dos sinais e do timer
	ocorrem em game.c.

	Caso as peças se empilhem até o topo da arena é gerado o sinal SIGUSR1,
	sinalizando o fim de jogo e salvando a pontuação.

3. PARTE SINCRONA

	Em tetris.c:114:
	O programa pega os inputs do teclado e aplica as ações nescessárias para
	trata-los.

	Essas ações podem ser:

		Mover a peça:
		Peças podem ser movidas para direita ou esquerda. A movimentação não é feita
		quando causar colisão.

		Rotacionar a peça:
		Peças podem ser rotacionadas de -90 graus (sentido horário). Não é feita se
		for causar colisão.

		Salvar e sair:
		Salva a pontuação atual e sai.

	Sistema de pontuação:
	Jogador ganha:
		5 pontos sempre que uma peça se move para baixo;
		10 pontos quando a peça é fixada;
		500 pontos quando uma linha é removida.

	A pontuação atual é mostrada logo abaixo do preview.

OBS1:

	A especificação pede que 'h' abra a tela de ajuda, mas como tinha espaço,
	resolvi imprimir as instruções ao lado da arena.

OBS2:

	Uma peça é representada por uma matrix 3x3:

	{0, 1, 0}
	{0, 1, 0}
	{0, 1, 0} é a peça "I", por exemplo.

	Um "bloco" é simplesmente o numero 1 na matriz da peça.
