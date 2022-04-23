Summarize the project and what problem it was solving.

The final project was a prototype for a smart thermostat that would send data to servers over Wi-Fi, with the prototype having the low-level functionality implemented. This included reading the room temperature, displaying whether the heat was turned on, adjusting the activation threshold for the thermostat, and simulating data being sent to servers. Additionally, it was meant to test whether the hardware used was appropriate for the final device.

What did you do particularly well?

I think I did well at transmitting intent through variable/function names so that the code is understandable even with somewhat sparse comments.

Where could you improve?

I think the thermostat.c file could have used more structure, as much of the functionality is jammed into the while loop in the mainThread function. Splitting it up into different functions could have made it easier to change or maintain later on.

What tools and/or resources are you adding to your support network?

With my current plans, there are no specific resources related to this project that I am likely to keep track of. It has highlighted the amount of information available in technical reference manuals though, which I will keep in mind for if I work with hardware.

What skills from this project will be particularly transferable to other projects and/or course work?

The information related to state machines and creating diagrams is likely to be useful in other areas. State machines are fairly common even in software designed for PCs or mobile devices, from what I have read.

How did you make this project maintainable, readable, and adaptable?

As mentioned before, I tried to take care when naming variables to improve readability. Another example is placing comments where the purpose of the code may not be obvious, such as the comments within the timerCallback function in morseLED.
