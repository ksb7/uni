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
-- Generated on "03/29/2025 09:55:21"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          Lab2
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY Lab2_vhd_vec_tst IS
END Lab2_vhd_vec_tst;
ARCHITECTURE Lab2_arch OF Lab2_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL f : STD_LOGIC;
SIGNAL x : STD_LOGIC_VECTOR(3 DOWNTO 0);
COMPONENT Lab2
	PORT (
	f : BUFFER STD_LOGIC;
	x : IN STD_LOGIC_VECTOR(3 DOWNTO 0)
	);
END COMPONENT;
BEGIN
	i1 : Lab2
	PORT MAP (
-- list connections between master ports and signals
	f => f,
	x => x
	);
-- x[3]
t_prcs_x_3: PROCESS
BEGIN
	x(3) <= '0';
	WAIT FOR 80000 ps;
	x(3) <= '1';
WAIT;
END PROCESS t_prcs_x_3;
-- x[2]
t_prcs_x_2: PROCESS
BEGIN
	x(2) <= '0';
	WAIT FOR 40000 ps;
	x(2) <= '1';
	WAIT FOR 40000 ps;
	x(2) <= '0';
	WAIT FOR 40000 ps;
	x(2) <= '1';
WAIT;
END PROCESS t_prcs_x_2;
-- x[1]
t_prcs_x_1: PROCESS
BEGIN
	x(1) <= '0';
	WAIT FOR 20000 ps;
	x(1) <= '1';
	WAIT FOR 20000 ps;
	x(1) <= '0';
	WAIT FOR 20000 ps;
	x(1) <= '1';
	WAIT FOR 20000 ps;
	x(1) <= '0';
	WAIT FOR 20000 ps;
	x(1) <= '1';
	WAIT FOR 20000 ps;
	x(1) <= '0';
	WAIT FOR 20000 ps;
	x(1) <= '1';
WAIT;
END PROCESS t_prcs_x_1;
-- x[0]
t_prcs_x_0: PROCESS
BEGIN
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
	WAIT FOR 10000 ps;
	x(0) <= '0';
	WAIT FOR 10000 ps;
	x(0) <= '1';
WAIT;
END PROCESS t_prcs_x_0;
END Lab2_arch;
