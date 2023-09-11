#**************************************************************************************
# Cálculo dos erros experimentais e aleatórios do experimento de medição
#     Data do experimento: 01set23
# 			Atualizado em: 08set23
# 					autor: Caio Coelho (github: coelho-oliva)
#      Alterações futuras: utilizar estrutura para anotar as dimensoes da placa e do cilindro. Montar gráfico com as medições e barras de erros.
#**************************************************************************************

import numpy as np;

# Placa Metalica **********************************************************************
# Dados em mm e g

print("*********************PLACA DE ALUMÍNIO*********************")

# Medições
LadoA_placa_medidas = np.array([40.80, 40.30, 40.60, 40.50, 40.50])
LadoB_placa_medidas = np.array([40.10, 40.00, 40.20, 40.10, 40.30])
Diametro_placa_medidas = np.array([10.20, 10.50, 10.40, 10.30, 10.10])
Massa_placa_medidas = np.array([10.20, 10.20, 10.20, 10.20, 10.20])
Espessura_placa_medidas = np.array([2.51, 2.52, 2.51, 2.51, 2.51])

LadoA_placa_media 		= np.mean(LadoA_placa_medidas) 			#mm
LadoB_placa_media		= np.mean(LadoB_placa_medidas) 			#mm
Diametro_placa_media 	= np.mean(Diametro_placa_medidas) 		#mm
Massa_placa_media 		= np.mean(Massa_placa_medidas) 			#g
Espessura_placa_media 	= np.mean(Espessura_placa_medidas) 	#mm

# Erros Instrumentais
ErroBalanca = 0.1 		#g
ErroPaquimetro = 0.05 	#mm
ErroMicrometro = 0.01 	#mm

# Erro aleatório das medidas (desvio padrão)
LadoA_placa_dp 		= np.std(LadoA_placa_medidas)
LadoB_placa_dp 		= np.std(LadoB_placa_medidas)
Massa_placa_dp 		= np.std(Massa_placa_medidas)
Diametro_placa_dp 	= np.std(Diametro_placa_medidas)
Espessura_placa_dp 	= np.std(Espessura_placa_medidas)

# Erros experimentais
LadoA_placa_erro 		= ErroPaquimetro + LadoA_placa_dp
LadoB_placa_erro 		= ErroPaquimetro + LadoB_placa_dp
Diametro_placa_erro 	= ErroPaquimetro + Diametro_placa_dp
Massa_placa_erro 		= ErroBalanca 	 + Massa_placa_dp
Espessura_placa_erro 	= ErroMicrometro + Espessura_placa_dp

# Volume e incerteza da placa em mm³
Volume_placa = Espessura_placa_media*(LadoA_placa_media*LadoB_placa_media - (np.pi/4)*(Diametro_placa_media**2))
Volume_placa_erro = Espessura_placa_media*(LadoB_placa_media*LadoA_placa_erro + LadoA_placa_media*LadoB_placa_erro) 
+ Espessura_placa_erro*(LadoA_placa_media*LadoB_placa_media + ((np.pi**2)/16)*(Diametro_placa_media**2))
+ Diametro_placa_erro*((np.pi**2)/8)*Diametro_placa_media*Espessura_placa_media

# Erro e incerteza da densidade do alumínio em g/cm³
Rho_placa = 1000*Massa_placa_media/Volume_placa # densidade em g/cm³
Rho_placa_erro = 1000*((Massa_placa_erro/Volume_placa)+((Volume_placa_erro*Massa_placa_media)/(Volume_placa**2)))


print("\n|> Desvio padrão (Lado A) = {:.2f} mm".format(LadoA_placa_dp))
print("|> Desvio padrão (Lado B) = {:.2f} mm".format(LadoB_placa_dp))
print("|> Desvio padrão (Diâmetro) = {:.3f} mm".format(Diametro_placa_dp))
print("|> Desvio padrão (Massa) = {:.1f} g".format(Massa_placa_dp))
print("|> Desvio padrão (Espessura) = {:.5f} mm".format(Espessura_placa_dp))
print("|> Erro experimental (Lado A) = {:.2f} mm".format(LadoA_placa_erro))
print("|> Erro experimental (Lado B) = {:.2f} mm".format(LadoB_placa_erro))
print("|> Erro experimental (Diametro) = {:.2f} mm".format(Diametro_placa_erro))
print("|> Erro experimental (Massa) = {:.1f} g".format(Massa_placa_erro))
print("|> Erro experimental (Espessura) = {:.2f} mm".format(Espessura_placa_erro))


print("_______________________________________________________")
print("Resultados Experimentais")

print("|> Lado A ~ {:.2f}".format(LadoA_placa_media) 		+ " +- {:.2f}".format(LadoA_placa_erro) + "mm||")
print("|> Lado B ~ {:.2f}".format(LadoB_placa_media) 		+ " +- {:.2f}".format(LadoB_placa_erro) + "mm||")
print("|> Diâmetro ~ {:.2f}".format(Diametro_placa_media) 	+ " +- {:.2f}".format(Diametro_placa_erro) + "mm||")
print("|> Massa ~ {:.2f}".format(Massa_placa_media) 			+ " +- {:.2f}".format(Massa_placa_erro) + "g||")
print("|> Espessura  ~ {:.2f}".format(Espessura_placa_media) + " +- {:.2f}".format(Espessura_placa_erro) + "mm||")

print("|> Volume da placa de alumínio ~ {:.2f}".format(Volume_placa) + "+- {:.0f}".format(Volume_placa_erro) + "mm³||")
print("|> Densidade estimada do alumínio ~ {:.2f}".format(Rho_placa) + " +- {:.2f}".format(Rho_placa_erro) + "g/cm³||")
print("_______________________________________________________")



# Cilindro **********************************************************************
print("\n*********************CILINDRO*********************")

# Medições
Altura_cilindro_medidas 		= np.array([40.10, 40.20, 40.25, 40.20, 40.25])
DiametroInt_cilindro_medidas 	= np.array([25.70, 25.50, 25.70, 25.70, 25.60])
DiametroExt_cilindro_medidas 	= np.array([33.30, 33.30, 33.35, 33.40, 33.30])
Massa_cilindro_medidas 			= np.array([21.0, 21.0, 21.0, 21.0, 21.0])
Espessura_cilindro_medidas 		= np.array([4.27, 4.28, 4.28, 4.06, 4.09])

Altura_cilindro_media 			= np.mean(Altura_cilindro_medidas)
DiametroInt_cilindro_media 		= np.mean(DiametroInt_cilindro_medidas)
DiametroExt_cilindro_media 		= np.mean(DiametroExt_cilindro_medidas)
Massa_cilindro_media 			= np.mean(Massa_cilindro_medidas)
Espessura_cilindro_media 		= np.mean(Espessura_cilindro_medidas)

# Erro aleatório das medidas (desvio padrão)
Altura_cilindro_dp 		= np.std(Altura_cilindro_medidas)
DiametroInt_cilindro_dp = np.std(DiametroInt_cilindro_medidas)
DiametroExt_cilindro_dp = np.std(DiametroExt_cilindro_medidas)
Massa_cilindro_dp 		= np.std(Massa_cilindro_medidas)
Espessura_cilindro_dp 	= np.std(Espessura_cilindro_medidas)

# Erro experimental
Altura_cilindro_erro 		= ErroPaquimetro + Altura_cilindro_dp
DiametroInt_cilindro_erro 	= ErroPaquimetro + DiametroInt_cilindro_dp
DiametroExt_cilindro_erro 	= ErroPaquimetro + DiametroExt_cilindro_dp
Massa_cilindro_erro 		= ErroBalanca	 + Massa_cilindro_dp
Espessura_cilindro_erro 	= ErroMicrometro + Espessura_cilindro_dp

# Volume e incerteza do cilindro em mm³
Volume_cilindro 		= Altura_cilindro_media*(np.pi/4)*(DiametroExt_cilindro_media
	- DiametroInt_cilindro_media)*(DiametroExt_cilindro_media + DiametroInt_cilindro_media)
Volume_cilindro_erro 	= ((np.pi/4)**2)*(Altura_cilindro_erro*(DiametroExt_cilindro_media**2 - DiametroInt_cilindro_media**2) 
	+(Altura_cilindro_media*(DiametroExt_cilindro_erro + DiametroInt_cilindro_erro)*2*(DiametroExt_cilindro_media)))

# Densidade e incerteza do PVC em g/cm³
Rho_cilindro 		= 1000*Massa_cilindro_media/Volume_cilindro
Rho_cilindro_erro 	= 1000*((Massa_cilindro_erro/Volume_cilindro)+((Volume_cilindro_erro*Massa_cilindro_media)/(Volume_cilindro**2)))

print("\n|> Desvio padrão (Altura) = {:.2f} mm".format(Altura_cilindro_dp))
print("|> Desvio padrão (Diâmetro Interno) = {:.2f} mm".format(DiametroInt_cilindro_dp))
print("|> Desvio padrão (Diâmetro Externo) = {:.3f} mm".format(DiametroExt_cilindro_dp))
print("|> Desvio padrão (Massa) = {:.1f} g".format(Massa_cilindro_dp))
print("|> Desvio padrão (Espessura) = {:.2f} mm".format(Espessura_cilindro_dp))
print("|> Erro experimental (Altura) = {:.2f} mm".format(Altura_cilindro_erro))
print("|> Erro experimental (Diâmetro Interno) = {:.2f} mm".format(DiametroInt_cilindro_erro))
print("|> Erro experimental (Diametro Externo) = {:.2f} mm".format(DiametroExt_cilindro_erro))
print("|> Erro experimental (Massa) = {:.1f} g".format(Massa_cilindro_erro))
print("|> Erro experimental (Espessura) = {:.2f} mm".format(Espessura_cilindro_erro))
print("_______________________________________________________")
print("Resultados Experimentais")

print("|> Altura ~ {:.2f}".format(Altura_cilindro_media) 		+ " +- {:.2f}".format(Altura_cilindro_erro) + "mm||")
print("|> Diâmetro Interno ~ {:.2f}".format(DiametroInt_cilindro_media) 		+ " +- {:.2f}".format(DiametroInt_cilindro_erro) + "mm||")
print("|> Diâmetro Externo ~ {:.2f}".format(DiametroExt_cilindro_media) 	+ " +- {:.2f}".format(DiametroExt_cilindro_erro) + "mm||")
print("|> Massa ~ {:.2f}".format(Massa_cilindro_media) 			+ " +- {:.2f}".format(Massa_cilindro_erro) + "g||")
print("|> Espessura  ~ {:.2f}".format(Espessura_cilindro_media) 		+ " +- {:.2f}".format(Espessura_cilindro_erro) + "mm||")

print("|> Volume do cilindro de PVC ~ {:.2f}".format(Volume_cilindro) + "+- {:.0f}".format(Volume_cilindro_erro) + "mm³||")
print("|> Densidade estimada do PVC ~ {:.2f}".format(Rho_cilindro) + " +- {:.2f}".format(Rho_cilindro_erro) + "g/cm³||")
print("_______________________________________________________")
