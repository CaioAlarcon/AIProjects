Como compilar:

no terminal:<br>
git cone https://github.com/CaioAlarcon/AIProjects<br>
cd AIProjects<br>
make<br>


Como usar:

usage: maze [options] 

-s          :resolve            (-s alg)

-g          :gera o labirinto   (-g h w wd)

-w          :escreve no arquivo (-w arquivo)

-p          :mostrar passos

--seed      :especifica a seed  (--seed 465015)

--log       :habilita o arquivo de log

--print     :mostra na tela

alg         :0-6

0           :rand

1           :profundidade

2           :largura

3           :BestFirst

4           :AStar

5           :Dijkstra

6           :Hill Climbing



h           :altura do labirinto

w           :largura do labirinto

wd          :densidade de obstáculos



Exemplo:

Gerar um labirinto 50X50 com densidade 20% e salvar no arquivo maze.txt:

./maze -g 50 50 0.2 -w maze.txt




Resolver o labirinto salvo em maze.txt usando AStar e mostrar solução na tela:



./maze -s maze.txt 4 -p






