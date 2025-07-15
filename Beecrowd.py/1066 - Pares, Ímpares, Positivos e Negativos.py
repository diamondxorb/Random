cont_pares = 0
cont_posit = 0
cont_negat = 0

for i in range(5):
    numero = int(input())
    if(numero%2==0):
        cont_pares+=1
    if(numero>0):
        cont_posit+=1
    elif(numero<0):
        cont_negat+=1

print(f"""{cont_pares} valor(es) par(es)
{5-cont_pares} valor(es) impar(es)
{cont_posit} valor(es) positivo(s)
{cont_negat} valor(es) negativo(s)""")
