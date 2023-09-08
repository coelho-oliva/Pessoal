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
massa_placa = 10.2; 	#g
A_placa = 40.54; 		#mm
B_placa = 40.14; 		#mm
diametro_placa = 10.30; #mm
espessura_placa = 2.51; #mm

# Erros Instrumentais
ErroBalanca = 0.1 		#g
ErroPaquimetro = 0.05 	#mm
ErroMicrometro = 0.01 	#mm

# Volume e densidade calculados
volume_placa = A_placa*B_placa*espessura_placa - (np.pi/4)*(diametro_placa*diametro_placa)*espessura_placa;
rho_placa = massa_placa/volume_placa * 1000 # densidade em g/cm³

# Incerteza do volume da placa
alpha = A_placa*B_placa*espessura_placa
DeltaAlpha = alpha*((ErroPaquimetro/A_placa)+ (ErroPaquimetro/B_placa) + (ErroMicrometro/espessura_placa))
beta = (espessura_placa*diametro_placa**2)*np.pi/4
DeltaBeta = (beta*np.pi/4)*((ErroMicrometro/espessura_placa) + 2*(ErroPaquimetro/diametro_placa))
DeltaV = DeltaAlpha + DeltaBeta

# Erro da densidade do alumínio
DeltaRho_placa = rho_placa*(ErroBalanca/massa_placa + DeltaV/volume_placa)

print("_______________________________________________________")
print("||Volume da placa de alumínio ~ {:.2f}".format(volume_placa) + "+- {:.0f}".format(DeltaV) + "mm³||")
print("||Densidade do alumínio ~ {:.2f}".format(rho_placa) + " +- {:.2f}".format(DeltaRho_placa) + "g/cm³||")
print("_______________________________________________________")
#print("Densidade rho_placa ~ ""{:.1f}".format(rho_placa) + "g/cm³")
#print("DeltaRho_placa = ""{:.2f}".format(DeltaRho_placa) + "g/cm³")

# Erro aleatório das medidas (desvio padrão)
LadoA_placa_medidas = np.array([40.80, 40.30, 40.60, 40.50, 40.50])
LadoB_placa_medidas = np.array([40.10, 40.00, 40.20, 40.10, 40.30])
Diametro_placa_medidas = np.array([10.20, 10.50, 10.40, 10.30, 10.10])
Massa_placa_medidas = np.array([10.20, 10.20, 10.20, 10.20, 10.20])
Espessura_placa_medidas = np.array([2.51, 2.52, 2.51, 2.51, 2.51])

LadoA_placa_dp = np.std(LadoA_placa_medidas)
LadoB_placa_dp = np.std(LadoB_placa_medidas)
Massa_placa_dp = np.std(Massa_placa_medidas)
Diametro_placa_dp = np.std(Diametro_placa_medidas)
Espessura_placa_dp = np.std(Espessura_placa_medidas)

print("|> Desvio padrão (Lado A) = {:.2f} mm".format(LadoA_placa_dp))
print("|> Desvio padrão (lado A) = {:.2f} mm".format(LadoB_placa_dp))
print("|> Desvio padrão (massa) = {:.2f} g".format(Massa_placa_dp))
print("|> Desvio padrão (diâmetro) = {:.5f} mm".format(Diametro_placa_dp))
print("|> Desvio padrão (espessura) = {:.5f} mm".format(Espessura_placa_dp))
print("_______________________________________________________")
















# Cilindro **********************************************************************
print("\n*********************CILINDRO*********************")
massa_cilindro = 21.0 	#g
altura_cilindro = 40.20 #mm
dint_cilindro = 25.64 	#mm
dext_cilindro = 33.33 	#mm 

volume_cilindro = (np.pi/4)*(dext_cilindro**2 - dint_cilindro**2)*altura_cilindro #mm³
rho_cilindro = 1000*massa_cilindro/volume_cilindro #g/cm³

# Erro do volume do cilindro
DeltaV_cilindro = (ErroPaquimetro*(np.pi**2)/8)*((1/2)*((dext_cilindro**2) + (dint_cilindro**2)) + altura_cilindro*(dext_cilindro + dint_cilindro))

# Erro da densidade do cilindro
DeltaRho_cilindro = rho_cilindro*((ErroBalanca/massa_cilindro) + (DeltaV_cilindro/volume_cilindro))
print ("\n********DENSIDADE DO PVC********")
print("_______________________________________________________")
print("Volume do cilindro = ""{:.2f}".format(volume_cilindro) + " +- ""{:.2f}".format(DeltaV_cilindro) + "mm³")
print("Densidade do PVC = ""{:.2f}".format(rho_cilindro) + " +- ""{:.2f}".format(DeltaRho_cilindro) + "g/cm³")
print("_______________________________________________________")


# Erro aleatório das medidas (desvio padrão)
Altura_cilindro_medidas = np.array([40.10, 40.20, 40.25, 40.20, 40.25])
DiametroInt_cilindro_medidas = np.array([25.70, 25.50, 25.70, 25.70, 25.60])
DiametroExt_cilindro_medidas = np.array([33.30, 33.30, 33.35, 33.40, 33.30])
Massa_cilindro_medidas = np.array([21.0, 21.0, 21.0, 21.0, 21.0])
Espessura_cilindro_medidas = np.array([4.27, 4.28, 4.28, 4.06, 4.09])

Altura_cilindro_dp = np.std(Altura_cilindro_medidas)
DiametroInt_cilindro_dp = np.std(DiametroInt_cilindro_medidas)
DiametroExt_cilindro_dp = np.std(DiametroExt_cilindro_medidas)
Massa_cilindro_dp = np.std(Massa_cilindro_medidas)
Espessura_cilindro_dp = np.std(Espessura_cilindro_medidas)

print("|> Desvio padrão (altura) = {:.2f} mm".format(Altura_cilindro_dp))
print("|> Desvio padrão (diâmetro interno) = {:.2f} mm".format(DiametroInt_cilindro_dp))
print("|> Desvio padrão (diâmetro externo) = {:.2f} mm".format(DiametroExt_cilindro_dp))
print("|> Desvio padrão (massa) = {:.2f} g".format(Massa_cilindro_dp))
print("|> Desvio padrão (espessura) = {:.3f} mm".format(Espessura_cilindro_dp))
print("_______________________________________________________")
