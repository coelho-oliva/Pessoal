# Cálculo dos erros experimentais e aleatórios do experimento de medição
# Data do experimento: 01set23
# Atualizado em: 08set23
# autor: Caio Coelho (github: coelho.oliva)
###

import numpy as np;

# Placa Metalica **********************************************************************
# Dados em mm e g

print("*********************PLACA DE ALUMÍNIO*********************")

massa_placa = 10.2; #g
A_placa = 40.54; B_placa = 40.14; diametro_placa = 10.30; espessura_placa = 2.51; #mm

volume_placa = A_placa*B_placa*espessura_placa - (np.pi/4)*(diametro_placa*diametro_placa)*espessura_placa;
# print("Volume da placa perfurada = ""{:.4f}".format(volume_placa) + " mm³")

rho_placa = massa_placa/volume_placa * 1000 # densidade em g/cm³
# print("Densidade calculada do alumínio = ""{:.4f}".format(rho_placa) + " g/cm³")

# Erros Instrumentais
ErroBalanca = 0.1 #g
ErroPaquimetro = 0.05 #mm
ErroMicrometro = 0.01 #mm

# Erro do volume da placa
alpha = A_placa*B_placa*espessura_placa
DeltaAlpha = alpha*((ErroPaquimetro/A_placa)+ (ErroPaquimetro/B_placa) + (ErroMicrometro/espessura_placa))
beta = (espessura_placa*diametro_placa**2)*np.pi/4
DeltaBeta = (beta*np.pi/4)*((ErroMicrometro/espessura_placa) + 2*(ErroPaquimetro/diametro_placa))
# print ("\n********VOLUME DA PLACA********")
# print ("\nConsiderando que \nV = A.B.L - (PI.D².L)/4 = alpha - beta")
# print("\nValor de alpha = A.B.L = ""{:.4f}".format(alpha) + " mm³")
# print("DeltaAlpha = ""{:.1f}".format(DeltaAlpha) + "mm³")
# print("Valor de beta = L.pi.D²/4 = ""{:.4f}".format(beta) + " mm³")
# print("DeltaBeta = ""{:.1f}".format(DeltaBeta) + "mm³")
# print("\nComo DeltaV = DeltaAlpha + DeltaBeta, então:")

DeltaV = DeltaAlpha + DeltaBeta

# Erro da densidade do alumínio
DeltaRho_placa = rho_placa*(ErroBalanca/massa_placa + DeltaV/volume_placa)

print("_______________________________________________________")
print("||Volume da placa de alumínio ~ ""{:.2f}".format(volume_placa) + " +- ""{:.0f}".format(DeltaV) + "mm³||")
print("||Densidade do alumínio ~ ""{:.2f}".format(rho_placa) + " +- ""{:.2f}".format(DeltaRho_placa) + "g/cm³||")
print("_______________________________________________________")
#print("Densidade rho_placa ~ ""{:.1f}".format(rho_placa) + "g/cm³")
#print("DeltaRho_placa = ""{:.2f}".format(DeltaRho_placa) + "g/cm³")


# Cilindro **********************************************************************
print("\n*********************CILINDRO*********************")
massa_cilindro = 21.0 #g
altura_cilindro = 40.20 #mm
dint_cilindro = 25.64 #mm
dext_cilindro = 33.33 #mm 

volume_cilindro = (np.pi/4)*(dext_cilindro**2 - dint_cilindro**2)*altura_cilindro #mm³
rho_cilindro = 1000*massa_cilindro/volume_cilindro #g/cm³

# Erro do volume do cilindro
DeltaV_cilindro = ((np.pi**2)/8)*((ErroMicrometro/2)*((dext_cilindro**2) + (dint_cilindro**2)) + altura_cilindro*ErroPaquimetro*(dext_cilindro + dint_cilindro))

# Erro da densidade do cilindro
DeltaRho_cilindro = rho_cilindro*((ErroBalanca/massa_cilindro) + (DeltaV_cilindro/volume_cilindro))
print ("\n********DENSIDADE DO PVC********")
print("_______________________________________________________")
print("Volume do cilindro = ""{:.2f}".format(volume_cilindro) + " +- ""{:.3f}".format(DeltaV_cilindro) + "mm³")
print("Densidade do PVC = ""{:.2f}".format(rho_cilindro) + " +- ""{:.3f}".format(DeltaRho_cilindro) + "g/cm³")
print("_______________________________________________________")

