# Diablo3-model-exporter

Hi
This is a Diablo 3 model extractor, it uses the installed game to export all the files.
Diablo 3 needs to be installed on your system for this to work.

## Step by step:
Firstly you need to find a file you want to extract. The easiest way to do this is to use a program like [CascView](http://www.zezula.net/en/casc/main.html "CascView")
You'll need to look for .app files under Appearance.
When you have found a file you wan't to use, copy or write down the name.
Open cmd in the folder with the exporter exe. You can easily do this by typing cmd in the finders path text box and pressing enter.
Execute the exe with the following command line arguments `"<diablo3 installation folder>"` and `"<app filename without .app>"`
The quotation marks need to be in there.
For example `DiabloExporter.exe "F:\blizzard\Diablo III" "Cain"`
This wil extract a T posing Deckard Cain.

If you run it for the first time the program will map some id's to files and after doing so it will create the requested file.

When you run it without command line arguments it will try to run the program with my personal parameters which I use for lazy testing. There is a very slim chance that would work for your pc.


### This is a very early build of the app and has only been tested on a few models. If any bugs occur ,and they will occur, take note of the model you tried out and send the info to me. This can best be done through issues.
