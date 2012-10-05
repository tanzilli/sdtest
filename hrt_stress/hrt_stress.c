/* Copyright (C) 2010 Antonio Galea
 *
 * May be copied or modified under the terms of the GNU General Public
 * License. See linux/COPYING for more information.
 *
 * Module for stressing the high resolution timer system
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antonio Galea");
MODULE_DESCRIPTION("Stress test for high resolution timer");

#if defined(CONFIG_PREEMPT)
#define DEFAULT_FREQUENCY  1000000L // 1MHz
#else
#define DEFAULT_FREQUENCY   100000L // 100kHz
#endif

static int frequency = DEFAULT_FREQUENCY;
module_param(frequency, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
#if defined(CONFIG_PREEMPT)
MODULE_PARM_DESC(frequency, " timer interrupt frequency [1Hz-100kHz, default 20kHz]");
#else
MODULE_PARM_DESC(frequency, " timer interrupt frequency [1Hz-40kHz, default 20kHz]");
#endif

ktime_t interval;
static struct hrtimer hr_timer;
int value=0;

enum hrtimer_restart hrt_callback(struct hrtimer *timer){
  value=1-value;
  __gpio_set_value(80,value); //toggle pin J7.3 (PB18)
  hrtimer_forward(&hr_timer, ktime_get(), interval);
  return HRTIMER_RESTART;
}

/* module initialization: init the hr-timer and register a driver class */
static int __init hrt_stress_init(void){
  struct timespec tp;
  unsigned long duration;

  printk(KERN_INFO "HRT stress test initializing.\n");

  hrtimer_get_res(CLOCK_MONOTONIC, &tp);
  printk(KERN_INFO "Clock resolution is %ldns\n", tp.tv_nsec);

  hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  hr_timer.function = &hrt_callback;

  if(frequency<1){
    printk(KERN_INFO "Requested frequency %uHz should be positive, reverting to default.\n", frequency);
    frequency = DEFAULT_FREQUENCY;
  }
  printk(KERN_INFO "Frequency for timer interrupts: %uHz.\n", frequency);
  duration = 1000000000L/frequency;
  interval = ktime_set(0, duration);

  printk(KERN_INFO "Starting timer to fire every %ldns\n", duration);
  hrtimer_start(&hr_timer, interval, HRTIMER_MODE_REL);

  printk(KERN_INFO "HRT stress test initialized.\n");
  return 0;
}

/* module finalization: cancel the hr-timer */
static void __exit hrt_stress_exit(void){
  hrtimer_cancel(&hr_timer);
  printk(KERN_INFO "HRT stress test stopped.\n");
}

module_init(hrt_stress_init);
module_exit(hrt_stress_exit);
