#!/usr/bin/env python
#
# Vector Boson Taskforce electron ID implementation for RA1
#========================================================================================
#
# Here, "Loose" ID is identified with WP95 of the EWK Vector Boson Task Force (VBTF)
# while "Tight" ID is identified with WP80 of the same specification.
#
# Further details here:
# * CMS AN-2010/116 "Measurements of Inclusive W and Z Cross Sections in pp Collisions..."
# * https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID
#
# Notes:
# * There are different cut values for Barrel and Endcap electrons.
# * Electrons falling into the Barrel-Endcap "transition region" are IDed as non-Loose.
# * The eta values corresponding to these regions are hard-coded into the IDFilter
#   and decisions are made on the fly.

from icf.core import PSet

vbtfelectronidps = PSet(
    Verbose = False,
    LooseCuts = PSet(
        #isolation
        TrkIso = PSet(
            B = 0.15,
            E = 0.08,
            ),
        EclIso = PSet(
            B = 2.0,
            E = 0.06,
            ),
        HclIso = PSet(
            B = 0.12,
            E = 0.05,
            ),
        #conversion rejection
        ConversionNumHits = PSet(
            B = 1,
            E = 1,
            ),
        ConversionDcot = PSet(
            B = 999999.,
            E = 999999.,
            ),
        ConversionDist = PSet(
            B = 999999.,
            E = 999999.,
            ),
        #ID variables
        SigmaIEtaIEtaCut = PSet(
            B = 0.01,
            E = 0.03,
            ),
        DeltaPhiAtVertexCut = PSet(
            B = 999999.,
            E = 999999.,
            ),
        DeltaEtaAtVertexCut = PSet(
            B = 0.007,
            E = 0.01,
            ),
        HcalOverEcalCut = PSet(
            B = 0.15,
            E = 0.07,
            ),
        ),#end of LooseCuts
    TightCuts = PSet(
        #isolation
        TrkIso = PSet(
            B = 0.09,
            E = 0.04,
            ),
        EclIso = PSet(
            B = 0.07,
            E = 0.05,
            ),
        HclIso = PSet(
            B = 0.10,
            E = 0.025,
            ),
        #conversion rejection
        ConversionNumHits = PSet(
            B = 0,
            E = 0,
            ),
        ConversionDcot = PSet(
            B = 0.02,
            E = 0.02,
            ),
        ConversionDist = PSet(
            B = 0.02,
            E = 0.02,
            ),
        #ID variables
        SigmaIEtaIEtaCut = PSet(
            B = 0.01,
            E = 0.03,
            ),
        DeltaPhiAtVertexCut = PSet(
            B = 0.06,
            E = 0.03,
            ),
        DeltaEtaAtVertexCut = PSet(
            B = 0.004,
            E = 0.007,
            ),
        HcalOverEcalCut = PSet(
            B = 0.04,
            E = 0.025,
            ),
        ),#end of TightCuts
    )#end of VBTF electron ID PSet
