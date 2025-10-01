library ieee;
use ieee.std_logic_1164.all;

entity Lab2 is
    port (
        x0, x1, x2, x3: in std_logic;
        F: out std_logic
    );
end Lab2;

architecture Lab2_struct of Lab2 is

    component Gate_And2 is
        port (x, y: in std_logic; F: out std_logic);
    end component;

    component Gate_And3 is
        port (x, y, z: in std_logic; F: out std_logic);
    end component;

    component Gate_OR3 is
        port (x, y, z: in std_logic; F: out std_logic);
    end component;

    component Gate_NOT is
        port (x: in std_logic; F: out std_logic);
    end component;

    signal  NOT_1_out, NOT_2_out: std_logic;
    signal AND2_0_out, AND3_0_out, AND3_1_out: std_logic;

begin

    NOT_1: Gate_NOT port map (x => x3, F => NOT_1_out);

    AND2_0: Gate_And2 port map (x => x1, y => x2, F => AND2_0_out);

    AND3_0: Gate_And3 port map (x => x0, y => x2, z => x3, F => AND3_0_out);
    AND3_1: Gate_And3 port map (x => x0, y => x1, z => NOT_1_out, F => AND3_1_out);

    OR3_0: Gate_OR3 port map (x => AND2_0_out, y => AND3_0_out, z => AND3_1_out, F => F);

end Lab2_struct;