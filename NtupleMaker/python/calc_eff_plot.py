#!/usr/bin/env python
import numpy
import os, sys, re
import ROOT
from ROOT import TCanvas, TFile, TH1F
#from ROOT import gRoot
#from ROOT import gDirectory

from optparse import OptionParser

parser = OptionParser()
parser.add_option('--input', '-i', action='store',
		default='output_oldTrigFull.root', dest='inputFile',
		help='input root file folder'
		)
parser.add_option('--var', '-v', action='store',
		default="t1_pt_A", dest='variable',
		help='eff as a func of this variable'
		)
parser.add_option('--bin', '-b', action='store',
		default="20,0,400", dest='binning',
		help='binning'
		)
parser.add_option('--outputdir', '-o', action='store',
		default="../plots", dest='outputDir',
		help='output location for plot'
		)
(options, args) = parser.parse_args()

#ROOT.gROOT.SetBatch(ROOT.kTRUE) #sets plots not to display when drawn

def main():
    # get input from parser
    inFile = options.inputFile
    var = options.variable
    bins = options.binning
    outDir = options.outputDir

    # open input root file and input tree
    f=ROOT.TFile(inFile)
    tree = f.Get("outTree")

    f.cd()

    # from the input file, make a histogram of a variable, give it a specific binning and selection
    tree.Draw(var + ">>" + var + "_passSelAndNewTrig" + '(' + bins + ')', "passNewTrig>0 && passSel > 0")
    tree.Draw(var + ">>" + var + "_passSel"  + '(' + bins + ')', "passSel>0")

    # get the new histograms
    passBothHistName = var+"_passSelAndNewTrig"
    passSelHistName  = var+"_passSel"
    bothHist = f.Get(passBothHistName)
    selHist  = f.Get(passSelHistName)
    
    print(bothHist.Integral())

    effHist = bothHist.Clone()
    #effHist.Add(selHist,1.0)
    effHist.Divide(selHist)

       
    # create output file, overwrite it if it already exists
    ofName = outDir + "/%s_eff.root"%(var)
    of = TFile(ofName, 'recreate')

    #write histograms to output file
    of.cd()
    effHist.Write()
 

    # close input and output files
    of.Close()
    f.Close()


if __name__ == "__main__":
	main()
