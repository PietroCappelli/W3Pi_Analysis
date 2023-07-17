-- null_algo
--
-- Do-nothing top level algo for testing
--
-- Dave Newbold, July 2013
-- Adding slink outputs and ipbus config : Kristian Hahn, 2022

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_MISC.ALL; -- or_reduce

use ieee.numeric_std.all;
use work.ipbus.all;
use work.emp_data_types.all;
use work.emp_project_decl.all;

use work.emp_device_decl.all;
use work.emp_ttc_decl.all;

use work.emp_slink_types.all;

entity emp_payload is
  port(
    clk         : in  std_logic;        -- ipbus signals
    rst         : in  std_logic;
    ipb_in      : in  ipb_wbus;
    ipb_out     : out ipb_rbus;
    clk40       : in  std_logic;	
    clk_payload : in  std_logic_vector(2 downto 0);
    rst_payload : in  std_logic_vector(2 downto 0);
    clk_p       : in  std_logic;        -- data clock
    rst_loc     : in  std_logic_vector(N_REGION - 1 downto 0);
    clken_loc   : in  std_logic_vector(N_REGION - 1 downto 0);
    ctrs        : in  ttc_stuff_array;
    bc0         : out std_logic;
    d           : in  ldata(4 * N_REGION - 1 downto 0);  -- data in
    q           : out ldata(4 * N_REGION - 1 downto 0);  -- data out
    gpio        : out std_logic_vector(29 downto 0);  -- IO to mezzanine connector
    gpio_en     : out std_logic_vector(29 downto 0);  -- IO to mezzanine connector (three-state enables)
    slink_q : out slink_input_data_quad_array(SLINK_MAX_QUADS-1 downto 0);
    backpressure : in std_logic_vector(SLINK_MAX_QUADS-1 downto 0)
    );

end emp_payload;


architecture rtl of emp_payload is

  constant NLINKS : natural := 2;
  constant QUAD0 : natural := 10;
  constant QUAD1 : natural := 15;
  type dr_t is array(PAYLOAD_LATENCY downto 0) of ldata(NLINKS - 1 downto 0);
  type dr4_t is array(PAYLOAD_LATENCY downto 0) of ldata(4*NLINKS - 1 downto 0);
  signal din : dr_t;
  signal dout : dr4_t;
  signal gen4 : ldata(4*NLINKS-1 downto 0);
  --signal orbit, orbit_d : unsigned(31 downto 0) := (others => '0');
  --signal orbit_bit, orbit_bit_d: std_logic := '0';
  --signal bctr_d : bctr_t;
begin

  ipb_out <= IPB_RBUS_NULL;

  fill_dr: process (clk_p)
  begin
    if rising_edge(clk_p) then
      din(0)(0) <= d(4*QUAD0);
      din(0)(1) <= d(4*QUAD1);
      din(PAYLOAD_LATENCY downto 1) <= din(PAYLOAD_LATENCY - 1 downto 0);
    end if;
  end process;

--  orbit_counter: process(clk_p)
--  begin
--    if rising_edge(clk_p) then
--        bctr_d <= ctrs(QUAD0).bctr;
--        if (or(ctrs(QUAD0).bctr) = '0') and (or(bctr_d) /= '0') then 
--           orbit <= orbit + to_unsigned(1, orbit'length);
--            orbit_bit <= '1';
--        end if;
--        orbit_d <= orbit;
--        orbit_bit_d <= orbit_bit;
--    end if;
--  end process orbit_counter;

--  gen_gen: for i in 0 to NLINKS-1 generate
    generator : entity work.gen4
    port map (
        CLOCK_RATIO_MINUS_ONE => std_logic_vector(to_unsigned(CLOCK_RATIO-1, 4)),
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;
        ap_done => open,
        --valid => din(PAYLOAD_LATENCY)(i).valid, -- : IN STD_LOGIC;
        --data => din(PAYLOAD_LATENCY)(i).data, -- : IN STD_LOGICECTOR (63 downto 0);
        
	p_idxs_0 => d(4*QUAD0).data,
	p_idxs_1 => d(4*QUAD0 +1).data,
	p_idxs_2 => d(4*QUAD0 +2).data,
	p_idxs_3 => d(4*QUAD0 +3).data,

	valid => d(4*QUAD0).valid,
	set =>   d(4*QUAD0).start,

	data_out_0  => q(4*QUAD0).data,
	valid_out_0 => q(4*QUAD0).valid,
	orbit_out_0 => q(4*QUAD0).start_of_orbit,
	start_out_0 => q(4*QUAD0).start,
	end_out_0   => q(4*QUAD0).last,

	data_out_1  => q(4*QUAD0 +1).data,
	valid_out_1 => q(4*QUAD0 +1).valid,
	orbit_out_1 => q(4*QUAD0 +1).start_of_orbit,
	start_out_1 => q(4*QUAD0 +1).start,
	end_out_1   => q(4*QUAD0 +1).last,

	data_out_2  => q(4*QUAD0 +2).data,
	valid_out_2 => q(4*QUAD0 +2).valid,
	orbit_out_2 => q(4*QUAD0 +2).start_of_orbit,
	start_out_2 => q(4*QUAD0 +2).start,
	end_out_2   => q(4*QUAD0 +2).last,

	data_out_3  => q(4*QUAD0 +3).data,
	valid_out_3 => q(4*QUAD0 +3).valid,
	orbit_out_3 => q(4*QUAD0 +3).start_of_orbit,
	start_out_3 => q(4*QUAD0 +3).start,
	end_out_3   => q(4*QUAD0 +3).last
    );

--  end generate gen_gen;


end rtl;
