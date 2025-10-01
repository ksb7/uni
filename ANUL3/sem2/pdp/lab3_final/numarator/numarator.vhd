library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity numarator is
    port (
        CLK        : in  std_logic;
        RESET      : in  std_logic;
        LOAD       : in  std_logic;
        D          : in  std_logic_vector(3 downto 0);
        Q          : out std_logic_vector(3 downto 0)
    );
end numarator;

architecture Behavioral of numarator is
    signal counter : std_logic_vector(3 downto 0) := "0011"; -- asignam 3 in binar
begin
    process(CLK, RESET)
    begin
	     if falling_edge(CLK) then --resetare sincrona cu falling edge
				if RESET = '1' then
					counter <= "0011"; --reseteaza la 3
				elsif LOAD = '1' then
						 counter <= D;  -- incarca paralel
					else
						 if counter = "1100" then
							  counter <= "0011";
						 else
							  counter <= counter + 1;
						 end if;
					end if;
        end if;
    end process;

    Q <= counter;
end Behavioral;
