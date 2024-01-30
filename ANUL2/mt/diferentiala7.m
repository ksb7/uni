function dxdt = diferentiala7(t,x)
  h = 7;
  w0 = 10;
  p = 10;
  dxdt = zeros(2,1);
  dxdt(1) = x(2);
  dxdt(2) = -w0.^2.*x(1)+h.*sin(p.*t);
