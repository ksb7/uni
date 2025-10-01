library ieee;
use ieee.std_logic_1164.all;

entity Lab2 is
    port (
        x0, x1, x2, x3: in std_logic;
        F: out std_logic
    );
end Lab2;

architecture fluxdate of Lab2 is
   
    signal NOT_1_out: std_logic;

    signal AND2_0_out, AND3_0_out, AND3_1_out: std_logic;
begin
  
    NOT_1_out <= not x3;
   
	
    AND2_0_out <= x1 and x2;

   
    AND3_0_out <= x0 and x2 and x3;

 
    AND3_1_out <= x0 and x1 and NOT_1_out;

    F <= AND2_0_out or AND3_0_out or AND3_1_out;

end fluxdate;