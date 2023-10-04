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
    type rng_vector is array(3 downto 0) of std_logic_vector(63 downto 0); -- array to connect xoshiro with gen4
    signal seeds, rng : rng_vector;    
    -- type setseed_bool_vec is array(3 downto 0) of std_logic;
    -- signal has_set_seed, setseeds : setseed_bool_vec:= (others => '0');
    signal has_set_seed : std_logic_vector(3 downto 0) := (others => '0');
    signal setseeds : std_logic_vector(3 downto 0) := (others => '0');

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

--   setseeds: process(clk_p)
--   begin
--        if rising_edge(clk_p) then
--            for i in 0 to 3 loop
--                 if d(...+i).start_of_orbit = '1' and has_set_seed(i) = '0' then
--                          seed(i) <= ...
--                          setseed(i) <= '1'
--                          has_set_seed(i) <= '1'
--                 else
--                          setseed(i) <= '0'
--                 end if;
--         end loop;
--   end if;
--   end process;

    setting_seeds: process(clk_p)
    begin 
        if rising_edge(clk_p) then
            for i in 0 to 3 loop
                if d(4*QUAD0 +i).start_of_orbit = '1' and has_set_seed(i) = '0' then
                    seeds(i) <= d(4*QUAD0 +i).data;
                    setseeds(i) <= '1';
                    has_set_seed(i) <= '1';
                else
                    setseeds(i) <= '0';
                end if;
            end loop;
        end if;
    end process;

    block1: entity work.xoshiro256hw
    port map(
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;

        setseed => setseeds(0),
        seed    => seeds(0),
        ap_return => rng(0)
    );

    block2: entity work.xoshiro256hw
    port map(
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;

        setseed => setseeds(1),
        seed    => seeds(1),
	ap_return => rng(1)
    );

    block3: entity work.xoshiro256hw
    port map(
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;

        setseed => setseeds(2),
        seed    => seeds(2),
    	ap_return => rng(2)
    );

    block4: entity work.xoshiro256hw
    port map(
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;

        setseed => setseeds(3),
        seed    => seeds(3),
    	ap_return => rng(3)
    );

    generator : entity work.gen4
    port map (
        CLOCK_RATIO_MINUS_ONE => std_logic_vector(to_unsigned(CLOCK_RATIO-1, 4)),
        ap_clk => clk_p, --: IN STD_LOGIC;
        ap_rst => '0', --: IN STD_LOGIC;
        ap_start => '1', --: IN STD_LOGIC;
        ap_done => open,
        
        p_idxs_0 => rng(0),
        p_idxs_1 => rng(1),
        p_idxs_2 => rng(2),
        p_idxs_3 => rng(3),

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
