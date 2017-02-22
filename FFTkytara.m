clear all;clc;close all;
[a,b] = audioread('nahranipokus2.wav');
plot((fft(a,b)));