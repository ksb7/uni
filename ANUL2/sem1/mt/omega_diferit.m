function[x,y] = omega_diferit(t,dalfa)
a1 = 15;
a2 = 23;
omega1 = 2;
omega2 = omega1+4;
alfa1 = dalfa - pi/2;
alfa2 = dalfa - pi/2;
x = a1*sin(omega1*t+alfa1);
y = a2*sin(omega2*t+alfa2);

