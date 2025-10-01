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
-- Generated on "03/29/2025 10:01:40"
                                                             
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
SIGNAL F : STD_LOGIC;
SIGNAL x0 : STD_LOGIC;
SIGNAL x1 : STD_LOGIC;
SIGNAL x2 : STD_LOGIC;
SIGNAL x3 : STD_LOGIC;
COMPONENT Lab2
	PORT (
	F : BUFFER STD_LOGIC;
	x0 : IN STD_LOGIC;
	x1 : IN STD_LOGIC;
	x2 : IN STD_LOGIC;
	x3 : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : Lab2
	PORT MAP (
-- list connections between master ports and signals
	F => F,
	x0 => x0,
	x1 => x1,
	x2 => x2,
	x3 => x3
	);

-- x0
t_prcs_x0: PROCESS
BEGIN
	x0 <= '0';
	WAIT FOR 80000 ps;
	x0 <= '1';
WAIT;
END PROCESS t_prcs_x0;

-- x1
t_prcs_x1: PROCESS
BEGIN
	x1 <= '0';
	WAIT FOR 40000 ps;
	x1 <= '1';
	WAIT FOR 40000 ps;
	x1 <= '0';
	WAIT FOR 40000 ps;
	x1 <= '1';
WAIT;
END PROCESS t_prcs_x1;

-- x2
t_prcs_x2: PROCESS
BEGIN
	x2 <= '0';
	WAIT FOR 20000 ps;
	x2 <= '1';
	WAIT FOR 20000 ps;
	x2 <= '0';
	WAIT FOR 20000 ps;
	x2 <= '1';
	WAIT FOR 20000 ps;
	x2 <= '0';
	WAIT FOR 20000 ps;
	x2 <= '1';
	WAIT FOR 20000 ps;
	x2 <= '0';
	WAIT FOR 20000 ps;
	x2 <= '1';
WAIT;
END PROCESS t_prcs_x2;

-- x3
t_prcs_x3: PROCESS
BEGIN
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
	WAIT FOR 10000 ps;
	x3 <= '0';
	WAIT FOR 10000 ps;
	x3 <= '1';
WAIT;
END PROCESS t_prcs_x3;
END Lab2_arch;
