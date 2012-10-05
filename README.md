#Set of utilities to test the SD cards behaviour

##hrt_stress

This is a Kernel module written Antonio Galea for stressing the high resolution timer system
and generate a lot of interrupts. 

Sintax:

<pre>
debarm:~/sdtest# insmod hrt_stress.ko frequency=10000                           
HRT stress test initializing.                                                   
Clock resolution is 1ns                                                         
Frequency for timer interrupts: 10000Hz.                                        
Starting timer to fire every 100000ns                                           
HRT stress test initialized. 
</pre>
