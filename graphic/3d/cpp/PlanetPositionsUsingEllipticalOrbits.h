// http://www.stargazing.net/kepler/ellipse.html
//
// Calculate the position of major planets within an
// accuracy of one arc minute.

#include <cmath>
#include <iostream>

#include "point3d.h"

//#define rads (M_PI/180.0)
  #define rads 1.0

class PlanetPositionsUsingEllipticalOrbits {

  public:

  PlanetPositionsUsingEllipticalOrbits() :
    
     //  Initialize the seven 'oscilating elements'
     //  for the planets, as valid per
     //  julian date (JD) = 2450680.5
     //
     //  Note: The Julian date (JD) is the interval 
     //  of time in days and fractions of a day since 
     //  January 1, 4713 BC Greenwich noon,
     //  
     //  As per http://aa.usno.navy.mil/data/docs/JulianDate.php
     //  this corresponds to 
     //  -> CE 1997 August 20 00:00:00.0 UT  Wednesday
     //
     mercury(  7.00507           , // {
              48.3339            ,
              77.45399999999999  ,
               0.3870978         ,
               4.092353          ,
               0.2056324         ,
             314.42369         )
     ,                             // }
     venus  (  3.39472           , // {
              76.6889            ,      
             131.761             ,      
               0.7233238         ,      
               1.602158          ,      
               0.0067933         ,      
             236.94045         )
     ,                             // }
     earth  (  0.00041           , // {
             349.2               ,           
             102.8517            ,           
               1.00002           ,                 
               0.9855796         ,           
               0.0166967         ,                  
             328.40353         )  
     ,                             // }
     mars   (  1.84992           , // {
              49.5664            ,    
             336.0882            ,   
               1.5236365         ,         
               0.5240613         ,   
               0.0934231         ,          
             262.42784    )         
     ,                             // }
     jupiter(  1.30463           , // {         
             100.4713            ,          
              15.6978            ,           
               5.202597          ,                  
               0.08309618000000001, // 8.309618000000001D-02 ,        
               0.0484646,                            
             322.55983         )                    
     ,                             // }
     saturn (  2.48524           , // {         
             113.6358            ,       
              88.863             ,         
               9.571899999999999 ,     
               0.03328656        ,      
               0.0531651         ,              
              20.95759         )       
     ,                             // }
     uranus (  0.77343           , // {         
              74.0954            ,          
             175.6807            ,         
              19.30181           ,                
               0.01162295        ,        
               0.0428959         ,                
             303.18967 )        
     ,                             // }
     neptune(  1.7681            , // {         
             131.7925            ,    
               7.206             ,       
              30.26664           ,           
               0.005919282       ,  
               0.0102981         ,           
             299.8641 )          
     ,                             // }
     pluto  ( 17.12137           , // {         
             110.3833            ,      
             224.8025            ,      
              39.5804            ,              
               0.003958072       ,         
               0.2501272         ,                  
             235.7656 )           // }     
     {}


  struct Planet {

     //     seven 'oscilating elements'. {
     //     -----------------------------
     //     The Astronomical Almanac provides 7 numbers 
     //     to specify an orbit: 
     //
     double inclination;              
     //     angle between the plane of the Ecliptic 
     //     and the plane of the orbit. 
     //
     double longitudeOfAscendingNode; 
     //     states the position in the orbit where 
     //     the elliptical path of the planet passes 
     //     through the plane of the ecliptic, from 
     //     below the plane to above the plane. 
     //
     double longitudeOfPerihelion;    
     //     states the position in the orbit where 
     //     the planet is closest to the Sun. 
     //
     double meanDistanceAU;             
     //     the value of the semi-major axis of the                                      
     //     orbit - measured in Astronomical Units                                       
     //     for the major planets.                                                       
     //
     double dailyMotion;              
     //     states how far (in degrees?) the planet moves                                      
     //     in one (mean solar) day. This figure                                            
     //     can be used to find the mean anomaly                                            
     //     of the planet for a given number of                                             
     //     days either side of the date of the                                             
     //     elements. The figures quoted in the                                             
     //     Astronomical Almanac do not tally with                                          
     //     the period of the planet as calculated                                          
     //     by applying Kepler's 3rd Law to the                                             
     //     semi-major axis.                                                                
     //
     double eccentricity;
     //     eccentricity of the ellipse which 
     //     describes the orbit 
     //
     double meanLongitude;
     //     Position of the planet in the orbit 
     //     on the date of the elements. 
     //
     //     -------------------------------------- }
     //     Constructor of a Planet...   {
     Planet(
       double i,
       double o,
       double p,
       double a,
       double n,
       double e,
       double l
     ) : 
     inclination              (i / 180.0 * M_PI ),
     longitudeOfAscendingNode (o / 180.0 * M_PI ),
     longitudeOfPerihelion    (p / 180.0 * M_PI ),
     meanDistanceAU           (a),
     dailyMotion              (n / 180.0 * M_PI ),
     eccentricity             (e /*180.0 * M_PI */),
     meanLongitude            (l / 180.0 * M_PI ) {}
     //       --------------------       }
     double meanAnomaly(double difference_JD) {
//          std::cout << "dailyMotion: " << dailyMotion << std::endl;
//          std::cout << "difference_JD: " << difference_JD << std::endl;
//          std::cout << "meanLongitude: " << meanLongitude << std::endl;
//          std::cout << "longitudeOfPerihelion: " << longitudeOfPerihelion << std::endl;

            return dailyMotion * difference_JD + meanLongitude - longitudeOfPerihelion;
     }
     double trueAnomaly(double difference_JD) {

            double  meanAnomaly_ = meanAnomaly(difference_JD);

            return  meanAnomaly_ +
                 /* 180.0/M_PI * */ (
                       ( (2.0 * eccentricity - std::pow(eccentricity, 3.0)/4.0) * std::sin(    meanAnomaly_) ) +
                       (  5.0/ 4.0  *          std::pow(eccentricity, 2.0)      * std::sin(2.0*meanAnomaly_) ) +
                       ( 13.0/12.0  *          std::pow(eccentricity, 3.0)      * std::sin(3.0*meanAnomaly_) )
                    );
                 
     }
     double distanceFromFocusAU(double difference_JD) { // Astronomical Units?
            return  meanDistanceAU * ( 1.0 - std::pow(eccentricity, 2.0) ) / ( 1.0 + eccentricity * std::cos(trueAnomaly(difference_JD)));
     }
     point3d positionAU(double difference_JD) {

             double r = distanceFromFocusAU(difference_JD);
             double v = trueAnomaly        (difference_JD);

             double anglePlanetFromAscendingNode = v + longitudeOfPerihelion - longitudeOfAscendingNode;

             double cos_anglePlanetFromAscendingNode = std::cos(anglePlanetFromAscendingNode) ; //* std::cos(anglePlanetFromAscendingNode);
             double sin_anglePlanetFromAscendingNode = std::sin(anglePlanetFromAscendingNode);
             

             return point3d (
                    r * ( std::cos(longitudeOfAscendingNode) * cos_anglePlanetFromAscendingNode - std::sin(longitudeOfAscendingNode) * sin_anglePlanetFromAscendingNode * std::cos(inclination) ),
                    r * ( std::sin(longitudeOfAscendingNode) * cos_anglePlanetFromAscendingNode + std::cos(longitudeOfAscendingNode) * sin_anglePlanetFromAscendingNode * std::cos(inclination) ),
                    r *                                                                                                                sin_anglePlanetFromAscendingNode * std::sin(inclination) 
             );
     }

  };

  //     The Planets are:
  Planet mercury,
         venus,
         earth,
         mars,
         jupiter,
         saturn,
         neptune,
         uranus,
         pluto;
};
