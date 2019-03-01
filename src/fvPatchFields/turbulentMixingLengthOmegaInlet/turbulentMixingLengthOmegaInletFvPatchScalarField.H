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

Class
    Foam::turbulentMixingLengthOmegaInletFvPatchScalarField

Description
    This boundary condition provides a turbulence dissipation, \f$\omega\f$
    (omega) inlet condition based on a specified mixing length.  The patch
    values are calculated using:

        \f[
            \omega_p = \frac{C_{\mu}^{-0.25} k^{0.5}}{L}
        \f]

    where

    \vartable
        \omega_p | patch omega values
        C_{\mu} | Model coefficient, set to 0.09
        k       | turbulence kinetic energy
        L       | length scale
    \endvartable

    In the event of reverse flow, a zero-gradient condition is applied.

Usage
    \table
        Property     | Description             | Required    | Default value
        mixingLength | Length scale [m]        | yes         |
        phi          | flux field name         | no          | phi
        k            | turbulence kinetic energy field name | no | k
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            turbulentMixingLengthOmegaInlet;
        mixingLength    0.005;
        value           uniform 200;   // placeholder
    }
    \endverbatim

See also
    Foam::inletOutletFvPatchField

SourceFiles
    turbulentMixingLengthOmegaInletFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef turbulentMixingLengthOmegaInletFvPatchScalarField_H
#define turbulentMixingLengthOmegaInletFvPatchScalarField_H

#include "inletOutletFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
   Class turbulentMixingLengthOmegaInletFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class turbulentMixingLengthOmegaInletFvPatchScalarField
:
    public inletOutletFvPatchScalarField
{
    // Private data

        //- Turbulent length scale
        scalar mixingLength_;

        //- Name of the turbulent kinetic energy field
        word kName_;


public:

    //- Runtime type information
    TypeName("turbulentMixingLengthOmegaInlet");


    // Constructors

        //- Construct from patch and internal field
        turbulentMixingLengthOmegaInletFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        turbulentMixingLengthOmegaInletFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  turbulentMixingLengthOmegaInletFvPatchScalarField
        //  onto a new patch
        turbulentMixingLengthOmegaInletFvPatchScalarField
        (
            const turbulentMixingLengthOmegaInletFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        turbulentMixingLengthOmegaInletFvPatchScalarField
        (
            const turbulentMixingLengthOmegaInletFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new turbulentMixingLengthOmegaInletFvPatchScalarField
                (
                    *this
                )
            );
        }

        //- Construct as copy setting internal field reference
        turbulentMixingLengthOmegaInletFvPatchScalarField
        (
            const turbulentMixingLengthOmegaInletFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new turbulentMixingLengthOmegaInletFvPatchScalarField
                (
                    *this,
                    iF
                )
            );
        }


    // Member functions

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
