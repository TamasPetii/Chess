# Chess SDL Project

![kép](https://user-images.githubusercontent.com/60004480/178121657-2c6624b3-4e16-417d-81fa-dc5e7c0fe026.png)
# About the Game
This game was created in c++ made whit **Simple DirectMedia Layer** (SDL). <br><br>
At this time it is a **1V1** game, which means 2 person needed to play the game properly.<br><br>
All the steps are checked and everything works by the rules.<br><br>
If the current player clicks on a piece the game instantly shows the pieces possible steps. 
# Game Marks


It can be a blue circle or a blue square with an transparent middle. <br>


|Mark                           |Meanings                     |
|-------------------------------|-----------------------------|
| ![kép](https://user-images.githubusercontent.com/60004480/178143304-b7d616e2-68e6-4332-bc6e-255d7b1060ec.png) | The possible step's position is empty |
|![kép](https://user-images.githubusercontent.com/60004480/178143334-dbbc476e-95d6-4d29-a17a-1d43a599ee85.png)  | On the possible step's position there is an opponent's piece |
|![kép](https://user-images.githubusercontent.com/60004480/178143753-57a3304a-1b52-4c10-8e41-8e575572f6ed.png) | When a player checks, a red square with a transparent center appears on the opponent's king|
|![kép](https://user-images.githubusercontent.com/60004480/178143401-2746720e-50b5-4a24-bdb3-29003b75c6cc.png) | If black resigns or black got chessmated the game stops and this picture will be displayed |
|![kép](https://user-images.githubusercontent.com/60004480/178143415-a46a3bf8-cd33-408e-b143-839f9a9d0287.png) | If white resigns or black got chessmated the game stops and this picture will be displayed |
|![kép](https://user-images.githubusercontent.com/60004480/178143483-46da890e-01fe-4e5e-8d7d-91d9ee7bacb8.png) | If both player deceide to draw or only the knigs are on the board this picture will be displayed | 

# About the Buttons

At the right side there are several colourfull or colourless (grey) buttons.<br>
- `Colourfull` : You can press that button and it could affect the program.           
- `Colourless / Red X`: You can't press that button and it won't effect the program.
<br>

|Buttons                        |Meanings                     |
|-------------------------------|-----------------------------|
|![kép](https://user-images.githubusercontent.com/60004480/178141802-a512d6e2-bfaf-4acf-8774-0fa65f4e16f2.png) | It changes the board colour to ***GREEN - BEIGE***        |
|![kép](https://user-images.githubusercontent.com/60004480/178141898-1644f426-24c3-4236-a5bb-1a0bf6e797ba.png) | It changes the board colour to ***PUEPLE - LIGHTGREY***   |
|![kép](https://user-images.githubusercontent.com/60004480/178141950-0f8e9fa8-21ec-472f-b099-c23b5025d525.png) | It changes the board colour to ***DARKWOOD - LIGHTWOOD*** |
|![kép](https://user-images.githubusercontent.com/60004480/178142057-fbbe729d-e811-4045-96bb-3519eacb4400.png) | By pressing it you'll ***RESIGN***, the game ended with your opponent's won.        |
|![kép](https://user-images.githubusercontent.com/60004480/178142066-02a3d0a5-ea33-419e-bcfe-edcc51de695b.png) | By pressing it you indicate the opportunity of a ***DRAW***. If your opponent deciedes to press his/her button too the game ends with a draw.        |
|![kép](https://user-images.githubusercontent.com/60004480/178142325-456f8fdc-282d-43cc-842a-ac06fa517449.png) | By pressing it you can go ***BACK*** at the game and examine the staps taken   |
|![kép](https://user-images.githubusercontent.com/60004480/178142382-bb092ad7-a0ec-4946-86ed-222150f32190.png) | By pressing it you can go ***FORWARD*** at the game and examine the staps taken        |
|![kép](https://user-images.githubusercontent.com/60004480/178142428-d532456b-47a4-432f-8bcc-89c94334ccec.png) | By pressing it the board will immediately turn back to the ***CURRENT*** stand |
|![kép](https://user-images.githubusercontent.com/60004480/178142494-0c416d61-964a-45de-b770-d759f2f18d73.png) | By pressing it a new game will stat |
|![kép](https://user-images.githubusercontent.com/60004480/178142524-ce8d9697-2068-47de-b0ae-70afae274de1.png) | By pressing it all the steps will be saved to a file. (Could be pressed only if game ended!)|

# Featues

- There is no memory leak according to ***CrtDumpMemoryLeaks()***
- Board is represented as a one dimensional vector
- You can save the game to a file
- You can go back and go forward at the game
- Customizable board background
- Every move is documented in the terminal (USE WINDOWS TERMINAL PS | UBUNTU TERMINAL!!!)
![kép](https://user-images.githubusercontent.com/60004480/178144025-b5c1bb8f-e2ec-456a-858c-75dc9935bc94.png)

# For further development

* Making more game modes:<br>
  * Player vs AI <br> 
  * AI vs AI <br>
  * 4 player game mode
* King castle movement

# Installation
1. Download SDL2 pack: https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip
2. Download SDL2_image pack: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip

# Setup Visual Studio Code / Terminal Compile
0. `The .cpp, .h, .png files are already int the main directory | SDL pack is already downloaded` <br>
1. `Create a "src" directory in the main directory` <br>
2. `Create a "include" directory in the src directory, and put the SDL header files there` <br>
3. `Create a "lib" directory in the src directory, and put the following librarys there: SDL2.lib, SDLmain.lib, SDL_image.lib` <br>
4. `Put the following dlls int the main direcotry: SDL2.dll, SDL_image.dll, libpng16-16.dll` <br>
5. `Open a terminal in the main library and copy this command and run a.exe:`<br> 
`g++ -Isrc/include -Lsrc/lib *.cpp -lSDL2main -lSDL2 -lSDL2_image -Wall -Wextra`

# Setup Visual Studio 2022 
1. Make a folder in local disk C:\ named as SDL.
2. In C:\SDL folder make folders named as bin, include and lib.
3. Extract the downloaded SDL2 folders and copy their x64 include content to the C:\SDL\include folder. Do the same thing with lib and bin folders (x64!!!). (If lib and bin files are in the same directory of the extracted SDL2 packs then sort them to the proper folds. )
4. Open a terminal and write this command: subst T: C:\SDL
5. Open Visual Studio 2022, make a project and open project settings.
6. Set the top bar like this.

<div align="center">
  
![kép](https://user-images.githubusercontent.com/60004480/183756201-ad72efa9-24f5-4ce0-93ca-4c6f3a25e4a1.png)

</div>
  
7. VC++ Directories >> Include directories >> T:\include;$(IncludePath)

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183755848-45156c5c-5283-4a82-a50d-2c31995a769b.png)

</div>

8. VC++ Directories >> Include directories >> T:\lib;$(LibraryPath)

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756057-69c29e07-f5ab-4154-87ff-cb18b109fd9a.png)

</div>

9. Debugging >> PATH=T:\bin;%PATH%

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756467-cce70722-d354-4400-aa8f-e5a40e635e6b.png)

</div>

10. Linker >> Input >> Additional Dependencies >> SDL2.lib;SDL2main.lib;SDL2_image.lib;

<div align="center">
  
![kép](https://user-images.githubusercontent.com/60004480/183758297-77e37605-df38-4407-a791-5add1374bb98.png)

</div>

11. Go back set this options like this and you are ready to go.

<div align="center">

![kép](https://user-images.githubusercontent.com/60004480/183756944-4628a035-eaed-4779-bc7a-f28d29cfb899.png)

</div>
