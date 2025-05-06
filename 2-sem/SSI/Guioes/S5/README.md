# Respostas das Questões

## Q1

O programa *chacha20_int_attck.py*, desenvolvido na aula anterior, não foi capaz de comprometer uma mensagem cifrada com o *pbenc_chacha20_poly1305*. Isto deve se ao facto de todas as mensagens cifradas com o novo programa serem também autenticadas pelo algoritmo. Desta forma, como o ataque, de forma resumida, altera os __bits__ da cifra de modo a modificar o sentido original da mensagem, uma assinatura que garanta a integridade da mensagem, não impede que o ataque seja realizado, mas impede o recetor de aceitar a mensagem recebida como uma mensagem segura.

## Q2
É sugerida a utilização de 'm2' com mais de 16 bytes, pois a solução envolve utilizar os primeiros 16 bytes de 'm2' para realizar um XOR com a 'tag1', tamanho estritamente necessário dado o comprimento da tag. Essa limitação pode ser contornada ao modificar o tamanho do bloco no método de cifragem, e consequentemente o tamanho da tag, contudo 'm2' terá de ter sempre, no mínimo, tamanho igual a 1 bloco.