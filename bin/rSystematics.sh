#!/usr/local/bin/zsh


./pico.app config/ana.xml --p.XeeXpipi=3 --p.XeeCut=10 --p.min_nHitsFit=30 --p.min_nHitsDedx=25 --p.max_Dca=1 --ver=_Tight_Quality --p.min_pT=0.2 --p.min_nhr=0.52 --p.EFFICIENCY="TIGHT" >& out/log_Tight_Quality.log

./pico.app config/ana.xml --p.XeeXpipi=0 --p.XeeCut=4 --p.min_nHitsFit=30 --p.min_nHitsDedx=25 --p.max_Dca=1 --ver=_Tight_Quality_PID4 --p.min_pT=0.2 --p.min_nhr=0.52 --p.EFFICIENCY="TIGHT" >& out/log_Tight_Quality_PID4.log

./pico.app config/ana.xml --p.XeeXpipi=0 --p.XeeCut=2 --p.min_nHitsFit=30 --p.min_nHitsDedx=25 --p.max_Dca=1 --ver=_Tight_Quality_PID2 --p.min_pT=0.2 --p.min_nhr=0.52 --p.EFFICIENCY="TIGHT" >& out/log_Tight_Quality_PID2.log

./pico.app config/ana.xml --p.XeeXpipi=3 --p.XeeCut=10 --ver=_NOMINAL >& out/log_NOMINAL.log

./pico.app config/ana.xml --p.XeeXpipi=0 --p.XeeCut=4 --ver=_Tight_PID4 >& out/log_Tight_PID4.log

./pico.app config/ana.xml --p.XeeXpipi=0 --p.XeeCut=2 --ver=_Tight_PID2 >& out/log_Tight_PID2.log
