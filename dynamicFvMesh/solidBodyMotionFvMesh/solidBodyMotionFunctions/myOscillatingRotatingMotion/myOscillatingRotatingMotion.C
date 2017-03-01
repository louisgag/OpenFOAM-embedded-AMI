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
    
    Modifications to the original oscillatingRotatingMotion code made by Louis Gagnon : louis.gagnon@polimi.it copyright 2017

\*---------------------------------------------------------------------------*/

#include "myOscillatingRotatingMotion.H"
#include "addToRunTimeSelectionTable.H"
#include "mathematicalConstants.H"

using namespace Foam::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace solidBodyMotionFunctions
{
    defineTypeNameAndDebug(myOscillatingRotatingMotion, 0);
    addToRunTimeSelectionTable
    (
        solidBodyMotionFunction,
        myOscillatingRotatingMotion,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solidBodyMotionFunctions::myOscillatingRotatingMotion::
myOscillatingRotatingMotion
(
    const dictionary& SBMFCoeffs,
    const Time& runTime
)
:
    solidBodyMotionFunction(SBMFCoeffs, runTime)
{
    read(SBMFCoeffs);
}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

Foam::solidBodyMotionFunctions::myOscillatingRotatingMotion::
~myOscillatingRotatingMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::septernion
Foam::solidBodyMotionFunctions::myOscillatingRotatingMotion::
transformation() const
{
    scalar t = time_.value();

    vector eulerAngles = amplitude_ * sign(omega_) * ( sin(fabs(omega_*t) + initialOffset_*pi ) - sin( initialOffset_*pi ) );  /// the second sin is to ensure that the value is null at time = 0

    eulerAngles *= pi/180.0;


     vector calcOrigin_ = outterOrigin_ + outterRadius_ * vector (sign(outterOmega_)*cos(fabs(outterOmega_)*t + outterInitialOffset_*pi ), sin(fabs(outterOmega_*t) + outterInitialOffset_*pi), 0);

//label patchI = patchData_.applyToPatch(pp.index());
//Info << "patchData_[patchI].patchName()" << patchData_[this].patchName() << endl;
//Info << "**************************" << endl;
//Info << "sign(outterOmega_) " << sign(outterOmega_) << endl;
//Info << "fabs(calcOrigin_.x()) " << fabs(calcOrigin_.x()) << endl;
//Info << "eulerAngles.z() " << eulerAngles.z() << endl;
//     
//   Info << "calcOrigin_ = " << calcOrigin_ << endl;
//        Info << "outterOrigin_ = " << outterOrigin_ << endl;
////            Info << "outterRadius_ = " << outterRadius_ << endl;
//                      Info << "outterInitialOffset_ = " << outterInitialOffset_ << endl;
//Info << "**************************" << endl;

     quaternion R(quaternion::XYZ, eulerAngles);
     septernion TR(septernion(-calcOrigin_)*R*septernion(calcOrigin_));



//    DebugInFunction << "solidBodyMotionFunctions::myOscillatingRotatingMotion::"
//        << "transformation(): "
//        << "Time = " << t << " transformation: " << TR << endl;

    return TR;
}


bool Foam::solidBodyMotionFunctions::myOscillatingRotatingMotion::read
(
    const dictionary& SBMFCoeffs
)
{
    solidBodyMotionFunction::read(SBMFCoeffs);

    SBMFCoeffs_.lookup("origin") >> origin_;
    SBMFCoeffs_.lookup("amplitude") >> amplitude_;
    SBMFCoeffs_.lookup("omega") >> omega_;
    SBMFCoeffs_.lookup("initialOffset") >> initialOffset_;

    SBMFCoeffs_.lookup("outterOrigin") >> outterOrigin_;
    SBMFCoeffs_.lookup("outterOmega") >> outterOmega_;
    SBMFCoeffs_.lookup("outterRadius") >> outterRadius_;
    SBMFCoeffs_.lookup("outterInitialOffset") >> outterInitialOffset_;

    return true;
}

// ************************************************************************* //
