%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% nome_q2.m
%%% Matlab function to simulate spiking neurons
%%% by Antonio Padilha L. Bo (antonio.plb@lara.unb.br)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function vMembrane = antonio_q2(time, inputCurrent, signal)

%% basic parameters
% vSpike = % [V]
% vRest = % [V]
% vThreshold = % [V]
% RMembrane = % [ohm]
% CMembrane = % [F]
% tauMembrane = % time constant [s]
% tauRefractory = % refractory period [s]

%% output variable
vMembrane = zeros(1, signal.N);

%% your LIF simulation code here
for k = 2:signal.N

end

end
