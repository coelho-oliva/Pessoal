#!/usr/bin/env python3
'''
autor: 		Caio Eduardo Coelho de Oliveira
linguagem:	Python 3.6.7
descrição:	
	Este programa resolve problemas de solução de raízes de funções utilizando dois métodos:
		1. Bissecção;
		2. De Newton.
	Funções analisadas:
		1. f(x) = x  - arctg(x)
		2. g(x) = x² - sen(x)
'''
import numpy as np 
import matplotlib.pyplot as plt
from   scipy.misc import derivative

def f(x):
	return (x - np.arctan(x))
def g(x):
	return (x**2 - np.sin(x))
def bisseccao (funcao, x_esquerda, x_direita, tolerancia):
	print ('Método da bissecção para ', funcao)
	x_central = (x_esquerda + x_direita)/2.0
	i = 1
	while (np.abs(x_esquerda - x_direita) >= tolerancia):
		x_central = (x_esquerda + x_direita)/2.0
		prod = funcao(x_esquerda)*funcao(x_central)
		print ('x_{} = {:.8f}'.format(i, x_central))
		if   prod > tolerancia:
			x_esquerda = x_central
		elif prod < tolerancia:
			x_direita = x_central
		i = i + 1
	return x_central
def x_next (funcao, x_n):
	derivada = derivative(funcao, x_n, dx = 0.1)
	return	 x_n - (funcao(x_n)/derivada)
def newton (funcao, x_n, iteracoes):
	print ('Método de Newton para a função ', funcao)
	for i in range(iteracoes):
		print ('x_{} = {:.8f}'.format(i+1, x_n))
		x_n = x_next(funcao, x_n)
	return x_n
true  = 1
false = 0
try:
	input ('Olá! Serão analisadas as seguintes funções:\nf(x) = x - arctg(x)\ng(x) = x² - sen(x)')
except:
	pass
print ('Para o método da bissecção, com quais valores de x_esquerda, x_direita e tolerância que você gostaria de iniciar?')

try:
	x_esquerda = float(input("x_esquerda = "))
	x_direita  = float(input("x_direita  = "))
	tolerancia = np.abs(float(input("tolerância(Exemplos: 1e-10; 0.0000001) = ")))
	print ('OK. Agora, para o método de Newton, defina o x inicial e a quantidade de iterações desejadas.')
	x_n = float(input("x_inicial = "))
	iteracoes = int(input("iterações desejadas = "))

except:
	print("Algo deu errado! Por favor, digite algum número (Exemplo: -19; 45.)")
	exit()

respostaFx = bisseccao(f, x_esquerda, x_direita, tolerancia)
respostaGx = bisseccao(g, x_esquerda, x_direita, tolerancia)
auxFx = respostaFx
auxGx = respostaGx

respostaFx = newton(f, x_n, iteracoes)
respostaGx = newton(g, x_n, iteracoes)

#Resultados
print ('Resumo -------------------------')
print ('1. Funções analisadas:\nf(x) = x - arctg(x)\ng(x) = x² - sen(x)')
print ("2. Resposta para o método da bissecção(x_esquerda = {:.3f}; x_direita = {:.3f})".format(x_esquerda, x_direita))
print ('Zero de f = {:.8f}'.format(auxFx))
print ('Zero de g = {:.8f}'.format(auxGx))
print ("3. Resposta para o método de Newton(x_inicial = {:.3f}; iterações: {:d})".format(x_n, iteracoes))
print ('Zero de f = {:.8f}'.format(respostaFx))
print ('Zero de g = {:.8f}'.format(respostaGx))
try:
	input("4. Aperte qualquer tecla para ver os gráficos das funções")
except:
	pass
x   = np.arange(-5.0, 5.0, 0.01)

plt.plot(x, f(x), 'p', label = 'x - arctg(x)')
plt.plot(x, g(x), 'y', label = 'x² - sen(x)')
plt.title("Funções f e g")
plt.xlabel('x')
plt.ylabel('y')
plt.grid()
plt.legend()
plt.show()