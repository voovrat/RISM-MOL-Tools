# 30 Apr 2012
# available compounds:
# -  alkanes
#  - alcohols (COH) 
#  - ethers (COC)
#  - acetals (OCO)
#  - COOH
#  - COO-
#  - benzene C6H6
#  - phenyl  C6H5R

#   
#   FORCE FIELD DEFINITION
#
#  file consists of PATTERNs 
# pattern begins with a patten name with a ':' n separate line.
# e.g.
# methyl:
#
#  each pattern consists of two parts: definition of bonds and assignments of atom types
#
#  ------ definition of bonds ----
#
#  definition of bonds follow the pattern name
#  it consists of several rows
#  each row define the connections of atoms to the other atoms
#  the atom definition contain: 
#   - element name
#   - atom number in  a pattern in backets
#   - optionally - terminal symbol 'T'
# for example: 
#  C(1) means the carbon atom number one
#  C(5)T means the carbon terminal atom number 5
#  
#  in each pattern atoms should be numerated form 1 to N, where N is total number of atoms
#  ( all numbers 1..N should be used)
# 
#  terminal atom 'T'  means that not all conactions of the atom are given in the pattern 
# (so the connections will not be checked)
# 
#  also, there are two special atom elements
#     * means any atom type
#     R means residue (e.g. any atom or group of atoms)
#     technically, R(N) is equal to *(N)T
#
#  each line define connections of the first atom to other atoms.
#  f.e. 
#   C(1) H(2) H(3) H(4) R(5)
#  means that carbon atom #1 is connected to three hydrogen atoms (#2,#3,#4) and to any number of oter atoms (R).
#
#  all lines in the pattern define the full connections in the pattern (see the patterns below for examples) 
#
#  ---- assignments of atom types ---
#
#  after the first section the next section - assignment of atom types -- follows.
#
#  it contains of several lines
#  each line - one asignment
# it consists of the atom definition, ':' symbol and atom name in the force field
#
# for example 
#  C(1) : methyl_C 
#  means that the first atom in the patten has  a methyl_C name in the force field
#  not all the atoms should necesarrily have the force field names 
# (especially: R atoms and  * atoms probably should not have the force field names.
# Although it is not prohibited by the program, this is quite unatural and will lead to wrong assignments)
# 

########### CH3 (methyl)

methyl:
C(1) H(2) H(3) H(4) R(5)

C(1) : opls_135 # methyl_C
H(2) : opls_140 # methyl_H
H(3) : opls_140 # methyl_H 
H(4) : opls_140 # methyl_H


###########   CH2 

# Note: CH3 also match this pattern, but because it is before, it will be matched beforehead
alkane_CH2:
C(1) H(2) H(3) C(4)T C(5)T

C(1) : opls_136 # alkane CH2 CH2_C
H(2) : opls_140 # alkane H #CH2_H
H(3) : opls_140 #CH2_H

alkane_CH:
C(1) H(2) C(3)T C(4)T C(5)T

C(1) : opls_137
H(2) : opls_140

alkane_C: 
C(1) C(2)T C(3)T C(4)T C(5)T

C(1): opls_139

alkane_CH4:
C(1) H(2) H(3) H(4) H(5)

C(1) : opls_138
H(1) : opls_140
H(2) : opls_140
H(3) : opls_140
H(4) : opls_140
H(5) : opls_140


############  COOH
COOH:
C(1) O(2) O(3) R(4)
O(2) H(5)

C(1) : opls_267 # COOH_C
O(2) : opls_268 # COOH_Ohyd
O(3) : opls_269 # COOH_Odb
H(5) : opls_270 # COOH_H

############ CH3COO
CH3COO:
C(1) O(2) O(3) C(4)
C(4) H(5) H(6) H(7)

C(1) : opls_271 # C in COO-
O(2) : opls_272 # O in COO-
O(3) : opls_272 # O in COO-
C(4) : opls_273 # C in CH3 in CH3COO-
H(5) : opls_140 # H in alkanes
H(6) : opls_140 # H in alkanes
H(7) : opls_140 # H in alkanes

############## CH2COO
CH2COO:
C(1) O(2) O(3) C(4)
C(4) H(5) H(6) R(7)

C(1) : opls_271 # C in COO-
O(2) : opls_272 # O in COO-
O(3) : opls_272 # O in COO-
C(4) : opls_274 # C in CH2 in CH2COO-
H(5) : opls_140 # H in alkanes
H(6) : opls_140 # H in alkanes

############## CHCOO
CHCOO:
C(1) O(2) O(3) C(4)
C(4) H(5) R(6) R(7)

C(1) : opls_271 # C in COO-
O(2) : opls_272 # O in COO-
O(3) : opls_272 # O in COO-
C(4) : opls_275 # C in CH in CHCOO-
H(5) : opls_140 # H in alkanes


# note: C(1) O(2) O(4) C(4)T does not work because of bug:
# T atoms are not assigned properly
############# CCOO
CCOO:
C(1) O(2) O(3) C(4)
C(4) C(5)T C(6)T C(7)T

C(1) : opls_271 # C in COO-
O(2) : opls_272 # O in COO-
O(3) : opls_272 # O in COO-
C(4) : opls_276 # C in C in CCOO-

############# phenyl-CCOO 
PhCCOO:
C(1) O(2) O(3) C(4)
C(4) C(5)T C(6)T

C(1) : opls_271 # C in COO-
O(2) : opls_272 # O in COO-
O(3) : opls_272 # O in COO-
C(4) : opls_276 # C in C in CCOO-

############# OH (alcohols)
# Note: OH group should stay AFTER COOH, because OH is part of COOH 
# methanol
CH3OH:
O(1) H(2) C(3)
C(3) H(4) H(5) H(6)

O(1) : opls_154 #hydroxyl_O
H(2) : opls_155 #hydroxyl_H
C(3) : opls_157 # C in H2COH, H3COH
H(4) : opls_156 # H in methanol
H(5) : opls_156
H(6) : opls_156

#CH2OH
CH2OH:
O(1) H(2) C(3)
C(3) H(4) H(5) C(6)T

O(1) : opls_154 # O in OH in alcohols
H(2) : opls_155 # H in OH in alcohols
C(3) : opls_157 # C in H2COH
H(4) : opls_140 # alkane H
H(5) : opls_140 # alkane H

#CHCOH
CHOH:
O(1) H(2) C(3)
C(3) H(4) C(5)T C(6)T

O(1) : opls_154 # O in OH in alcohols
H(2) : opls_155 # H in OH in alcohols
C(3) : opls_158 # C in HCOH
H(4) : opls_140 # alkane H

#COH
COH:
O(1) H(2) C(3)
C(3) C(4)T C(5)T C(6)T

O(1) : opls_154 # O in OH in alcohols
H(2) : opls_155 # H in OH in alcohols
C(3) : opls_159 # C in COH

############## ketone
# Note: After COOH
ketone:
C(1) O(2) R(3) R(4)

C(1) : opls_280  # ketone_C
O(2) : opls_281  # ketone_O

##############  Acetal O-C-O
#OCH2O
OCH2O:
C(1) O(2) O(3) H(4) H(5)
O(2) C(6)T
O(3) C(7)T

C(1) : opls_189 # C in OCH2O (+0.2)
O(2) : opls_186 # O acetal ether (-0.4)
O(3) : opls_186 
H(4) : opls_190 # H in OCH2O (+0.1)
H(5) : opls_190

#OCHO
OCH2O:
C(1) O(2) O(3) H(4) C(5)T
O(2) C(6)T
O(3) C(7)T

C(1) : opls_193 # C in OCHO (+0.3)
O(2) : opls_186 # O acetal ether (-0.4)
O(3) : opls_186 
H(4) : opls_194 # H in OCHO (+0.1)

#OCO
OCO:
C(1) O(2) O(3) C(4)T C(5)T
O(2) C(6)T
O(3) C(7)T

C(1) : opls_197 # C in OCO (+0.4)
O(2) : opls_186 # O acetal ether (-0.4)
O(3) : opls_186 


############## dyalkyl ether 
# NOTE: AFTER acetal (OCO)
# methyl ether:
H3COC:
O(1) C(2) C(3)T
C(2) H(4) H(5) H(6)

O(1) : opls_180 # dialkyl ether  #ether_O
C(2) : opls_181 # C in H3CO in H3COC (charge 0.11)
H(4) : opls_185 # alpha H ether (charge 0.03)
H(5) : opls_185
H(6) : opls_185

# ethyl ether:
H2COC:
O(1) C(2) C(3)T
C(2) H(4) H(5) C(6)T

O(1) : opls_180 # dialkyl ether  #ether_O
C(2) : opls_182 # C in H2CO in H2COC (charge 0.14)
H(4) : opls_185 # alpha H ether (charge 0.03)
H(5) : opls_185

#HCOC
HCOC:
O(1) C(2) C(3)T
C(2) H(4) C(5)T C(6)T

O(1) : opls_180 # dialkyl ether  #ether_O
C(2) : opls_183 # C in HCO in HCOC (charge 0.17)
H(4) : opls_185 # alpha H ether (charge 0.03)

#COC
COC:
O(1) C(2) C(3)T
C(2) C(4)T C(5)T C(6)T

O(1) : opls_180 # dialkyl ether  #ether_O
C(2) : opls_184 # C in CO in COC (charge 0.2)



# graphene, CNT, fulerene, etc
# NOTE: before benzene. Otherwise it starts to travell acrros the graphene structure  and hangs...
graphene:
C(1) C(2)T C(3)T C(4)T

C(1) : opls_147
# benzene
benzene:
C(1) C(2) C(6) H(7)
C(2) C(1) C(3) H(8)
C(3) C(2) C(4) H(9)
C(4) C(3) C(5) H(10)
C(5) C(4) C(6) H(11)
C(6) C(5) C(1) H(12)

C(1) : opls_145 # benzene_C
C(2) : opls_145 # benzene_C
C(3) : opls_145 # benzene_C
C(4) : opls_145 # benzene_C
C(5) : opls_145 # benzene_C
C(6) : opls_145 #benzene_C
H(7) : opls_146 #benzene_H
H(8) : opls_146 #benzene_H
H(9) : opls_146 #benzene_H
H(10) : opls_146 #benzene_H
H(11) : opls_146 #benzene_H
H(12) : opls_146 #benzene_H

#phenyl (after benzene)
phenyl:
C(1) C(2) R(7)
C(2) C(3) H(8)
C(3) C(4) H(9)
C(4) C(5) H(10)
C(5) C(6) H(11)
C(6) C(1) H(12)

C(1) : opls_145
C(2) : opls_145 # benzene_C
C(3) : opls_145 # benzene_C
C(4) : opls_145 # benzene_C
C(5) : opls_145 # benzene_C
C(6) : opls_145 #benzene_C
H(8) : opls_146 #benzene_H
H(9) : opls_146 #benzene_H
H(10) : opls_146 #benzene_H
H(11) : opls_146 #benzene_H
H(12) : opls_146 #benzene_H



