
RISM-MOL-Tools
rismff
RISM-FF
RISM-MOL-3D
RISM-MOL-3D
rism-vmol
RISM-VMOL

RISM-MOL-Tools include:

    RISM-MOL-3D (3DRISM package)
    RISM-MOL-FF (package to assign force-fields)
    RISM-VMol (package for visualizing the binding sites)
    other useful tools, like createSlv, createOmega, 3DtoDX etc.
    VMD RISM-MOL plugin

How to install:

1 Download

2    Compile fftw and lapack libraries
    (it can take some time. If you already have lapack & fftw:just put them to libfftw3.a and lapack_LINUX.a files in the rism-mol-tools folder)

    ./makeFFTW
    ./makeLAPACK

3   Compile the RISM-MOL-Tools
    ./makeAll

4   Setup paths

    export PATH=$PATH:$(pwd)
    echo 'export PATH=$PATH:'$(pwd) >> ~/.bashrc

    (NOTE: these lines are only for bash)
5   Install vmd plugin
    (you can get VMD at http://www.ks.uiuc.edu/Research/vmd/ )

    ./installVmdPlugin


---------------------------
-- at this point you can perform 3drism calculations 
-- see the documentation 
---------------------

HOW TO CALCULATE Solvation Free Energy:


1    Create solvent files
    assignSolventFF water.composition > water.rism
    createSlv water.composition water.rism > water.slv
    createOmega water.composition > waterOmega.txt

2    Create solute input

    Simplest example:

    echo 0 0 0 3.5 0.15 0 >file.rism

    (first 3 columns - coordinates (Angstr), 4th - sigma (Angstr), 5th -epsilon (kcal/mol), 6th - charge (e))

    More complicated: if you have pdb or xyz file (for example file.pdb), type

    coors2pat file.pdb > file.pat
    assignAtomTypes file.pat oplsaa.ff > file.at
    createRismInput file.pdb file.at oplsaa.ff > file.rism
    Run 3DRISM
    multiGridMain parameters_fast.txt 'SoluteStructureFile="file.rism";'

    calculate solvation free energy
    calculateFreeEnergySimple file_in_water_


NOTE: if you want to run 3DRISM form other folder, you will need:

    to copy water.slv to that folder
    to copy parameters_fast.txt to that folder
    to modify parameters_fast.txt to put full paths to the files at lines:

    SolventOmegaFile="(full path to your RISM-MOL-Tools instalation)/waterOmega.txt";
    SolventRDFsFile="(full path to your RISM-MOL-Tools instalation)/waterRDFs.txt";


ALSO:  Read the documentation in doc.pdf


============================================


How to use VMD plugin:

To test the vmd plugin:

    1. In the installation folder run vmd 
    2. In the main menu select Extentions->RISM-MOL-Tools->binding 
    3. Fill the fields. If you are in the installation folder - you can leave all the fields untouched 

The fields:

-Solute Coordinates: the solute coordinate file in *xyz or *pdb format.

-Solute ForceField: force-field for the solute if *ff format.

    The standard force field oplsaa.ff is distributed with rism-mol-tools, however it still includes only a few molecule types.
    You can extend the force-field if you need
    (see instructions inside the oplsaa.ff file)
-Solvent composition: file which describes the solvent.

    Each line coresponds to one solvent component.
    The first column is the name of xyz or pdb structure file.
    The second column is the name of ff force-field file.
-Solvent RDFs: is the file which contains the RDFs of the solvent.

    With rism-mol-tools only the waterRDFs.txt is distributed - the RDFs for water molecule.
    The RDFs for outer solvents can be calculated using the AmberTools rism1d.
    3DRISM parameters: parameters for the 3DRISM calculations.
    The standard file is parameters_fast.txt.
    For more details see the documentation to RISM-MOL-3D program.
4. Push the button "Run 3DRISM". Wait 3-5 min.

    After the 3DRISM calculations are finished, the *distr files for each solvent component will be created.
    These files contain the names of 3d distributions for each solvent component.
    Select in the field "Distributions" one of these files, select the threshold to show binding molecules, and run "show binding molecules."
5. Push the buttom "show Binding molecules". Wait 2-3 min.

    the picture like this will appear in the VMD OpenGL window.
6. If you cannot or do not want to use the VMD, you can simply run the shell commands:

    run3DRISM solute.xyz solute.ff solvent.composition solvent.rdfs parameters.txt

    runBinding distribution.distr threshold solvent.composition

(#this is actually what VMD plugins do)
Example:

    run3DRISM CD.xyz oplsaa.ff water.composition waterRDFs.txt parameters_fast.txt

    runBinding CD_in_water_water.distr 2 water.composition
The following openable files whill be created:

    CD_in_water_water_Gmax.dx - 3d water distribution

    CD_in_water_water_binding.xyz - the file with binding water molecules

Visit the page on wikispaces.org

