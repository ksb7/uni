function pas = figpas(fig, pas)
  t = [0:pas:pi];
  t1 = 1;
  [x,y,z] = xyz(t);
  [x1,y1,z1] = xyz(t1);
  figure(fig);
  plot3(x, y, z, x1, y1, z1, '*');
  xlabel('x');
  ylabel('y');
  zlabel('z');
  title('t = 1');
  legend('Traiectoria punctului material', 'Pozitia punctului t');
