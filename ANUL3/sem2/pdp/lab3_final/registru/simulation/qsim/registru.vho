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

-- DATE "03/29/2025 10:09:11"

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


LIBRARY ALTERA;
LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	registru IS
    PORT (
	CLK : IN std_logic;
	RESET : IN std_logic;
	SHIFT_EN : IN std_logic;
	SERIAL_IN : IN std_logic;
	SERIAL_OUT : OUT std_logic
	);
END registru;

-- Design Ports Information
-- SERIAL_OUT	=>  Location: PIN_A15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- RESET	=>  Location: PIN_B9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CLK	=>  Location: PIN_M15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SHIFT_EN	=>  Location: PIN_M1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SERIAL_IN	=>  Location: PIN_T8,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF registru IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_CLK : std_logic;
SIGNAL ww_RESET : std_logic;
SIGNAL ww_SHIFT_EN : std_logic;
SIGNAL ww_SERIAL_IN : std_logic;
SIGNAL ww_SERIAL_OUT : std_logic;
SIGNAL \CLK~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \SERIAL_OUT~output_o\ : std_logic;
SIGNAL \CLK~input_o\ : std_logic;
SIGNAL \CLK~inputclkctrl_outclk\ : std_logic;
SIGNAL \RESET~input_o\ : std_logic;
SIGNAL \SERIAL_IN~input_o\ : std_logic;
SIGNAL \reg_data~5_combout\ : std_logic;
SIGNAL \SHIFT_EN~input_o\ : std_logic;
SIGNAL \reg_data[0]~1_combout\ : std_logic;
SIGNAL \reg_data~4_combout\ : std_logic;
SIGNAL \reg_data~3_combout\ : std_logic;
SIGNAL \reg_data~2_combout\ : std_logic;
SIGNAL \reg_data~0_combout\ : std_logic;
SIGNAL reg_data : std_logic_vector(4 DOWNTO 0);

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_CLK <= CLK;
ww_RESET <= RESET;
ww_SHIFT_EN <= SHIFT_EN;
ww_SERIAL_IN <= SERIAL_IN;
SERIAL_OUT <= ww_SERIAL_OUT;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\CLK~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \CLK~input_o\);
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: IOOBUF_X38_Y34_N16
\SERIAL_OUT~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => reg_data(0),
	devoe => ww_devoe,
	o => \SERIAL_OUT~output_o\);

-- Location: IOIBUF_X53_Y17_N15
\CLK~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CLK,
	o => \CLK~input_o\);

-- Location: CLKCTRL_G9
\CLK~inputclkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLK~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \CLK~inputclkctrl_outclk\);

-- Location: IOIBUF_X25_Y34_N8
\RESET~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_RESET,
	o => \RESET~input_o\);

-- Location: IOIBUF_X27_Y0_N15
\SERIAL_IN~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SERIAL_IN,
	o => \SERIAL_IN~input_o\);

-- Location: LCCOMB_X27_Y16_N10
\reg_data~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data~5_combout\ = (!\RESET~input_o\ & \SERIAL_IN~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \RESET~input_o\,
	datad => \SERIAL_IN~input_o\,
	combout => \reg_data~5_combout\);

-- Location: IOIBUF_X0_Y16_N22
\SHIFT_EN~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SHIFT_EN,
	o => \SHIFT_EN~input_o\);

-- Location: LCCOMB_X27_Y16_N16
\reg_data[0]~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data[0]~1_combout\ = (\RESET~input_o\) # (\SHIFT_EN~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \RESET~input_o\,
	datac => \SHIFT_EN~input_o\,
	combout => \reg_data[0]~1_combout\);

-- Location: FF_X27_Y16_N11
\reg_data[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \reg_data~5_combout\,
	ena => \reg_data[0]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg_data(4));

-- Location: LCCOMB_X27_Y16_N28
\reg_data~4\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data~4_combout\ = (!\RESET~input_o\ & reg_data(4))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \RESET~input_o\,
	datad => reg_data(4),
	combout => \reg_data~4_combout\);

-- Location: FF_X27_Y16_N29
\reg_data[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \reg_data~4_combout\,
	ena => \reg_data[0]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg_data(3));

-- Location: LCCOMB_X27_Y16_N6
\reg_data~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data~3_combout\ = (!\RESET~input_o\ & reg_data(3))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \RESET~input_o\,
	datad => reg_data(3),
	combout => \reg_data~3_combout\);

-- Location: FF_X27_Y16_N7
\reg_data[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \reg_data~3_combout\,
	ena => \reg_data[0]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg_data(2));

-- Location: LCCOMB_X27_Y16_N18
\reg_data~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data~2_combout\ = (!\RESET~input_o\ & reg_data(2))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \RESET~input_o\,
	datad => reg_data(2),
	combout => \reg_data~2_combout\);

-- Location: FF_X27_Y16_N19
\reg_data[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \reg_data~2_combout\,
	ena => \reg_data[0]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg_data(1));

-- Location: LCCOMB_X27_Y16_N12
\reg_data~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \reg_data~0_combout\ = (!\RESET~input_o\ & reg_data(1))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \RESET~input_o\,
	datad => reg_data(1),
	combout => \reg_data~0_combout\);

-- Location: FF_X27_Y16_N13
\reg_data[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \reg_data~0_combout\,
	ena => \reg_data[0]~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => reg_data(0));

ww_SERIAL_OUT <= \SERIAL_OUT~output_o\;
END structure;


