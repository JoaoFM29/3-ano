# Respostas das Questões

## Q2
O NONCE é uma parte crucial neste tipo de criptografia e ao repeti-lo estamos a comprometer a segurança do sistema. O uso do mesmo com tudo '0', num esquema de criptografia como o ChaCha20, não garantirá a unicidade das chaves, uma vez que, para diferentes mensagens criptografadas com a mesma chave, terão o mesmo NONCE.
O ChaCha20 gera um fluxo de chave exclusivo com base no NONCE e na chave. Ao usar um NONCE fixo, significa que o mesmo fluxo de chave é gerado repetidamente, comprometendo a confidencialidade dos dados e, consequentemente, a debilitação da segurança do sistema.


## Q3
Relativamente ao impacto do Ataque em AES-CTR, o ataque em si não é muito impactante, no sentido em que o modo de operação CTR é mais resistente a alterações no criptograma. Com isto, queremos dizer que a alteração de um byte específico afetaria apenas esse byte na mensagem decifrada, sem afetar outros blocos.
Em relação ao impacto do Ataque em AES-CBC, a situação é diferente. Uma alteração num bloco afeta diretamente o bloco decifrado correspondente e pode causar um efeito de propagação, alterando blocos subsequentes, ou seja, um byte alterado pode afetar mais que um bloco, resultando em blocos decifrados diferentes do esperado.
