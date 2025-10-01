library ieee;
use ieee.std_logic_1164.all;
entity Gate_And3 is
 port (x, y, z: in std_logic;
 F: out std_logic);
end Gate_And3;
architecture Gate_And3_beh of Gate_And3 is
 begin
 process (x, y, z)
 begin
 F <= x and y and z;
 end process;
end Gate_And3_beh;