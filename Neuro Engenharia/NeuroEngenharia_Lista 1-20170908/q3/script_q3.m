%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% script_q3.m
%%% by Antonio Padilha L. Bo (antonio.plb@lara.unb.br)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% before everything
close all; clear all; clc;

%% loading data
load emg_practice.mat; flagEMG = 1; flagEEG = 0; flagClassifyEEG = 0;
%load eeg_practice.mat; flagEEG = 1; flagEMG = 0; flagClassifyEEG = 0;
%load eeg_practice.mat; flagEEG = 0; flagEMG = 0; flagClassifyEEG = 1;

%% EMG
if flagEMG
    emgProcessedVoltage = nome_q3a(time, emgVoltage, signal);
end

%% EEG
if flagEEG
    [delta, theta, alpha, beta, gamma] = nome_q3b(time, eegVoltage, signal);
end

%% EEG classification

if flagEEG
    classificationResult = nome_q3c(time, eegVoltage, signal);
end

input('Press any key to move on');

%% plot 
figure;
if flagEMG

    subplot(211); plot(time, emgVoltage);
    subplot(212); plot(time, emgProcessedVoltage);
    
end
if flagEEG
    
    subplot(611); plot(time, eegVoltage);
    subplot(612); plot(time, delta);
    subplot(613); plot(time, theta);
    subplot(614); plot(time, alpha);
    subplot(615); plot(time, beta);
    subplot(616); plot(time, gamma);
    
end

%% the end