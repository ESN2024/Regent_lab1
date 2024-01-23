# Regent_lab1
# Lab 1: “Let there be light” - Implement a led chaser

1. The first step is to create a basic Nios II system 
So I've used the platform designer of Quartus:
![image](https://github.com/ESN2024/Regent_lab1/assets/131348400/8d73d5fb-e80e-4f5c-8703-85e99cb111f2)

From this system desgin, we can implement the code of the hardware:
 ![image](https://github.com/ESN2024/Regent_lab1/assets/131348400/490f67c3-e204-4db6-b66d-a01d17273807)

After having made the analysis and synthesis, we can connect the signals to the true outputs of the FPGA (the pins) thanks to the Pin Planner:
![image](https://github.com/ESN2024/Regent_lab1/assets/131348400/3e2d57d8-f64c-43ec-8abf-42ce837a53c0)

I've made 4 differents scripts: main.c, chenillard.c, trigger.c, switch.c
The first one just lights up a LED.
chenillard.c turn the lights on, one after the other and repeat it in a while loop.
trigger.c, here I used an interrupt function using a push button in order to trigger the "chenillard".
switch.c, as before I use an interrupt function in order to change the speed of the "chenillard".

Everything work as attempted !!!

This lab learned me how to create a Nios II system, how to code with a software intagrated in the FPGA and how to look for information in the documentation.
