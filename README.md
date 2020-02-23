# SearchEngine@Powered by GTK
This app is used to filter files based on a querry given by the user
## Prerequisites
To download the app you'll need the **git** package. If you don't already have it, you can install it by typing one of the following commands in the CLI:
```
sudo apt install --yes git // sudo apt-get --yes git
```
(These commands are only available on Debian based distros)

After installing the **git** package, pick a folder you want to clone the app into, **cd** your way to it and the use the following command:
```
sudo git clone https://github.com/LaurentiuM1234/CDLSearchEngine
```
## Installing
After cloning the repo files, you'll have a folder called **CDLSearchEngine**. Inside of it you can find a script called **run_me.sh** and a folder called **src**.
If you don't already have the **pkg-config** utility and **libgtk-3-dev** you'll have to run the script:

```
sudo ./run_me.sh
```
**(!!! the sudo in the command is very important because without it the script won't be able to install the packages !!!)**

(Also, make sure the script is executable!)

After making sure **libgtk-3-dev** and **pkg-config** were installed, you have to make sure that  **make** and **gcc** are available on your system. If they are, you can open
the **src** directory in **CDLSearchEngine(in CLI, of course)** and build the executable:

```
make build OR make
```
You can run the executable by typing:

```
make run
```
You can delete the executable and the .o files by typing:

```
make clean
```

## Using the engine
After running the **make run** command you'll get the following interface:

[Imgur](https://i.imgur.com/EaoCWzg.png)

To use the app, you have to type the path to the directory containing the .txt files under the **Input directory** label **FIRST**
(DO NOT PRESS THE **Search** BUTTON YET)

After typing the input directory, you have to intorduce the querry under the **querry** label
**(Each token from the querry must be separated by a whitespace)**

e.g:

```
! ( linus || torvalds ) && c && kernel // ( ana || are ) && mere && ! pere
```
**Supported tokens : !, (, ), &&, ||**

After introducing the querry, you can press the **Search** button. The files will be printed in the text box that's above the two labes aforementioned.

[Imgur](https://i.imgur.com/tISV8yj.png)

If you want to introduce another querry, you have to delete the previous one(modification is not yet supported - it can work if you haven't deselected the search box but it's not recommended)
preferably using the delete arrow in the right side of the search box( the delete key on the keybord works too but the search bar can act a bit weird )

**(The input directory will stay the same after pressing the Search button so no need to type it again)**

## Warnings

**1) Not typing anythig in the input directory search bar and then pressing the Search button will lead to exiting the program(intentional)**

 **2) Not typing anything in the querry search bar and then pressing the Search button will lead to exiting the program( intentional)**
  
  **3) Querries can't be longer than 100 characters**
  
  **4) File paths can't be longer than 100 characters**
  
  **5) Input .txt files can't contain more than 5000 characters( this limit can be adjusted in the source files )**
  
  **6) The app uses a lot of resources since it doesn't dealloc some of the resources it uses**
  
  **7) Trying to modify the querry in the querry search bar will lead to some weird output in the console( due to the library used for the GUI). That's why it's recommended to delete the previous querry not modify it.**
  
  **8) Any unsuccesful file openings or allocs will lead to the program closing. (intentional)**
  
  **9) You can have up to 20 tokens in a querry(operators included)**
  
  **10) The word separators in .txt files are the following: ",.;:()'[]- \"?!" , so, as a consequence you can't look for sequences such as :**
  
```
open-source OR example,
```
If you want to look for words separated by "-" for example you have to use the following querry:

```
open && source
```
   **11)!!! MOST IMPORTANTLY DO NOT PRESS THE SEARCH BUTTON AFTER TYPING IN THE INPUT DIRECTORY( ONLY PRESS IT AFTER YOU ENTER THE QUERRY ). THERE'S NO NEED TO TYPE IN THE INPUT DIRECTORY AGAIN AFTER SEARCHING FOR THE FIRST QUERRY UNLESS YOU WANT TO CHANGE IT !!!**
   
## Built with
-> GTK+3.0

-> The C programming language

## Author

Mihalcea Laurentiu-Cristian

## Acknowledgments

Special thanks go to:

->Dorin@CDL

->Stack overflow

->@Dijkstra for inventing the shunting-yard algorithm

->GTK+3.0 reference page for the function definitions

->Glade 

->Ora de SD de la CB for helping me understand how to implement generic stacks and queuesFr

For additional information or possible bugs contact me at: **laurentiumihalcea111@gmail.com**

