# PROJECT 4 ELEVATOR
## General info 

The project shows a simulation of the elevator. The elevator can move between 3 levels.  At every level are located 2 buttons to transport preson to 2 other levels. 


The program allows you to simulate and display a graphical interpretation of the elevator in 2D - in interface people entering and leaving the elevator using the "Dodaj pasażera" and "Odejmi pasażera" buttons defined in Recource.h.
You can stop the elevator on specific floors thanks to the buttons on the left side of the user interface with the number of the target floor, when you press more buttons, the program remembers the queue usung vector<int> kolejka[]
You can also force the elevator to start using the "start" button, but you can wait 3 seconds to start it automatically

- The program checks the weight of passengers in the elevator.
If the weight of people in the elevator exceeds the set limit, the program displays the MessageBox "Masa została przekroczona!"
Max weight is 600kg
- If the elevator remains empty on a specific floor for more than 5 seconds, it automatically goes to the ground floor. 
This function works thanks to the "SetTimer" function, which is reset after the elevator moves
- The program presents the mass of transported passengers on the user interface in the right top corner. Average person mass is 70kg 


![image](https://github.com/jwszol-classes/tp2023-KubiHombre/assets/106477285/1db56057-5efd-47ae-9170-b3a326d72ed9)


## Code language: 
C++.
## Sources: 
https://cpp0x.pl/
https://cplusplus.com/
### Authors: Jakub Ebertowski, Jakub Dufke. 
