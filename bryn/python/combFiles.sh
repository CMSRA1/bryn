#!/usr/bin/bash

cd ../results/Data
hadd AK5Calo_Jets.root *.root &
cd ../JESplus
hadd AK5Calo_QCD_All.root  AK5Calo_QCD_Pt_*.root &
hadd AK5Calo_Zinv.root     AK5Calo_ZinvisibleJets_7TeV*.root &
hadd AK5Calo_WJets.root    AK5Calo_WJetsToLNu_*.root &
hadd AK5Calo_TTbar.root    AK5Calo_TTJets_*.root &
hadd AK5Calo_LM0.root      *LM0*.root &
hadd AK5Calo_LM1.root      *LM1*.root &
hadd AK5Calo_LM2.root      *LM2*.root &
hadd AK5Calo_LM3.root      *LM3*.root &
hadd AK5Calo_LM4.root      *LM4*.root &
hadd AK5Calo_LM5.root      *LM5*.root &
hadd AK5Calo_LM6.root      *LM6*.root &
hadd AK5Calo_LM7.root      *LM7*.root &
hadd AK5Calo_SingleTop.root AK5Calo_TToBLNu_TuneZ2_*.root &
cd ../JESminus
hadd AK5Calo_QCD_All.root AK5Calo_QCD_Pt_*.root &
hadd AK5Calo_Zinv.root  AK5Calo_ZinvisibleJets_7TeV*.root &
hadd AK5Calo_WJets.root AK5Calo_WJetsToLNu_*.root &
hadd AK5Calo_TTbar.root AK5Calo_TTJets_*.root &
hadd AK5Calo_LM0.root *LM0*.root &
hadd AK5Calo_LM1.root *LM1*.root &
hadd AK5Calo_LM2.root *LM2*.root &
hadd AK5Calo_LM3.root *LM3*.root &
hadd AK5Calo_LM4.root *LM4*.root &
hadd AK5Calo_LM5.root *LM5*.root &
hadd AK5Calo_LM6.root *LM6*.root &
hadd AK5Calo_LM7.root *LM7*.root &
hadd AK5Calo_SingleTop.root AK5Calo_TToBLNu_TuneZ2_*.root &
cd ../NoSmear
hadd AK5Calo_QCD_All.root AK5Calo_QCD_Pt_*.root &
hadd AK5Calo_Zinv.root  AK5Calo_ZinvisibleJets_7TeV*.root &
hadd AK5Calo_WJets.root AK5Calo_WJetsToLNu_*.root &
hadd AK5Calo_TTbar.root AK5Calo_TTJets_*.root &
hadd AK5Calo_LM0.root *LM0*.root &
hadd AK5Calo_LM1.root *LM1*.root &
hadd AK5Calo_LM2.root *LM2*.root &
hadd AK5Calo_LM3.root *LM3*.root &
hadd AK5Calo_LM4.root *LM4*.root &
hadd AK5Calo_LM5.root *LM5*.root &
hadd AK5Calo_LM6.root *LM6*.root &
hadd AK5Calo_LM7.root *LM7*.root &
hadd AK5Calo_SingleTop.root AK5Calo_TToBLNu_TuneZ2_*.root &
cd ../Smear
hadd AK5Calo_QCD_All.root AK5Calo_QCD_Pt_*.root &
hadd AK5Calo_Zinv.root  AK5Calo_ZinvisibleJets_7TeV*.root &
hadd AK5Calo_WJets.root AK5Calo_WJetsToLNu_*.root &
hadd AK5Calo_TTbar.root AK5Calo_TTJets_*.root &
hadd AK5Calo_LM0.root *LM0*.root &
hadd AK5Calo_LM1.root *LM1*.root &
hadd AK5Calo_LM2.root *LM2*.root &
hadd AK5Calo_LM3.root *LM3*.root &
hadd AK5Calo_LM4.root *LM4*.root &
hadd AK5Calo_LM5.root *LM5*.root &
hadd AK5Calo_LM6.root *LM6*.root &
hadd AK5Calo_LM7.root *LM7*.root &
hadd AK5Calo_SingleTop.root AK5Calo_TToBLNu_TuneZ2_*.root &
cd ../../python




