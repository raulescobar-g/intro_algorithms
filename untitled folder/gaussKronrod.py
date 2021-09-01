"""
This function implements Gauss-Kronrod quadrature for numeric integration.

soln, splits = integrate(a, b, f)

soln, splits = integrate(a, b, f, tol)

inputs

a      is the lower limit of integration
b      is the upper limit of integration
f      is the function to be integrated
tol    is the error tolerance - it has a default

outputs

soln   is the solution to the integral
splits is the number of intervals halved and reintegrated because of error
"""

import numpy as np
from sortedcontainers import SortedDict

# maximum possible number of subintervals for integration is 2**maxSplits
maxSplits = 31

# the nodes and weights given here are for 7-15 Gauss-Kronrod quadrature
nG = 4    # total number of Gauss   nodes = 2*nG - 1
nK = 8    # total number of Kronrod nodes = 2*nK - 1
# the weights of Gauss quadrature; these are symmetric about x=0
GaussW = np.zeros(nG, dtype=float)
GaussW[0] = 0.417959183673469
GaussW[1] = 0.381830050505119
GaussW[2] = 0.279705391489277
GaussW[3] = 0.129484966168870

# the nodes of Kronrod quadrature; these have +/- values; there is a 0 node
# the Gauss nodes are in the even entries of these Kronrod nodes
KronrodN = np.zeros(nK, dtype=float)
KronrodN[1] = 0.207784955007898
KronrodN[2] = 0.405845151377397
KronrodN[3] = 0.586087235467691
KronrodN[4] = 0.741531185599394
KronrodN[5] = 0.864864423359769
KronrodN[6] = 0.949107912342759
KronrodN[7] = 0.991455371120813
# the weights of Kronrod quadrature; these are symmetric about x=0
KronrodW = np.zeros(nK, dtype=float)
KronrodW[0] = 0.209482141084728
KronrodW[1] = 0.204432940075298
KronrodW[2] = 0.190350578064785
KronrodW[3] = 0.169004726639267
KronrodW[4] = 0.140653259715525
KronrodW[5] = 0.104790010322250
KronrodW[6] = 0.063092092629979
KronrodW[7] = 0.022935322010529


def integrate(a, b, f, tol=100.0*np.finfo(float).eps):

    # perform Gauss-Kronrod integration over an interval
    def GaussKronrod(ai, bi):
        xMid = (bi + ai) / 2.0
        xAmp = (bi - ai) / 2.0
        # get solutions at the midpoint, i.e., at x = 0
        fMid = f(xMid)
        solnG = GaussW[0] * fMid
        solnK = KronrodW[0] * fMid
        # get solutions at the remaining nodes, which have +/- symetry
        for k in range(1, nK):
            fp = f(xMid + xAmp * KronrodN[k])
            fm = f(xMid - xAmp * KronrodN[k])
            solnK = solnK + KronrodW[k] * (fp + fm)
            if k % 2 == 0:
                # Gauss nodes are a subset of the Kronrod nodes
                solnG = solnG + GaussW[k//2] * (fp + fm)
        # estimate the local truncation error
        error = abs(solnK - solnG) / max(abs(solnG), 1.0)
        # scale the solution back to interval [ai, bi]
        solnG = xAmp * solnG
        return solnG, error

    # halve an interval when too much error, and reintegrate
    # call recursively until all subintervals have converged
    # use a sorted dictionary to hold the solution data
    def split(kL, splits):
        splits = splits + 1
        (kR, xL, xR, sOld) = sd[kL]
        # get mid-point value for x and its associated key
        xM = (xL + xR) / 2.0
        kM = (kL + kR) // 2
        # integrate the two subintervals
        sL, eL = GaussKronrod(xL, xM)
        sM, eM = GaussKronrod(xM, xR)
        # insert the data into the sorted directory
        sd[kL] = (kM, xL, xM, sL)
        sd[kM] = (kR, xM, xR, sM)
        # subdivide each subinterval if their error remains too large
        if eL > tol:
            splits = split(kL, splits)
        if eM > tol:
            splits = split(kM, splits)
        return splits

    # the main body of the program
    splits = 0
    keyLo = 0
    keyHi = 2**maxSplits
    soln, err = GaussKronrod(a, b)
    if err < tol:
        return soln, splits
    else:
        # create a sorted dictionary and begin refining the solution
        sd = SortedDict()
        sd[keyLo] = (keyHi, a, b, soln)
        splits = split(keyLo, splits)
    # sum up the individual solutions from the split intervals
    soln = 0.0
    atKey = keyLo
    atEnd = False
    while not atEnd:
        (kRgt, xLft, xRgt, deltaSoln) = sd[atKey]
        soln = soln + deltaSoln
        if kRgt == keyHi:
            atEnd = True
        else:
            atKey = kRgt

    return soln, splits

