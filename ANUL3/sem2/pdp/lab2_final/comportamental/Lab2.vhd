library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Lab2 is
    port ( x : in  std_logic_vector (3 downto 0);
           f : out std_logic);
end Lab2;

architecture Lab2_comp of Lab2 is
begin
    process (x)
        variable x_int : integer;
    begin
        x_int := to_integer(unsigned(x));

        f <= '0';

        if (x_int = 6) or 
           (x_int = 7) or 
           (x_int = 11) or 
           (x_int = 12) or 
           (x_int = 14) or 
           (x_int = 15) then
            f <= '1';
        else
            f <= '0';
        end if;
    end process;
end Lab2_comp;
