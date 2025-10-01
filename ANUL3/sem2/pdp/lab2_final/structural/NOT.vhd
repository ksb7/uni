library ieee;
use ieee.std_logic_1164.all;

entity Gate_NOT is
    port (
        x : in std_logic; 
        F : out std_logic  
    );
end Gate_NOT;

architecture Gate_NOT_beh of Gate_NOT is
begin
    process (x)
    begin
        F <= not x; 
    end process;
end Gate_NOT_beh;