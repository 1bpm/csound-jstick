<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
; ==============================================
<CsInstruments>

sr	=	48000
ksmps	=	1024
nchnls	=	2
0dbfs	=	1


instr 1	
	kfreq init 440
	kaxes[], kbuttons[] jstick 0
	printk2 kaxes[2]
	kfreq = kaxes[3]
	a1 oscil 1, kfreq
	outs a1, a1
endin

</CsInstruments>
; ==============================================
<CsScore>
i1 0 100


</CsScore>
</CsoundSynthesizer>

