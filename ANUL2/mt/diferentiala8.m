function dxdt = diferentiala8(t,x)
  h = 2;
  h1 = 7;
  w0 = 10;
  p = 10;
  dxdt = zeros(2,1);
  dxdt(1) = x(2);
  dxdt(2) = -2.*h.*x(2)-w0.^2.*x(1)+h1.*sin(p*t);
