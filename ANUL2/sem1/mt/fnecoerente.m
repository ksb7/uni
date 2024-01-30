function[x1,x2,x] = fnecoerente(t)
a1 = 10;
a2 = 20;
omega1 = 19;
omega2 = 5;
alfa1 = pi/7;
alfa2 = 3*pi/10;
x1 = a1*sin(omega1*t+alfa1);
x2 = a2*sin(omega2*t+alfa2);
x = x1+x2;

