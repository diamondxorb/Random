codigo_1, quant_1, valor_1 = map(float, input().split())
codigo_2, quant_2, valor_2 = map(float, input().split())

preco = (quant_1*valor_1)+(quant_2*valor_2)

print(f"VALOR A PAGAR: R$ {preco:.2f}")
