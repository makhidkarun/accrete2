
# Classes of stars, from http://crash.ihug.co.nz/~r-smith/worlds/part2.html

# super giant (0.0001 chance)
0.00001	cB
0.00001	cA
0.00002	cF
0.00002	cG
0.00002	cK
0.00002	cM

# giant (0.0099 chance)
0.0004	gF
0.0005	gG
0.0045	gK
0.0045	gM

# main sequence stars (0.92 chance)
0.0001	O	generally high (5-9) subclass
0.0099	B
0.02	A
0.04	F
0.08	G
0.15	K
0.63	M

# white dwarfs (0.07 chance)
0.01	DB
0.02	DA
0.02	DF
0.01	DG
0.0095	DK
0.00045	NS - Neutron star
0.00005	BH - Black hole

what about quasars?

# Stellar density

one star system per 600 cubic light-years of space

# Multiple star systems

His odds:
0.40	1 star
0.40	2 stars
0.09	3 stars
0.01	more stars

Its close, but completely non-scientific.


# Planetary existence odds

Poor. Very poor.

# Stellar mass criteria:

0.08 S is minimum mass required for the star to ignite and burn.
A star of that mass would be an M9 for sure, and would burn for
friggin eternity. That's 26622 earth masses.

The star systems in Carl Sagan's Cosmos include one which has a
planet 31164 Earth masses, and the system is binary (planet ignited)
Is this possible in this version of ACCRETE?

Stars with stellar masses of 0.08 to 6 S will likely become white
dwarfs when they die, but suns over that mass will likely nova.

Jupiter is, like 318 times Earth's mass. The largest planet I have
seen accrete2 create is 2340 Earth masses.

Look at http://seds.lpl.arizona.edu/nineplanets/nineplanets/
for info on distance, radius, and masses of all of the planets and
all of the planets' moons.


# Age on main sequence (Tau)

Based on (mass of star) / (mass of sol) = M_ratio (mass ratio)

time_sol * M_ratio ^ x 

if M_ratio < 0.7, then x = -3.75
   M_ratio >= 0.7, then x = -1.125 - 3.75*M_ratio


# Radius (R)

R_star = R_sol * L_ratio ^ 0.233

where L_ratio = L_star / L_sol


# Luminosity (L)

L_star = L_sol * 10 ^ (0.4 * (Mv_sol - Mv_star))

# Surface temp (T)

T = L / (4 * pi * sigma * R^2)

# Ecosphere range

from 0.53 to 1.02 times the luminosity at Earth's orbit, i.e.

X_earth * sqrt ( L / (1.02*L_sol) ) < X < X_earth * sqrt ( L / (0.53*L_sol) )

# Luminosity vaires thru a star's lifetime as

L_zero_age_main_sequence * e ^ ( 0.045 * (tau/tau_ms)^1.33 )


# Eccentricity and axial tilt

Does accrete2 do this? Oh, yes it does!


# Planets:

maximum mass, in earth masses:

(gamma_E / (G*gamma_rho))^1.5 * Z^3 / r^2

where gamma_E = e^2 / (4*pi*epsilon_0*m_p^1.333)

      gamma_rho = 1.0 - IF

      IF = inertia factor = 2/3 - 4/15 * sqrt( 10*pi^2*r*3/T^2/G/m/epsilon - 1 )

shortest possible period (hours), otherwise planet breaks up

      P = sqrt ( 2*pi / (0.19*G*rho) )   rho = density

plate tectonics ending time (billions of years)

      pte = (m/m_someplace)^0.71

maximum mountain height h_max

      h_max = h_max_someplanet / density

Roche limit (if moon gets any closer, it breaks up)

      R_l_in_km = 0.00244 * r * cube_root( rho_planet / rho_moon )





