# Content
`toolShed-6` currently contains:

## 1. Dissipation rate inlet BC for omega
OpenFOAM provides the turbulentMixingLengthDissipationRateInlet boundary
condition to automatically calculate the disspation rate based on turbulent
kinetic energy _k_ and a turbulent mixing length scale. This boundary condition
is set up to calculate dissipation rate _epsilon_ for the kEpsilon turbulence
model. The `turbulentMixingLengthOmegaInlet` does the same, but for the
kOmega(SST) turbulence model.

- Source code: `src/fvPatchFields/turbulentMixingLengthOmegaInlet`
- Example: `tutorials/incompressible/simpleFoam/pitzDaily`


## Disclaimer
This offering is not approved or endorsed by OpenCFD Limited, producer and
distributor of the OpenFOAM software and owner of the OPENFOAM® and OpenCFD®
trade marks.
