library IEEE;
use IEEE.std_logic_1164.all;

entity LED_peripheral is
    port (
        -- Gloabals
        clock     : in  std_logic;             -- clock.clk
		  
        -- I/Os
		  led       : out std_logic_vector(5 downto 0);
		  switch		: in std_logic_vector(3 downto 0);
		  key 		: in std_logic_vector(1 downto 0)

	);
end entity LED_peripheral;

architecture rtl of LED_peripheral is

-- signal
signal blink : std_logic := '0';
signal EN    : std_logic := '0';

begin

  process(key)
  --switch ON/OFF
  begin
		if (falling_edge(KEY(0))) then
			EN <= NOT EN;
		end if;		
  end process;

  process(clock, switch) 
      variable counter : integer range 0 to 50000000 := 0;
		variable fq		  : integer range 0 to 50000000 := 10000000;
		
		begin
		
		--frequencias variando de 10kk a 41kk (ainda vou melhorar os valores)
		if (switch = "0000")  then fq := 41000000; end if;
		if (switch = "0001")  then fq := 40000000; end if;
		if (switch = "0010")  then fq := 39000000; end if;
		if (switch = "0011")  then fq := 36000000; end if;
		if (switch = "0100")  then fq := 34000000; end if;
		if (switch = "0101")  then fq := 31000000; end if;
		if (switch = "0110")  then fq := 29000000; end if;
		if (switch = "0111")  then fq := 27000000; end if;
		if (switch = "1000")  then fq := 25000000; end if;
		if (switch = "1001")  then fq := 22000000; end if;
		if (switch = "1010")  then fq := 20000000; end if;
		if (switch = "1011")  then fq := 18000000; end if;
		if (switch = "1100")  then fq := 16000000; end if;
		if (switch = "1101")  then fq := 14000000; end if;
		if (switch = "1110")  then fq := 12000000; end if;
		if (switch = "1111")  then fq := 10000000; end if;
		
		
      --blink led
		if (rising_edge(clock)) then
					if (counter < fq) then
						 counter := counter + 1;
					else
						 blink <= not blink;
						 counter := 0;
					end if;	
		end if;
  end process;

  led(0) <= blink AND EN;
  led(1) <= blink AND EN;
  led(2) <= blink AND EN;
  led(3) <= blink AND EN;
  led(4) <= blink AND EN;
  led(5) <= blink AND EN;
  
  end architecture;