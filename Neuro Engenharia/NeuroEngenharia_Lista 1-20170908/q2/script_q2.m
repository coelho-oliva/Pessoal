%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% script_q2.m
%%% by Antonio Padilha L. Bo (antonio.plb@lara.unb.br)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% before everything
clc; close all; clear all

applyNoise = 0;

%% simulation timing

% basic properties
signal = struct;
signal.fs = 1000; % sampling frequency [Hz]
signal.Ts = 1/signal.fs; % sampling period [s]
signal.Tf = 1; % total simulation time [s]
signal.N = signal.Tf * signal.fs + 1; % total samples

% time vector
time = (0:signal.Ts:signal.Tf);

%% simulation for range of input current
for i = 1:25
    
    %% input current
    
    inputCurrent = ones(1,signal.N) * 10e-6 * i;
    
    if applyNoise
    end
    
    %% lif simulation
    
    voltageMembrane = nome_q2(time, inputCurrent, signal);
    
    %% interspike histogram

    figure
    % your interspike histogram code here
    
    ylabel('Frequency of events');
    xlabel('Interspike interval [s]');
    title(num2str(i));
    hold on;

    %% plotting
    
    figure;
    subplot(211); plot(time,voltageMembrane);
    subplot(212); plot(time,inputCurrent);
    
    pause(.8);
    input('Press any key to move on');

end