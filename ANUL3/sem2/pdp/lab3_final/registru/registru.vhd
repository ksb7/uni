library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity registru is
    port (
        CLK       : in  std_logic;  
        RESET     : in  std_logic;  
        SHIFT_EN  : in  std_logic;
        SERIAL_IN : in  std_logic;
        SERIAL_OUT: out std_logic 
    );
end registru;

architecture Behavioral of registru is
    signal reg_data: std_logic_vector(4 downto 0);
begin
    process (CLK, RESET)
    begin
			if rising_edge(CLK) then  --front crescator al ceasului
				if RESET = '1' then   
					reg_data <= (others => '0');
				elsif SHIFT_EN = '1' then  
					for i in 1 to 4 loop
					reg_data(i-1) <= reg_data(i); -- deplasare la dreapta 
					end loop;
                reg_data(4) <= SERIAL_IN;  -- incarcare seriala
            end if;
        end if;
    end process;

    SERIAL_OUT <= reg_data(0);  --iesire seriala, ultimul bit
end Behavioral;
