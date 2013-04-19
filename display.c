#include	<stdio.h>
#include	<string.h>
#include        <math.h>

#ifdef MSDOS
#include        <stddef.h>
#include        <malloc.h>
#include	<stdlib.h>
#include        <float.h>
#endif

#include	"structs.h"
#include	"const.h"

#define	MAX_EXP_DIGS	3
#define	MAX_MAN_DIGS	20

extern double stellar_mass_ratio, stellar_luminosity_ratio, main_seq_life,
	age, ecosphere_radius;
extern int flag_graphics, flag_lisp;

char OP[] = "(";
char CP[] = ")";


char *engineer_notation(d, p)
double d;
int p;
{
	static char mansign;
	static char expsign;
	static char output[1+MAX_MAN_DIGS+1+1+MAX_EXP_DIGS+1];
	double mantissa;
	int exponent;

	mansign = '+';
	expsign = '+';
	if (p > MAX_MAN_DIGS)
		p = MAX_MAN_DIGS;
	if (p < 3)
		p = 3;
	--p;
	if (d < 0.0)
	{
		mansign = '-';
		d = -d;
	}
	if (d == 0.0)
	{
		exponent = 0;
		mantissa = 0;
	}
	else
	{
		exponent = log10(d);
		if (exponent == 0 && d < 1.0)	/* log10 sometimes lies */
		{
			--exponent;
			--p;
		}
		if (exponent < 0)
		{
			expsign = '-';
			--exponent;
		}
		mantissa = d / pow(10.0, (double) exponent);
		if (exponent < 0)
			exponent = -exponent;
		while ((exponent % 3) != 0)
		{
			mantissa *= 10.0;
			p--;
			if (expsign == '-')
				++exponent;
			else
				--exponent;
		}
	}
	sprintf(output, "%c%*.*lfe%c%*.*d", mansign, p, p, mantissa,
		expsign, MAX_EXP_DIGS, MAX_EXP_DIGS, exponent);
	return (output);
}

/* This function has not yet been implemented */
void chart_system(innermost_planet)
planet_pointer innermost_planet;
{
}

/*
 * This function writes a textual description of the solar system
 */
void text_describe_system(innermost_planet)
planet_pointer innermost_planet;
{
     planet_pointer node1;	/* node1 is the planet_pointer for planets */
     int counter; 
#ifdef MOON
     planet_pointer node2;	/* node1 is the planet_pointer for moons */
     int mcounter; 
#endif
     
     printf("                         SYSTEM  CHARACTERISTICS\n");
     printf("Mass of central star: %4.2lf solar masses\n", stellar_mass_ratio);
     printf("Luminosity of central star: %4.2lf\n",stellar_luminosity_ratio);
     printf("Current age of stellar system: %5.3lf billion years\n", (age /1.0E9));
     printf("   (%5.3lf billion left on main sequence)\n",(main_seq_life - age) / 1.0E9);
     printf("Radius of habitable ecosphere: %3.3lf AU\n",ecosphere_radius);
     printf("\n");
     printf("Planets present at:\n");
     for (node1=innermost_planet, counter=1; node1 != NULL; node1=node1->next_planet, counter++)
     {
          printf("%d\t%7.3lf \t AU\n", counter, node1->a);
     }
     printf("\n\n");
     for (node1=innermost_planet, counter=1; node1 != NULL; node1=node1->next_planet, counter++)
     {
          printf("Planet %d\t",counter);
          if (node1->gas_giant)
               printf("*gas giant*\n");
          else printf("\n");
          if ((int)node1->day == (int)(node1->orbital_period * 24.0))
               printf("   Planet is tidally locked with one face to primary star\n");
          if (node1->resonant_period)
               printf("   Planet's rotation is in a resonant spin lock with primary star\n");
          printf("   Distance from primary star:\t%5.3lf\tAU\n",node1->a);
          printf("   Mass:\t\t\t%5.3lf\tEarth masses\n",node1->mass * SUN_MASS_IN_EARTH_MASSES);
          if (!(node1->gas_giant))
          {
               printf("   Surface gravity:\t\t%4.2lf\tEarth gees\n",node1->surface_grav);
               printf("   Surface pressure:\t\t%5.3lf\tEarth atmospheres",(node1->surface_pressure / 1000.0));
               if ((node1->greenhouse_effect) && (node1->surface_pressure > 0.0))
                    printf("\tRUNAWAY GREENHOUSE EFFECT\n");
               else 
                    printf("\n");
               printf("   Surface temperature:\t\t%4.2lf\tdegrees Celcius\n",(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE));
               printf("   Boiling point of water:\t%3.1lf\tdegrees Celcius\n",(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE));
          }
          printf("   Equatorial radius:\t\t%3.1lf\tkm\n",node1->radius);
          printf("   Density:\t\t\t%5.3lf\tgrams/cc\n",node1->density);
          printf("   Eccentricity of orbit:\t%5.3lf\n",node1->e);
          printf("   Escape velocity:\t\t%4.2lf\tkm/sec\n",node1->escape_velocity / CM_PER_KM);
          printf("   Smallest molecular weight\n");
          printf("      retained in atmosphere:\t%4.2lf and above\n",node1->molecule_weight);
          printf("   Surface accel. of gravity:\t%4.2lf\tm/sec2\n",node1->surface_accel / 100.0);
          printf("   Axial tilt:\t\t\t%d\tdegrees\n",node1->axial_tilt);
          printf("   Planetary albedo:\t\t%5.3lf\n",node1->albedo);
          printf("   Length of year:\t\t%4.2lf\tdays\n",node1->orbital_period);
          printf("   Length of day:\t\t%4.2lf\thours\n",node1->day);
          if (!(node1->gas_giant))
          {
               printf("   Hydrosphere percentage:\t%4.2lf\n",(node1->hydrosphere * 100.0));
               printf("   Cloud cover percentage:\t%4.2lf\n",(node1->cloud_cover * 100));
               printf("   Ice cover percentage:\t%4.2lf\n",(node1->ice_cover * 100));
          }
          printf("\n");
#ifdef MOON
          printf("   Moons present at:\n");
          for (node2=first_moon, mcounter=1; node2 != NULL; node2=node2->next_planet, mcounter++)
          {
               printf("   %d\t%7.3lf \t AU\n", counter, node1->a);
          }
          printf("\n\n");
          for (node2=first_moon, mcounter=1; node2 != NULL; node2=node2->next_planet, mcounter++)
          {
               printf("   Moon %d\t",mcounter);
               printf("\n");
          }
          printf("\n\n");
#endif
     }
}

void lisp_describe_system(innermost_planet)
planet_pointer innermost_planet;
{
	planet_pointer node1; 
	int counter; 
     
	printf("%splanetary-system\n", OP);
	printf(" %ssun\n", OP);
	printf("  %smass %s%s ; kg\n",
		OP,
		engineer_notation(stellar_mass_ratio * SOLAR_MASS_IN_GRAMS / 1000.0, 6),
		CP);
	printf("  %sluminosity %s%s ; * SOL luminosity\n",
		OP, engineer_notation(stellar_luminosity_ratio, 6), CP);
	printf("  %slifetime %s%s ; years\n",
		OP, engineer_notation(main_seq_life, 6), CP);
	printf("  %scurrent-age %s%s ; years\n",
		OP, engineer_notation(age, 6), CP);
	printf("  %secosphere-radius %s%s ; km\n",
		OP, engineer_notation(ecosphere_radius * KM_PER_AU, 6), CP);
	printf(" %s\n", CP);
	for (node1=innermost_planet, counter=1;
	     node1 != NULL;
	     node1=node1->next_planet, counter++)
	{
		printf(" %splanet ; #%d\n",
			OP, counter);
		printf("  ; boolean:\n");
		printf("  %sis-gas-giant %d%s\n", OP, node1->gas_giant, CP);
		printf("  ; orbital statistics:\n");
		printf("  %smean-orbit-radius %s%s ; km\n",
			OP, engineer_notation(node1->a * KM_PER_AU, 6), CP);
		printf("  %sorbit-eccentricity %s%s\n",
			OP, engineer_notation(node1->e, 6), CP);
		printf("  %saxial-tilt %d%s ; degrees\n",
			OP, node1->axial_tilt, CP);
		printf("  %sorbital-period %s%s ; Earth days\n",
			OP, engineer_notation(node1->orbital_period, 6), CP);
		printf("  %srotation-period %s%s ; Earth hours\n",
			OP, engineer_notation(node1->day, 6), CP);
		printf("  %sis-resonant %d%s\n", OP, node1->resonant_period, CP);
		printf("  ; planetary measurements:\n");
		printf("  %smass %s%s ; kg\n",
			OP, engineer_notation(node1->mass * SOLAR_MASS_IN_GRAMS / 1000.0, 6), CP);
		printf("  %sequatorial-radius %s%s ; km\n",
			OP, engineer_notation(node1->radius, 6), CP);
		printf("  %sdensity %s%s ; g/cm3\n",
			OP, engineer_notation(node1->density, 6), CP);
		printf("  ; planetary environment:\n");
		printf("  %sescape-velocity %s%s ; km/sec\n",
			OP, engineer_notation(node1->escape_velocity / CM_PER_KM, 6), CP);
		printf("  %smin-molecular-weight-retained %s%s\n",
			OP, engineer_notation(node1->molecule_weight, 3), CP);
		printf("  %ssurface-acceleration %s%s ; cm/sec2\n",
			OP, engineer_notation(node1->surface_accel, 6), CP);
		if (!node1->gas_giant)
		{
			printf("  %ssurface-gravity %s%s ; Earth gees\n",
				OP, engineer_notation(node1->surface_grav, 3), CP);
			printf("  %sh2o-boils %s%s ; degrees celcius\n",
				OP,
				engineer_notation(node1->boil_point - KELVIN_CELCIUS_DIFFERENCE, 3),
				CP);
			printf("  %ssurface-pressure %s%s ; Earth atmospheres\n",
				OP, engineer_notation(node1->surface_pressure / 1000.0, 3), CP);
			if (node1->greenhouse_effect && node1->surface_pressure > 0.0)
				printf("  %sgreenhouse 1%s\n", OP, CP);
			else
				printf("  %sgreenhouse 0%s\n", OP, CP);
			printf("  %ssurface-temperature %s%s ; degrees celcius\n",
				OP,
				engineer_notation(node1->surf_temp - KELVIN_CELCIUS_DIFFERENCE, 3),
				CP);
			printf("  %shydrosphere %s%s\n",
				OP, engineer_notation(node1->hydrosphere, 3), CP);
			printf("  %scloud-cover %s%s\n",
				OP, engineer_notation(node1->cloud_cover, 3), CP);
			printf("  %sice-cover %s%s\n",
				OP, engineer_notation(node1->ice_cover, 3), CP);
		}
		printf("  %salbedo %s%s\n",
			OP, engineer_notation(node1->albedo, 3), CP);
		printf(" %s\n", CP);
	}
	printf("%s\n", CP);
}

void display_system(innermost_planet)
planet_pointer innermost_planet;
{
     if (flag_graphics)
          chart_system(innermost_planet);
     else if (flag_lisp)
          lisp_describe_system(innermost_planet);
     else
     text_describe_system(innermost_planet);
}

