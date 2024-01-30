function [x,y,z] = xyz(t)
  x = (e.^t).*sin(2.*t);
  y = t.*(1.+cos(t));
  z = 1.3*(t.^(1.2));
