library ieee;
use ieee.std_logic_1164.all;
entity Lab2 is
port (A, B : in std_logic_vector (3 downto 0);
Sel: in std_logic;
Sum: out std_logic_vector (3 downto 0);
Cout: out std_logic);
end Lab2;
architecture AddSub_struct of Lab2 is
component Gate_XOR2 is
port (x, y: in std_logic;
f: out std_logic);
end component;
component FullAdder is
port (A, B, Cin: in std_logic;
Sum, Cout: out std_logic);
end component;
signal XOR2_0_out, XOR2_1_out, XOR2_2_out, XOR2_3_out: std_logic;
signal c1, c2, c3: std_logic;
begin
XOR2_0: Gate_XOR2 port map (B(0), Sel, XOR2_0_out);
XOR2_1: Gate_XOR2 port map (B(1), Sel, XOR2_1_out);
XOR2_2: Gate_XOR2 port map (B(2), Sel, XOR2_2_out);
XOR2_3: Gate_XOR2 port map (B(3), Sel, XOR2_3_out);
FullAdder_0: FullAdder port map (A(0), XOR2_0_out, Sel, Sum(0), c1);
FullAdder_1: FullAdder port map (A(1), XOR2_1_out, c1, Sum(1), c2);
FullAdder_2: FullAdder port map (A(2), XOR2_2_out, c2, Sum(2), c3);
FullAdder_3: FullAdder port map (A(3), XOR2_3_out, c3, Sum(3), Cout);
end AddSub_struct;