%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% script_q1.m
%%% by Antonio Padilha L. Bo (antonio.plb@lara.unb.br)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% before everything
close all; clear all; clc;

%% loading data
load spikedectection_easypractice.mat; flagSpikeSorting = 0;
%load spikedectection_hardpractice.mat; flagSpikeSorting = 0;
%load spikesorting_practice.mat; flagSpikeSorting = 1;

%% spike detection
if ~flagSpikeSorting
    detectedSpikes = nome_q1a(time, electrodeVoltage, signal);
    
    % showing detection results
    disp(' ');
    disp('## Results');
    disp(['detectedSpikes = ', int2str(length(detectedSpikes))]);
    disp(['actualSpikes = ', int2str(length(actualSpikes))]);
    disp(' ');
end

%% spike sorting
if flagSpikeSorting
    [detectedSpikesA, detectedSpikesB] = nome_q1d(time, electrodeVoltage, signal);
end

input('Press any key to move on');

%% plot raster
% adapt the next plotting function for flagSpikeSorting
nome_q1b(time, electrodeVoltage, detectedSpikes, signal);

input('Press any key to move on');

%% plot individual spike
% adapt the next plotting function for flagSpikeSorting
nome_q1c(time, electrodeVoltage, detectedSpikes, signal);

%% the end