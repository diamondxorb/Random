numero = int(input())
numero+=1

for i in range(numero):
    if(i%2==0 and i!=0):
        print(f"{i}^2 = {i**2}")
