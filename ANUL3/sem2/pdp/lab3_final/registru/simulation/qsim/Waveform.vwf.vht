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
-- Generated on "03/29/2025 10:09:10"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          registru
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY registru_vhd_vec_tst IS
END registru_vhd_vec_tst;
ARCHITECTURE registru_arch OF registru_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL CLK : STD_LOGIC;
SIGNAL RESET : STD_LOGIC;
SIGNAL SERIAL_IN : STD_LOGIC;
SIGNAL SERIAL_OUT : STD_LOGIC;
SIGNAL SHIFT_EN : STD_LOGIC;
COMPONENT registru
	PORT (
	CLK : IN STD_LOGIC;
	RESET : IN STD_LOGIC;
	SERIAL_IN : IN STD_LOGIC;
	SERIAL_OUT : OUT STD_LOGIC;
	SHIFT_EN : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : registru
	PORT MAP (
-- list connections between master ports and signals
	CLK => CLK,
	RESET => RESET,
	SERIAL_IN => SERIAL_IN,
	SERIAL_OUT => SERIAL_OUT,
	SHIFT_EN => SHIFT_EN
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
	WAIT FOR 620000 ps;
	RESET <= '1';
	WAIT FOR 50000 ps;
	RESET <= '0';
WAIT;
END PROCESS t_prcs_RESET;

-- SHIFT_EN
t_prcs_SHIFT_EN: PROCESS
BEGIN
	SHIFT_EN <= '0';
	WAIT FOR 90000 ps;
	SHIFT_EN <= '1';
	WAIT FOR 890000 ps;
	SHIFT_EN <= '0';
WAIT;
END PROCESS t_prcs_SHIFT_EN;

-- SERIAL_IN
t_prcs_SERIAL_IN: PROCESS
BEGIN
	SERIAL_IN <= '0';
	WAIT FOR 90000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 130000 ps;
	SERIAL_IN <= '0';
	WAIT FOR 80000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 30000 ps;
	SERIAL_IN <= '0';
	WAIT FOR 20000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 30000 ps;
	SERIAL_IN <= '0';
	WAIT FOR 60000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 20000 ps;
	SERIAL_IN <= '0';
	WAIT FOR 30000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 40000 ps;
	SERIAL_IN <= '0';
	WAIT FOR 50000 ps;
	SERIAL_IN <= '1';
	WAIT FOR 110000 ps;
	SERIAL_IN <= '0';
WAIT;
END PROCESS t_prcs_SERIAL_IN;
END registru_arch;
