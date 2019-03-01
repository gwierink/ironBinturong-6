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
    writeCellSize

Description
    Write out approximate of cell size as a volume scalar field. The cell size
    is calculated by the cubic root of cell volume.

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

    volScalarField V
    (
        IOobject
        (
            mesh.V().name(),
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE,
            false
        ),
        mesh,
        dimensionedScalar(mesh.V().name(), mesh.V().dimensions(), 0),
        calculatedFvPatchField<scalar>::typeName
    );

    V.ref() = mesh.V();

    volScalarField dCell
    (
        IOobject
        (
            "dCell",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT
        ),
        Foam::pow(V, 1.0/3.0)
    );
    
    dCell.write();

    Info<< "\n end\n";

    return 0;
}


// ************************************************************************* //
