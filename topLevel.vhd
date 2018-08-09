library IEEE;
use IEEE.std_logic_1164.all;

entity topLevel is
    port (
        -- Gloabals
        fpga_clk_50        : in  std_logic;             -- clock.clk
		  
        -- I/Os
        fpga_led_pio       : out std_logic_vector(5 downto 0);
		  fpga_sw_pio        : in std_logic_vector(3 downto 0);
		  fpga_key_pio			: in std_logic_vector(1 downto 0)

	);
end entity topLevel;

architecture rtl of topLevel is


component LED_peripheral is
    port (
        -- Gloabals
        clock     : in  std_logic;             -- clock.clk
		  
        -- I/Os
		  led       : out std_logic_vector(5 downto 0);
		  switch		: in std_logic_vector(3 downto 0);
		  key 		: in std_logic_vector(1 downto 0)

	);
end component;

begin
	
 u1: LED_peripheral port map(
	clock => fpga_clk_50,
	led   => fpga_led_pio,
	switch => fpga_sw_pio,
	key   => fpga_key_pio
 );

  
end architecture;