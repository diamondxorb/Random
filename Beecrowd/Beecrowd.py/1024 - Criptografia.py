numero = int(input())

for _ in range(numero):
    frase = input()
    resposta = ""
    i = 0
    tamanho = len(frase)
    if(tamanho%2!=0):
        tamanho = (tamanho//2)+1
    else:
        tamanho = tamanho//2
    for letra in frase:
        i+=1
        if(i<=tamanho):
            if(letra.isalpha()):
                resposta+=chr(ord(letra)+2)
            else:
                resposta+=chr(ord(letra)-1)
        else:
            if(letra.isalpha()):
                resposta+=chr(ord(letra)+3)
            else:
                resposta+=letra
    resposta = resposta[::-1]
    print(resposta)
