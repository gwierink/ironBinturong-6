/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

Application
    convertToPpm

Description
    Converts the concentration field C from mol/m3 to ppm, using the material
    properties set in constant/caseSettings.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    // Get times list
    instantList timeDirs = timeSelector::select0(runTime, args);

    Info<< "Reading case properties\n" << endl;

    IOdictionary caseSettings
    (
        IOobject
        (
            "caseSettings",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    // WIP - Make this utility use dimensioned data
    // dimensionedScalar rhoSteel
    // (
    //     caseSettings.lookup("rhoSteel")
    // );

    // For now, we can use non-dimensional data ...
    scalar rhoSteel(readScalar(caseSettings.lookup("rhoSteel")));
    scalar MC(readScalar(caseSettings.lookup("MC")));

    // For each time step read all fields
    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);
        Info<< "\nConvert field C [mol/m3] to Cppm [ppm] for time "
            << runTime.timeName() << endl;

        volScalarField C
        (
            IOobject
            (
                "C",
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            mesh
        );

        volScalarField Cppm
        (
            IOobject
            (
                "Cppm",
                runTime.timeName(),
                mesh,
                IOobject::READ_IF_PRESENT
            ),
            C*MC*1000.0/rhoSteel
        );
        
        Cppm.write();
    }

    Info<< "\n end\n";

    return 0;
}


// ************************************************************************* //
