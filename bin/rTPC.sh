
cwd=`pwd`
cd /Users/jdb/bnl/vendor/6.14.04
source bin/thisroot.sh
cd $cwd

./pico.app ana.xml --p.XeeXpipi=3 --p.XeeCut=2 --p.min_nHitsFit=20 --p.min_nHitsDedx=15 --p.max_Dca=1 --ver=_TPC_Signal --p.min_pT=0.2 --p.min_nhr=0.52
