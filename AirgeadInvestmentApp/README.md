**Summarize the project and what problem it was solving.**
This program allows users to input an initial investment, monthly investment, number of years and interest rate. It then calculates and displays the yearly and monthly returns on the initial investment over the time period, as well as returns on the initial investment plus monthly investments over the time period. This allows users to directly measure the power of compound interest and increase their understanding of fiscal responsibility.

**What did you do particularly well?**
I think the design of this program is something I did well on. The separation of calculating interest, displaying reports and handling of user input into different classes allows for each portion to be changed relatively easily.

**Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?**
One improvement would be to allow any number of months in the calculator portion, rather than chunks of 12 months. This would increase flexibility. The for loop conditionals in the reporting portion look convoluted, so cleaning those up would likely make it easier to understand.

**Did you find writing any piece of this code challenging, and how did you overcome this? What tools and/or resources are you adding to your support network?**
None of this code was particularly challenging to write. I will likely continue to use cppreference.com in the future to find and understand C++ functions.

**What skills from this project will be particularly transferable to other projects and/or course work?**
The experience with exception handling is likely to be useful in the future. The experience with using a particular code style will also likely be useful, since uniform code style is required in many cases.

**How did you make this program maintainable, readable, and adaptable?**
As mentioned before, the separation of responsibilities into different classes increases maintainability and adaptability significantly. I also attempted to use self-explanatory variable names, add a comment for the purpose of most functions, and comment within functions to explain any code where the purpose didn't seem obvious. The use of constants in the reporting and menu portion also allows for quick adjustment of the display, if necessary.
