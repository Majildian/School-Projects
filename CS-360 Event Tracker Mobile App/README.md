**Briefly summarize the requirements and goals of the app you developed. What user needs was this app designed to address?**

The requirements were for the app to have a login screen, a database interface screen that supported CRUD operations, and a notification system. It was designed to address the need for an application that could keep track of important events in the user's life and remind the user about them shortly before they occurred.

**What screens and features were necessary to support user needs and produce a user-centered UI for the app? How did your UI designs keep users in mind? Why were your designs successful?**

I would say the necessary screens were the screen to display events for the current day, the dialog to choose a different day and the screen to add an event to the current day. Because of the limited screen space, trying to fit those all on one screen would have been detrimental to the user experience. A screen for controlling the notification system was also necessary solely because it was implemented to deliver SMS notifications, which required the user to set a phone number. I attempted to keep the designs intuitive using standardized icons for actions, such as the disk for the save action and the gear for opening the settings screen.

**How did you approach the process of coding your app? What techniques or strategies did you use? How could those be applied in the future?**

Much of the code needed to implement the features of this app was available through the course resources, so my first step was to adapt what I could from there. For some features, I wasn't able to completely understand what was needed to adapt from the resource to the app at first. There were also some features such as the notifications that needed a large amount of research to properly implement. My main method for researching in these cases was to either review the Android reference if it was a specific class I was having trouble with, or searching the web for the related feature if it was a broader issue. Reviewing the library reference and searching the web are both strategies that could be applied to any number of situations.

**How did you test to ensure your code was functional? Why is this process important and what did it reveal?**

My testing process was manual, and it involved making small changes to the code then launching the app to see if it functioned as expected. The testing process is important to ensure that a program is functioning correctly during use. It can also reveal misconceptions about how library functions are used, especially if the developer is unfamiliar with the library - this happened for me several times.

**Considering the full app design and development process, from initial planning to finalization, where did you have to innovate to overcome a challenge?**

One challenge I encountered was handling the transition from the settings screen to the events screen. The ways of restoring screen state that I was aware of were not functioning like I expected them to, so I chose to save and restore the state using the device storage instead. I may have been able to implement a better way of restoring state if I understood the Android system better, but I decided that this choice was necessary to get the app functional before the deadline.

**In what specific component from your mobile app were you particularly successful in demonstrating your knowledge, skills, and experience?**

Although it's not a section that I think is necessary for this type of app, I think the way I handled validating user credentials is a good example. The username and password both have a minimum length, and attempted logins don't expose whether it is the username or password that are incorrect. Attempting to register a new account can expose whether a username exists, but there is an extra layer of difficulty in using this method to brute force credentials, since successfully creating an account automatically logs you in for a better user experience.
