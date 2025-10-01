-- Copyright (C) 2018  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "03/29/2025 10:11:02"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          numarator
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY numarator_vhd_vec_tst IS
END numarator_vhd_vec_tst;
ARCHITECTURE numarator_arch OF numarator_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL CLK : STD_LOGIC;
SIGNAL D : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL LOAD : STD_LOGIC;
SIGNAL Q : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL RESET : STD_LOGIC;
COMPONENT numarator
	PORT (
	CLK : IN STD_LOGIC;
	D : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
	LOAD : IN STD_LOGIC;
	Q : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
	RESET : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : numarator
	PORT MAP (
-- list connections between master ports and signals
	CLK => CLK,
	D => D,
	LOAD => LOAD,
	Q => Q,
	RESET => RESET
	);

-- CLK
t_prcs_CLK: PROCESS
BEGIN
LOOP
	CLK <= '0';
	WAIT FOR 10000 ps;
	CLK <= '1';
	WAIT FOR 10000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_CLK;

-- RESET
t_prcs_RESET: PROCESS
BEGIN
	RESET <= '0';
	WAIT FOR 320000 ps;
	RESET <= '1';
	WAIT FOR 10000 ps;
	RESET <= '0';
WAIT;
END PROCESS t_prcs_RESET;

-- LOAD
t_prcs_LOAD: PROCESS
BEGIN
	LOAD <= '0';
	WAIT FOR 10000 ps;
	LOAD <= '1';
	WAIT FOR 10000 ps;
	LOAD <= '0';
	WAIT FOR 140000 ps;
	LOAD <= '1';
	WAIT FOR 10000 ps;
	LOAD <= '0';
	WAIT FOR 100000 ps;
	LOAD <= '1';
	WAIT FOR 10000 ps;
	LOAD <= '0';
WAIT;
END PROCESS t_prcs_LOAD;
-- D[3]
t_prcs_D_3: PROCESS
BEGIN
	D(3) <= '1';
	WAIT FOR 50000 ps;
	D(3) <= '0';
WAIT;
END PROCESS t_prcs_D_3;
-- D[2]
t_prcs_D_2: PROCESS
BEGIN
	D(2) <= '0';
	WAIT FOR 50000 ps;
	D(2) <= '1';
	WAIT FOR 230000 ps;
	D(2) <= '0';
WAIT;
END PROCESS t_prcs_D_2;
-- D[1]
t_prcs_D_1: PROCESS
BEGIN
	D(1) <= '0';
	WAIT FOR 230000 ps;
	D(1) <= '1';
	WAIT FOR 50000 ps;
	D(1) <= '0';
WAIT;
END PROCESS t_prcs_D_1;
-- D[0]
t_prcs_D_0: PROCESS
BEGIN
	D(0) <= '0';
	WAIT FOR 50000 ps;
	D(0) <= '1';
	WAIT FOR 230000 ps;
	D(0) <= '0';
WAIT;
END PROCESS t_prcs_D_0;
END numarator_arch;
