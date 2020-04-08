# Final Project 1

## Instruction
I'd like to make an animation based on the song Stop The World from the musical Come From Away.
Users can have some simple interactions with the charater (e.g. moving charatcers, interacting with the scene and other characters, changing the scenes)

Here is the design for the two main characters <br/>
![](imgs/character.jpg)
___________
## Problems
1. I have a display error when I used the ofDrawBezier function. It seems like there is a notch in the curve.<br/>The code for the arms is in the drawFoxDef() function.
``` C++
ofDrawBezier(foxCenterPosX + 100/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 30/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 125/jpgTimes, foxCenterPosY + 400/jpgTimes, foxCenterPosX - 21, foxCenterPosY + 500/jpgTimes);

ofDrawBezier(foxCenterPosX + 370/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX + 470/jpgTimes, foxCenterPosY + 150/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 300/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 500/jpgTimes);
```

![error](imgs/error.png)

2. If I want to draw a buch of objects(e.g. birds, clouds...) in openFrameworks, what should I do? ( or how can I use array in OF?)

![bird](imgs/bird.png)

3. If I want to switch between different scenarios (e.g. from scene A to scene B), what should I do?

![scene A](imgs/sceneA.jpg)
![scene B](imgs/sceneB.jpg)


### Thank you!
