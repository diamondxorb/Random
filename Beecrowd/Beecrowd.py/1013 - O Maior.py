a, b, c = map(int, input().split())

if(a>b):
    maiorab = a
else:
    maiorab = b

if(c>maiorab):
    maiorab = c

print(f"{maiorab} eh o maior")
