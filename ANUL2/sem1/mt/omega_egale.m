function[x,y] = omega_egale(t,dalfa)
a1 = 15;
a2 = 23;
omega1 = 2;
omega2 = 2;
alfa1 = pi/13;
alfa2 = alfa1 - dalfa;
x = a1*sin(omega1*t+alfa1);
y = a2*sin(omega2*t+alfa2);

