/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::solidBodyMotionFunctions::myOscillatingRotatingMotion

Description
    SolidBodyMotionFvMesh 6DoF motion function. Oscillating rotation.

SourceFiles
    myOscillatingRotatingMotion.C

\*---------------------------------------------------------------------------*/

#ifndef myOscillatingRotatingMotion_H
#define myOscillatingRotatingMotion_H

#include "solidBodyMotionFunction.H"
#include "primitiveFields.H"
#include "point.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace solidBodyMotionFunctions
{

/*---------------------------------------------------------------------------*\
                          Class myOscillatingRotatingMotion Declaration
\*---------------------------------------------------------------------------*/

class myOscillatingRotatingMotion
:
    public solidBodyMotionFunction
{
    // Private data

        //- Centre of gravity
        point origin_;

        //- Amplitude
        vector amplitude_;

        //- Radial velocity
        scalar omega_;
        //- initial offset of inner AMI rotation state in multiples of pi
        scalar initialOffset_;

        //- Centre of gravity or outter AMI zone
        point outterOrigin_;

        //- radius between inner and outter AMI zones
        scalar outterRadius_;

        //- Radial velocity of outter AMI zone
        scalar outterOmega_;

        //- initial offset of inner AMI zone in multiples of pi
        scalar outterInitialOffset_;

    // Private Member Functions

        //- Disallow copy construct
        myOscillatingRotatingMotion(const myOscillatingRotatingMotion&);

        //- Disallow default bitwise assignment
        void operator=(const myOscillatingRotatingMotion&);


public:

    //- Runtime type information
    TypeName("myOscillatingRotatingMotion");


    // Constructors

        //- Construct from components
        myOscillatingRotatingMotion
        (
            const dictionary& SBMFCoeffs,
            const Time& runTime
        );
        
        
        //- Construct and return a clone
        virtual autoPtr<solidBodyMotionFunction> clone() const
        {
            return autoPtr<solidBodyMotionFunction>
            (
                new myOscillatingRotatingMotion
                (
                    SBMFCoeffs_,
                    time_
                )
            );
        }


    //- Destructor
    virtual ~myOscillatingRotatingMotion();


    // Member Functions

        //- Return the solid-body motion transformation septernion
        virtual septernion transformation() const;

        //- Update properties from given dictionary
        virtual bool read(const dictionary& SBMFCoeffs);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace solidBodyMotionFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
