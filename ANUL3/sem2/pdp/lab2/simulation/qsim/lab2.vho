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

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 18.1.0 Build 625 09/12/2018 SJ Lite Edition"

-- DATE "01/21/2025 22:15:27"

-- 
-- Device: Altera EP4CE22F17C6 Package FBGA256
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	hard_block IS
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic
	);
END hard_block;

-- Design Ports Information
-- ~ALTERA_ASDO_DATA1~	=>  Location: PIN_C1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_FLASH_nCE_nCSO~	=>  Location: PIN_D2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_DCLK~	=>  Location: PIN_H1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_DATA0~	=>  Location: PIN_H2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_nCEO~	=>  Location: PIN_F16,	 I/O Standard: 2.5 V,	 Current Strength: 8mA


ARCHITECTURE structure OF hard_block IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \~ALTERA_ASDO_DATA1~~padout\ : std_logic;
SIGNAL \~ALTERA_FLASH_nCE_nCSO~~padout\ : std_logic;
SIGNAL \~ALTERA_DATA0~~padout\ : std_logic;
SIGNAL \~ALTERA_ASDO_DATA1~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_FLASH_nCE_nCSO~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_DATA0~~ibuf_o\ : std_logic;

BEGIN

ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
END structure;


LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Lab2 IS
    PORT (
	A : IN std_logic_vector(3 DOWNTO 0);
	B : IN std_logic_vector(3 DOWNTO 0);
	Sel : IN std_logic;
	Sum : OUT std_logic_vector(3 DOWNTO 0);
	Cout : OUT std_logic
	);
END Lab2;

-- Design Ports Information
-- Sum[0]	=>  Location: PIN_G5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Sum[1]	=>  Location: PIN_F3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Sum[2]	=>  Location: PIN_F8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Sum[3]	=>  Location: PIN_B11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Cout	=>  Location: PIN_K1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A[0]	=>  Location: PIN_F2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B[0]	=>  Location: PIN_G1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A[1]	=>  Location: PIN_D1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B[1]	=>  Location: PIN_G2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Sel	=>  Location: PIN_F15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A[2]	=>  Location: PIN_J2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B[2]	=>  Location: PIN_K5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A[3]	=>  Location: PIN_F1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B[3]	=>  Location: PIN_E1,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Lab2 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_A : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_B : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_Sel : std_logic;
SIGNAL ww_Sum : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_Cout : std_logic;
SIGNAL \Sum[0]~output_o\ : std_logic;
SIGNAL \Sum[1]~output_o\ : std_logic;
SIGNAL \Sum[2]~output_o\ : std_logic;
SIGNAL \Sum[3]~output_o\ : std_logic;
SIGNAL \Cout~output_o\ : std_logic;
SIGNAL \B[0]~input_o\ : std_logic;
SIGNAL \A[0]~input_o\ : std_logic;
SIGNAL \FullAdder_0|XOR2_1|F~0_combout\ : std_logic;
SIGNAL \Sel~input_o\ : std_logic;
SIGNAL \FullAdder_0|AND2_2|F~combout\ : std_logic;
SIGNAL \A[1]~input_o\ : std_logic;
SIGNAL \B[1]~input_o\ : std_logic;
SIGNAL \XOR2_1|F~combout\ : std_logic;
SIGNAL \FullAdder_0|OR3_1|F~0_combout\ : std_logic;
SIGNAL \FullAdder_1|XOR2_1|F~combout\ : std_logic;
SIGNAL \FullAdder_1|OR3_1|F~0_combout\ : std_logic;
SIGNAL \B[2]~input_o\ : std_logic;
SIGNAL \A[2]~input_o\ : std_logic;
SIGNAL \FullAdder_2|XOR2_1|F~0_combout\ : std_logic;
SIGNAL \B[3]~input_o\ : std_logic;
SIGNAL \A[3]~input_o\ : std_logic;
SIGNAL \FullAdder_2|OR3_1|F~0_combout\ : std_logic;
SIGNAL \FullAdder_3|XOR2_1|F~0_combout\ : std_logic;
SIGNAL \FullAdder_3|OR3_1|F~0_combout\ : std_logic;

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_A <= A;
ww_B <= B;
ww_Sel <= Sel;
Sum <= ww_Sum;
Cout <= ww_Cout;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: IOOBUF_X0_Y24_N16
\Sum[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \FullAdder_0|XOR2_1|F~0_combout\,
	devoe => ww_devoe,
	o => \Sum[0]~output_o\);

-- Location: IOOBUF_X0_Y26_N16
\Sum[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \FullAdder_1|XOR2_1|F~combout\,
	devoe => ww_devoe,
	o => \Sum[1]~output_o\);

-- Location: IOOBUF_X20_Y34_N16
\Sum[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \FullAdder_2|XOR2_1|F~0_combout\,
	devoe => ww_devoe,
	o => \Sum[2]~output_o\);

-- Location: IOOBUF_X40_Y34_N9
\Sum[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \FullAdder_3|XOR2_1|F~0_combout\,
	devoe => ww_devoe,
	o => \Sum[3]~output_o\);

-- Location: IOOBUF_X0_Y12_N9
\Cout~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \FullAdder_3|OR3_1|F~0_combout\,
	devoe => ww_devoe,
	o => \Cout~output_o\);

-- Location: IOIBUF_X0_Y23_N22
\B[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B(0),
	o => \B[0]~input_o\);

-- Location: IOIBUF_X0_Y24_N22
\A[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A(0),
	o => \A[0]~input_o\);

-- Location: LCCOMB_X4_Y23_N0
\FullAdder_0|XOR2_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_0|XOR2_1|F~0_combout\ = \B[0]~input_o\ $ (\A[0]~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B[0]~input_o\,
	datac => \A[0]~input_o\,
	combout => \FullAdder_0|XOR2_1|F~0_combout\);

-- Location: IOIBUF_X53_Y22_N8
\Sel~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_Sel,
	o => \Sel~input_o\);

-- Location: LCCOMB_X4_Y23_N12
\FullAdder_0|AND2_2|F\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_0|AND2_2|F~combout\ = (!\B[0]~input_o\ & \Sel~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \B[0]~input_o\,
	datad => \Sel~input_o\,
	combout => \FullAdder_0|AND2_2|F~combout\);

-- Location: IOIBUF_X0_Y25_N8
\A[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A(1),
	o => \A[1]~input_o\);

-- Location: IOIBUF_X0_Y23_N15
\B[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B(1),
	o => \B[1]~input_o\);

-- Location: LCCOMB_X4_Y23_N26
\XOR2_1|F\ : cycloneive_lcell_comb
-- Equation(s):
-- \XOR2_1|F~combout\ = \B[1]~input_o\ $ (\Sel~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \B[1]~input_o\,
	datad => \Sel~input_o\,
	combout => \XOR2_1|F~combout\);

-- Location: LCCOMB_X4_Y23_N6
\FullAdder_0|OR3_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_0|OR3_1|F~0_combout\ = (\A[0]~input_o\ & ((\B[0]~input_o\) # (\Sel~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B[0]~input_o\,
	datac => \A[0]~input_o\,
	datad => \Sel~input_o\,
	combout => \FullAdder_0|OR3_1|F~0_combout\);

-- Location: LCCOMB_X4_Y23_N16
\FullAdder_1|XOR2_1|F\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_1|XOR2_1|F~combout\ = \A[1]~input_o\ $ (\XOR2_1|F~combout\ $ (((\FullAdder_0|AND2_2|F~combout\) # (\FullAdder_0|OR3_1|F~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001110010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \FullAdder_0|AND2_2|F~combout\,
	datab => \A[1]~input_o\,
	datac => \XOR2_1|F~combout\,
	datad => \FullAdder_0|OR3_1|F~0_combout\,
	combout => \FullAdder_1|XOR2_1|F~combout\);

-- Location: LCCOMB_X4_Y23_N10
\FullAdder_1|OR3_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_1|OR3_1|F~0_combout\ = (\A[1]~input_o\ & ((\FullAdder_0|AND2_2|F~combout\) # ((\XOR2_1|F~combout\) # (\FullAdder_0|OR3_1|F~0_combout\)))) # (!\A[1]~input_o\ & (\XOR2_1|F~combout\ & ((\FullAdder_0|AND2_2|F~combout\) # 
-- (\FullAdder_0|OR3_1|F~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \FullAdder_0|AND2_2|F~combout\,
	datab => \A[1]~input_o\,
	datac => \XOR2_1|F~combout\,
	datad => \FullAdder_0|OR3_1|F~0_combout\,
	combout => \FullAdder_1|OR3_1|F~0_combout\);

-- Location: IOIBUF_X0_Y7_N8
\B[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B(2),
	o => \B[2]~input_o\);

-- Location: IOIBUF_X0_Y15_N1
\A[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A(2),
	o => \A[2]~input_o\);

-- Location: LCCOMB_X4_Y23_N4
\FullAdder_2|XOR2_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_2|XOR2_1|F~0_combout\ = \FullAdder_1|OR3_1|F~0_combout\ $ (\B[2]~input_o\ $ (\A[2]~input_o\ $ (\Sel~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100110010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \FullAdder_1|OR3_1|F~0_combout\,
	datab => \B[2]~input_o\,
	datac => \A[2]~input_o\,
	datad => \Sel~input_o\,
	combout => \FullAdder_2|XOR2_1|F~0_combout\);

-- Location: IOIBUF_X0_Y16_N8
\B[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B(3),
	o => \B[3]~input_o\);

-- Location: IOIBUF_X0_Y23_N1
\A[3]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A(3),
	o => \A[3]~input_o\);

-- Location: LCCOMB_X4_Y23_N22
\FullAdder_2|OR3_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_2|OR3_1|F~0_combout\ = (\FullAdder_1|OR3_1|F~0_combout\ & ((\A[2]~input_o\) # (\B[2]~input_o\ $ (\Sel~input_o\)))) # (!\FullAdder_1|OR3_1|F~0_combout\ & (\A[2]~input_o\ & (\B[2]~input_o\ $ (\Sel~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011001011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \FullAdder_1|OR3_1|F~0_combout\,
	datab => \B[2]~input_o\,
	datac => \A[2]~input_o\,
	datad => \Sel~input_o\,
	combout => \FullAdder_2|OR3_1|F~0_combout\);

-- Location: LCCOMB_X4_Y23_N24
\FullAdder_3|XOR2_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_3|XOR2_1|F~0_combout\ = \B[3]~input_o\ $ (\A[3]~input_o\ $ (\FullAdder_2|OR3_1|F~0_combout\ $ (\Sel~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100110010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B[3]~input_o\,
	datab => \A[3]~input_o\,
	datac => \FullAdder_2|OR3_1|F~0_combout\,
	datad => \Sel~input_o\,
	combout => \FullAdder_3|XOR2_1|F~0_combout\);

-- Location: LCCOMB_X4_Y23_N2
\FullAdder_3|OR3_1|F~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \FullAdder_3|OR3_1|F~0_combout\ = (\A[3]~input_o\ & ((\FullAdder_2|OR3_1|F~0_combout\) # (\B[3]~input_o\ $ (\Sel~input_o\)))) # (!\A[3]~input_o\ & (\FullAdder_2|OR3_1|F~0_combout\ & (\B[3]~input_o\ $ (\Sel~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101010011101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B[3]~input_o\,
	datab => \A[3]~input_o\,
	datac => \FullAdder_2|OR3_1|F~0_combout\,
	datad => \Sel~input_o\,
	combout => \FullAdder_3|OR3_1|F~0_combout\);

ww_Sum(0) <= \Sum[0]~output_o\;

ww_Sum(1) <= \Sum[1]~output_o\;

ww_Sum(2) <= \Sum[2]~output_o\;

ww_Sum(3) <= \Sum[3]~output_o\;

ww_Cout <= \Cout~output_o\;
END structure;


