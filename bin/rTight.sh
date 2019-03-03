
cwd=`pwd`
cd /Users/jdb/bnl/vendor/6.14.04
source bin/thisroot.sh
cd $cwd

./pico.app ana.xml --p.XeeXpipi=3 --p.XeeCut=10 --p.min_nHitsFit=30 --p.min_nHitsDedx=25 --p.max_Dca=1 --ver=_Tight_Signal --p.min_pT=0.2 --p.min_nhr=0.52 --p.TpcEff="/Users/jdb/bnl/work/upc/embedding/output_eff_mass_TIGHT.root"
