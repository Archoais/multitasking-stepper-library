#include <cs50.h>
#include <stdio.h>

int main(void)
{   int max_pulses = 2000;
    int x_pulses [max_pulses];
    int y_pulses [max_pulses];
    int z_pulses [max_pulses];
    
    int dimentions = 3;
    int xyz_coordinate [dimentions];
    
    for(int i=0; i<dimentions; i++)
    {
        xyz_coordinate [i] = get_int("Please enter coordinate # %i:  ", i+1);
    }
    
    int longest_pulse;
    for(int j=0; j<dimentions; j++)
    {
        if(xyz_coordinate [0] >= xyz_coordinate [1] && xyz_coordinate [0] >= xyz_coordinate [2])
        {
            longest_pulse = xyz_coordinate [0];
        }
        if(xyz_coordinate [1] >= xyz_coordinate [0] && xyz_coordinate [1] >= xyz_coordinate [2])
        {
            longest_pulse = xyz_coordinate [1];
        }
        if(xyz_coordinate [2] >= xyz_coordinate [1] && xyz_coordinate [2] >= xyz_coordinate [0])
        {
            longest_pulse = xyz_coordinate [2];
        }
    }
    
    int x_factor = longest_pulse / xyz_coordinate [0];
    int y_factor = longest_pulse / xyz_coordinate [1];
    int z_factor = longest_pulse / xyz_coordinate [2];
    
    int x = 1;
    int y = 1;
    int z = 1;
    float v = 1.0;
    
    for(int k = 1; k <= longest_pulse; k++)
    {
        
        if (v>=((float)longest_pulse/xyz_coordinate [0])*x && v<= 1.0+((float)longest_pulse/xyz_coordinate [0])*x)
        {
            x_pulses [k-1] = x_pulses [k-1] + x;
            x++;
        }
        else
        {
            x_pulses [k-1] = 0;
        }
        if (v>=((float)longest_pulse/xyz_coordinate [1])*y && v<=1.0+((float)longest_pulse/xyz_coordinate [1])*y)
        {
            y_pulses [k-1] =  y_pulses [k-1] + y;
            y++;
        }
        else
        {
            y_pulses [k-1] = 0;
        }
        if (v>=((float)longest_pulse/xyz_coordinate [2])*z && v<=1.0+((float)longest_pulse/xyz_coordinate [2])*z)   
        {
            z_pulses [k-1] = z_pulses [k-1] + z;
            z++;
        }
        else
        {
            z_pulses [k-1] = 0;
        }
        v = v + 1.0;
    }
    
    for(int n = 0; n < longest_pulse; n++)
    {
        printf("%i   %i   %i   \n", x_pulses[n], y_pulses[n], z_pulses[n]);
    }
    
}