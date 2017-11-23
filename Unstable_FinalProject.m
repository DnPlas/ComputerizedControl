clc
clear

% ---------- SYSTEM ---------- %
numerator = [1 2.2];
denominator = [1 -5.7 9];
Gs = tf(numerator,denominator);
fc = 12.4;
fs = fc*7;
T = 2*pi/fs;
Ts = round(T,2); % The sampling time must be rounded up (2 decimal places)
Gz = c2d(Gs, Ts);
kp_system = numerator(2)/denominator(3);

% ---------- P CONTROLLER ---------- %
p_gain = 12;

% ---------- PI CONTROLLER ---------- %
c_pi = 25;
z1_pi = 0.7;
polynomial_pi = c_pi*[1 z1_pi];
pgain_pi = polynomial_pi(2);
igain_pi = polynomial_pi(1)- pgain_pi;

% ---------- PD CONTROLLER ---------- %
c_pd = 18;
z1_pd = 0.2;
polynomial_pd = c_pd*[1 z1_pd];
dgain_pd = polynomial_pd(2);
pgain_pd = polynomial_pd(1)- dgain_pd;

% ---------- PID CONTROLLER ---------- %
%%---------- EXPANDING THE POLYNOMIAL ----------%%
z1 = 0.45;
z2 = 0.06;
c_pid = 35;
polynomial = c_pid*[1 -(z1+z2) z1*z2];

%%---------- GETTING kd, kc, ki ----------%%
kd = polynomial(3);
kc = -polynomial(2)-(2*kd);
ki = polynomial(1) - kd - kc;

%%---------- >>LEAD COMPENSATOR<< ----------%%
%---------- ZPK ----------%
zero = 0.2;
pole = -0.03;
gain = 20;
Cz = zpk(zero, pole, gain, Ts);
kp_lead = gain*((1-zero)/(1-pole));

%%---------- >>LAG COMPENSATOR<< ----------%%
ess = 0.05;
syms k;
eqn = ess == 1/(1+(kp_system*kp_lead*k));
kp_lag = vpasolve(eqn, k);
kp_lag = double(kp_lag);
kp_lag = round(kp_lag,1);

% Calculate the compensator expression
syms a_2;
eqn = (1-a_2)/(1-0.99) == kp_lag;
a_2 = vpasolve(eqn, a_2);
a_2 = double(a_2);

%---------- ZPK ----------%
zeros = [zero, a_2];
poles = [pole, 0.99];
C2z = zpk(zeros, poles, gain, Ts);

