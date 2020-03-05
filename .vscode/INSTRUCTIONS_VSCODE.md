## Guide for building with visual studio code on linux with ubuntu 18.04 and derivatives

- install git, compilers, etc

```sudo apt install git build-essential cmake cmake-qt-gui -y```

- install Visual Studio Code

- In vscode launch extension manager (Ctrl+Shift+X) and install the extensions ```C/C++``` and ```Task Explorer```. Close vscode (or restart it).

- Fork this repo by pressing the fork button on github.

- Open a terminal. Run (after changing the github username in the first line):

```bash
export my_github_username=YOUR_NAME_HERE
mkdir -p $HOME/Work/MachineLearningSuite
cd $HOME/Work/MachineLearningSuite
git clone https://github.com/${my_github_username}/MachineLearningSuite MachineLearningSuite-src
# Launch vscode + open the source!
code MachineLearningSuite-src
```

- Inside VS Code in the explorer section (Ctrl+Shift+E) you will see a tab called "TASK EXPLORER". You will need to run the tasks under ```MachineLearningSuite-src>vscode``` (instruction below).

- The first time run the ```Setup OpenCV (run once)``` task. This will clone, configure and build OpenCV in both debug and release.

- ```CMAKE [Debug]``` and ```CMAKE [Release]``` configure and generate the project for debug and release respectively. These are a prerequisite for building. This should also be run again when something changes in the cmake files (usually because a source file was added).

- ```BUILD [Debug]``` and ```BUILD [Release]``` well.. build the project. Debug is slower and bigger (in terms of binary/libraries size) but allows the use of the debugger. Release is fast, but doesn't offer debugging. These tasks can also be accessed by pressing (Shift+Ctrl+B).

- To use the debugger, open the debug section (Ctrl+Shift+D). Select the debug configuration you want to run and press the play button at the top. Make sure you have run the task ```BUILD [Debug]``` beforehand, the play button just launches the debugger, it doesn't build. You can edit/add configurations by pressing the "settings-wheel" button next to the dropdown (it is just the file ```.vscode/launch.json```). Notice the "args" key.

- To run without a debugger use that start with RUN (i.e. ```RUN [Debug] train```). You can add more tasks by editing the file ```.vscode/tasks.json```. Of course, you can just invoke the executable directly from a terminal; it is ```$HOME/MachineLearningSuite/MachineLearningSuite-build/Release/MachineLearningSuite``` (or ```*/Debug/*```).