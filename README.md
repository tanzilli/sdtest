#Set of utilities to test the SD cards behaviour

##hrt_stress

This is a Kernel module written Antonio Galea for stressing the high resolution timer system
and generate a lot of interrupts. 

Sintax:

<pre>
debarm:~# insmod hrt_stress.ko frequency=500000
HRT stress test initializing.
Clock resolution is 1ns
Frequency for timer interrupts: 500000Hz.
Starting timer to fire every 2000ns
HRT stress test initialized.
hrtimer: interrupt took 47300 ns
</pre>
