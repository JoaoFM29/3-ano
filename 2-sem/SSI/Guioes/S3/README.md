# Respostas das Questões

## Q1

Algoritmicamente, não há difrenças na lógica de ambos os programas. Contudo, a difrença está sim presente na forma como a chave é gerada, mais concretamente nos bytes aleatórios que são escolhidos. Deste modo, as chaves geradas pelo o *otp.py* possuem uma maior variedade do que as do *bad_otp*.Esta difrença é relativamente complicada de observar, isto porque requer alguma paciência em testar o programa, e ainda a habilidade de comprarar corretamente as chaves geradas, sendo que pode muitas das vezes passar despercebida esta insegurança do mecanismo de geração de chaves

## Q2

O resultado obtido com o ataque à cifra *otp* mostra que esta cifra não é totalmente imbatível. Como referido na questão anterior, isto deve-se ao facto de a forma como se geram as chaves ser ou não segura. Desta forma, pode ser repetido o processo de geração que levou à chave utilizada, deixando assim de ser aleatória. Desta forma, pode até ser argumentado que se a chave for verdadeiramente aleatória e do mesmo tamanho ou maior que a mensagem que queremos cifrar, continuamos a garantir a segurança. Contudo o mecanismo de geração utilizado pelas máquinas nunca será inteiramente aleatório, pois dependerá sempre de fórmulas matemáticas utilziadas pelos computadores. A aleatoridade dos computadores é muito útil para coisas como jogos, mas extremamente insegura para segurança.
