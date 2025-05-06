# Q1

Para este ponto, criamos uma diretoria "testes" e um ficheiro "exemplo.txt". Por default, este ficheiro foi criado com permissões read para todos os utilizadores e write para o dono. Com o comando chmod, alteramos estas configurações, retirando a permissão write e read. Para este efeito, utilizamos a flag "a-rw", mas seria equivalente passar o octeto 000.O que observamos é que comandos como o "cat" deixaram de exibir o ficheiro, e que deixamos também de conseguir editar o ficheiro. 

A nível da diretoria:
r em diretoria podemos ver os ficheiros dentro de uma diretoria. É preciso ter "r" em todas as diretorias de um ficheiro "/desktop/s8..."
x em diretoria podemos fazer "cd" para lá.s
w em diretoria podemos adicionar, alterar e remover ficheiros.

Como funcionam as permissões em octal?
3 posições -;-;-
	   r:4, w:2, x:1
Se quissesse que todos fosse rw: 666, somamos para cada octeto.

chown muda o utilizador. Funciona se for owner do ficheiro.



# Q2

Primeiramente, verificamos que utilizadores se encontravam no ficheiro "/etc/passwd" e também os grupos no ficheiro "/etc/group". De seguida, criamos os utilizadores para a equipa. Um exemplo, seria criar o utilizador para o colega Rodrigo com o seguinte comando "sudo adduser rod". De seguida, criamos um grupo com o comando "sudo groupadd s8". Depois resta adicionar os utilizadores ao grupo. Isso pode ser feito com o comando "sudo usermod -a -G s8 rod". Podemos ver que o comando correu com sucesso ao utilizar outro comando "groups rod". Para terminar, 

usermod -a -G examplegroup exampleusername

# Q3

Depois de escrever o programa em c, inclui a linha "setuid(1000)", onde o id "1000" corresponde ao id do utilizador da máquina que criou o ficheiro. Contudo, com isto não vimos diferenças no ficheiro, então decidimos exprimentar com o comando "chmod 7751 reader" e desta vez já vimos a diferença no octeto das permissões. De seguida fizemos um teste com um ficheiro de texto com o octeto 600, e trocamos para um utilizador difrente do que criou o ficheiro (o utilizador que criou o ficheiro de texto era o de id 1000). Vimos que o nosso utilizador sem permissões não conseguia executar um "cat", mas conseguia o nosso ficheiro.

# Q4
Tendo uma diretoria chamado "testes", precisamos de definir diferentes permissões de acesso para utilizadores e grupos específicos. Digamos que queremos que o utilizador "rod" tenha permissão total de leitura e escrita, o grupo "s8" apenas permissão de leitura, e nenhum acesso para outros utilizadores. Para fazer isso, utilizamos o comando "setfacl". Primeiro, concedemos permissões para o utilizador "rod", usando o comando "setfacl -m u:rod:rw- testes". Isso significa que ele pode ler e escrever em todos os arquivos dentro da diretoria "testes". Em seguida, atribuímos permissões para o grupo "s8" com o comando setfacl -m g:s8:r-- testes. Isso garante que os membros desse grupo possam apenas ler os arquivos na diretoria. Por fim, removemos todas as permissões para outros users usando setfacl -m o:- testes, o que significa que nenhum outro utilizador terá acesso à diretoria.
Após configurar as permissões, podemos verificar se foram aplicadas corretamente usando o comando "getfacl". Ao executar "getfacl testes", podemos ver as permissões detalhadas atribuídas a cada utilizador e grupo. Com isso, garantimos que apenas o utilizador "rod" tem acesso total de leitura e escrita, o grupo "s8" tem apenas acesso de leitura e nenhum outro utilizador pode acessar os arquivos dentro da diretoria "projeto". Essa é uma maneira poderosa de gerenciar permissões de forma granular em sistemas Linux.