function dxdt = diferentiala1(t,x)
  w0 = 10;
  dxdt = zeros(2,1);
  dxdt(1) = x(2);
  dxdt(2) = -w0.^2.*x(1);
