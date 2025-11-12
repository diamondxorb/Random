contagem = 0
media = 0

for i in range(6):
    numero = float(input())
    if numero>0:
        media+=numero
        contagem+=1

media/=contagem

print(f"{contagem} valores positivos")
print(f"{media:.1f}")
