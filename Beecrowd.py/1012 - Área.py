PI = 3.14159
a, b, c = map(float, input().split())

triangulo = a*c/2.0
circulo = PI*(c**2)
trapezio = ((a+b)*c)/2.0
quadrado = b**2
retangulo = a*b

print(f"""TRIANGULO: {triangulo:.3f}
CIRCULO: {circulo:.3f}
TRAPEZIO: {trapezio:.3f}
QUADRADO: {quadrado:.3f}
RETANGULO: {retangulo:.3f}""")
